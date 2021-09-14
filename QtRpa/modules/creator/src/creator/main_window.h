#pragma once
#include "qobject.h"
#include "common/common_widget.h"
#include "wizard.hpp"

namespace shelllet {
	namespace creator {
		class AppWindowPrivate;
		class AppWindow : public MainWindow, public ResponseHandler
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, AppWindow)
		public:
			AppWindow(QWidget* parent = nullptr);
			~AppWindow();
		public:
			void finshed(Exit exit) override;
			void show();
			void create();
			void fromGit();
			void open();


		};
	}
}