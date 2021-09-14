#pragma once
#include <qwidget.h>
#include <Scintilla.h>
#include "scintilla_api_wrapper.h"
#include "scintilla_module_manager.h"

namespace shelllet {
	namespace scintilla {
		class scintilla_component : public QWidget, public ScintillaModuleManager

		{
		public:
			scintilla_component(QWidget* parent);
			~scintilla_component();
		public:
		private:

		public:

		private:
			//QWidget* widget_;
		protected:
			bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
		};
	}
}
