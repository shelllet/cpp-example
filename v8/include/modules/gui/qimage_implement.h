#pragma once
#include "framework.h"
#include <qimage.h>
#include "core/qsize_implement.h"
#include "core/qrect_implement.h"
#include "core/qpoint_implement.h"
#include "qimage_p.h"
#include "qimage_wrapper.h"

namespace shelllet {
	namespace gui {
		class Image : public QImageWrapper<QImage, Image, true>
		{
			using ReturnType = QImagePrivate<QImage, true>;
			using ReturnType2 = QImagePrivate<QImage, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			Image(const v8::FunctionCallbackInfo<v8::Value>& args) : QImageWrapper(*Private(args), args) {}
			Image(QImage* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QImageWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Image(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QImageWrapper(isolate, tpl) {}
			Image(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QImageWrapper(isolate, proto) {}

			static	const char* Name() { return "Image"; }
		};
	}
}
