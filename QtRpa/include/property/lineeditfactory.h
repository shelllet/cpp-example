#pragma once
#include "stringpropertymanager.h"
#include "abstracteditorfactory.h"
namespace shelllet {
    namespace property{
        class LineEditFactoryPrivate;
        class LineEditFactory : public AbstractEditorFactory<StringPropertyManager> {
			Q_OBJECT
            Q_DECLARE_PRIVATE(LineEditFactory)
        public:
           // LineEditFactory(Object*parent = nullptr);

		public:
			LineEditFactory(QObject* parent = 0);
			~LineEditFactory();
		protected:
			void connectPropertyManager(StringPropertyManager* manager);
			QWidget* createEditor(StringPropertyManager* manager, PropertySheet* property,
				QWidget* parent);
			void disconnectPropertyManager(StringPropertyManager* manager);
		private:
			//QScopedPointer<LineEditFactoryPrivate> d_ptr;
			//Q_DECLARE_PRIVATE(QtLineEditFactory)
			//	Q_DISABLE_COPY_MOVE(QtLineEditFactory)
				/*Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(PropertySheet*, const QString&))
				Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(PropertySheet*, const QRegExp&))
				Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QString&))
				Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject*))*/

			
        protected:
            LineEditFactory(LineEditFactoryPrivate& d, QObject* parent, Object*parent1 = nullptr);
        };
    }
}
    