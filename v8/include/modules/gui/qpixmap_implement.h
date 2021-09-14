#pragma once
#include "framework.h"
#include <qpixmap.h>
#include "core/qsize_implement.h"
#include "core/qrect_implement.h"
#include "qcolor_implement.h"
#include "qimage_implement.h"
#include "qpixmap_p.h"
#include "qpixmap_wrapper.h"

namespace shelllet {
	namespace gui {
		using namespace core;
		class Pixmap : public QPixmapWrapper<QPixmap, Pixmap, true>
		{
			using ReturnType = QPixmapPrivate<QPixmap, true>;
			using ReturnType2 = QPixmapPrivate<QPixmap, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			Pixmap(const v8::FunctionCallbackInfo<v8::Value>& args) : QPixmapWrapper(*Private(args), args) {}
			Pixmap(QPixmap* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QPixmapWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Pixmap(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) :QPixmapWrapper(isolate, tpl) {}
			Pixmap(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) :QPixmapWrapper(isolate, proto) {}

			static const char* Name() { return "Pixmap"; }
		};
	}
}
