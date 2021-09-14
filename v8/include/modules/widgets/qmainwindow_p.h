#pragma once
#include "qwidget_p.h"
namespace shelllet {
	namespace widgets {
		template<typename T, bool C>
		class MainWindowPrivate : public WidgetPrivate<T, C>
		{
		public:
			template<typename ...Args>
			MainWindowPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : WidgetPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
