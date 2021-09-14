#pragma once
#include "framework.h"
#include <qcolor.h>
#include "qcolor_p.h"
#include "qcolor_wrapper.h"
namespace shelllet {
	namespace gui {
		class  Color : public QColorWrapper<QColor, Color, true>
		{
			using ReturnType = QColorPrivate<QColor, true>;
			using ReturnType2 = QColorPrivate<QColor, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				v8::Isolate* isolate = args.GetIsolate();
				if (args.Length() > 3) {
					int r = args[0]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
					int g = args[1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
					int b = args[2]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
					int a = 255;
					if (args.Length() > 3) {
						a = args[3]->NumberValue(isolate->GetCurrentContext()).ToChecked();
					}

					return new ReturnType(isolate, args.This(), r, g, b, a);
				}
				return new ReturnType(isolate, args.This());
			}
		public:

			Color(const v8::FunctionCallbackInfo<v8::Value>& args) : QColorWrapper(*Param(args), args)
			{
			}
			Color(QColor* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QColorWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Color(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QColorWrapper(isolate, tpl) {}
			Color(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QColorWrapper(isolate, proto) {
			}

		public:
			static const char* Name() { return "Color"; }
		};
	}
}
