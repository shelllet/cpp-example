#pragma once
#include "framework.h"
#include "widgets/qapplication_implement.h"
#include "widgets/qwidget_implement.h"
#include "widgets/qmainwindow_implement.h"

namespace shelllet {
	namespace qtcore {
		void initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) {
			using namespace shelllet::core;
			{
				proto->Set(isolate, Application::Name(), Application::WrapClass(isolate));
				proto->Set(isolate, MainWindow::Name(), MainWindow::WrapClass(isolate));
				proto->Set(isolate, Widget::Name(), Widget::WrapClass(isolate));
			}
		
		}
	}
}