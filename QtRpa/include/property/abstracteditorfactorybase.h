#pragma once
#include "qobject.h"

namespace shelllet {
	namespace property {
		class PropertySheet;
		class AbstractPropertyManager;
		class AbstractEditorFactoryBasePrivate;
		class AbstractEditorFactoryBase : public QObject
		{
			Q_OBJECT
		public:
			virtual QWidget* createEditor(PropertySheet* property, QWidget* parent) = 0;
		protected:
			explicit AbstractEditorFactoryBase(QObject* parent = 0)
				: QObject(parent) {}

			virtual void breakConnection(AbstractPropertyManager* manager) = 0;

			AbstractEditorFactoryBase(AbstractEditorFactoryBasePrivate& d, QObject* parent);
		protected slots:
			virtual void managerDestroyed(QObject* manager) = 0;

			friend class AbstractPropertyBrowser;
		};

	}
}
