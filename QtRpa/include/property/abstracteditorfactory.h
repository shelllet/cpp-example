#pragma once
#include "propertysheet.h"
namespace shelllet {
	namespace property {
		class AbstractEditorFactoryPrivate;
		class PropertySheet;
		template <class PropertyManager>
		class AbstractEditorFactory : public AbstractEditorFactoryBase
		{
		public:
			explicit AbstractEditorFactory(QObject* parent) : AbstractEditorFactoryBase(parent) {}
			QWidget* createEditor(PropertySheet* property, QWidget* parent)
			{
				for (PropertyManager* manager : qAsConst(m_managers)) {
					if (manager == property->propertyManager()) {
						return createEditor(manager, property, parent);
					}
				}
				return 0;
			}
			void addPropertyManager(PropertyManager* manager)
			{
				if (m_managers.contains(manager))
					return;
				m_managers.insert(manager);
				connectPropertyManager(manager);
				connect(manager, &AbstractEditorFactory::destroyed, this, &AbstractEditorFactory::managerDestroyed);
			}
			void removePropertyManager(PropertyManager* manager)
			{
				if (!m_managers.contains(manager))
					return;
				
				disconnect(manager, &AbstractEditorFactory::destroyed, this, &AbstractEditorFactory::managerDestroyed);
				disconnectPropertyManager(manager);
				m_managers.remove(manager);
			}
			QSet<PropertyManager*> propertyManagers() const
			{
				return m_managers;
			}
			PropertyManager* propertyManager(PropertySheet* property) const
			{
				AbstractPropertyManager* manager = property->propertyManager();
				for (PropertyManager* m : qAsConst(m_managers)) {
					if (m == manager) {
						return m;
					}
				}
				return 0;
			}
		protected:
			AbstractEditorFactory(AbstractEditorFactoryPrivate& d, QObject* parent) :AbstractEditorFactoryBase(d, parent) {

			}
			virtual void connectPropertyManager(PropertyManager* manager) = 0;
			virtual QWidget* createEditor(PropertyManager* manager, PropertySheet* property,
				QWidget* parent) = 0;
			virtual void disconnectPropertyManager(PropertyManager* manager) = 0;
			void managerDestroyed(QObject* manager)
			{
				for (PropertyManager* m : qAsConst(m_managers)) {
					if (m == manager) {
						m_managers.remove(m);
						return;
					}
				}
			}
		private:
			void breakConnection(AbstractPropertyManager* manager)
			{
				for (PropertyManager* m : qAsConst(m_managers)) {
					if (m == manager) {
						removePropertyManager(m);
						return;
					}
				}
			}
		private:
			QSet<PropertyManager*> m_managers;
			friend class QtAbstractPropertyEditor;
		};

	}
}
