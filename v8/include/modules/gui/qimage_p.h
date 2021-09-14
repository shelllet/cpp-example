#pragma once
#include "qpaintdevice_p.h"

namespace shelllet::gui {
	template<typename T, bool C>
	class QImagePrivate : public QPaintDevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QImagePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QPaintDevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		
	};
}
