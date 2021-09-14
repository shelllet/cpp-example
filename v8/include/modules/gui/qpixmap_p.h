#pragma once
#include "qpaintdevice_p.h"

namespace shelllet::gui {
	template<typename T, bool C>
	class QPixmapPrivate : public QPaintDevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QPixmapPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QPaintDevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
