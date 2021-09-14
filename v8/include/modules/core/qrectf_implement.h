#pragma once
#include "framework.h"
#include <qrect.h>
#include "qrect_p.h"
#include "qrect_wrapper.h"
#include "qpoint_implement.h"
#include "qsize_implement.h"

namespace shelllet {
	namespace core {
		class RectF : public QRectFWrapper<QRectF, RectF, true>
		{
		public:
			using ReturnType = QRectFPrivate<QRectF, true>;
			using ReturnType2 = QRectFPrivate<QRectF, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				if (args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber()) {
					auto x1 = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
					auto y1 = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
					auto w = args[2]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
					auto h = args[3]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
					return new ReturnType(args.GetIsolate(), args.This(), x1, y1, w, h);
				}

				if (GetConstructorName(args.GetIsolate(), args[0]) == Point::Name() && GetConstructorName(args.GetIsolate(), args[1]) == Size::Name()) {
					auto* p = Point::From(args[0]);
					auto* s = Size::From(args[1]);
					if (p && s) {
						return new ReturnType(args.GetIsolate(), args.This(), **p, **s);
					}
				}

				if (GetConstructorName(args.GetIsolate(), args[0]) == Point::Name() && GetConstructorName(args.GetIsolate(), args[1]) == Point::Name()) {
					auto* p1 = Point::From(args[0]);
					auto* p2 = Point::From(args[1]);
					if (p1 && p2) {
						return new ReturnType(args.GetIsolate(), args.This(), **p1, **p2);
					}
				}
				return new ReturnType(args.GetIsolate(), args.This());
			}
			RectF(const v8::FunctionCallbackInfo<v8::Value>& args) :QRectFWrapper(*Private(args), args)
			{
			}
			RectF(QRectF* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QRectFWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			RectF(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QRectFWrapper(isolate, tpl) {}
			RectF(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QRectFWrapper(isolate, proto)
			{}

			static const char* Name() { return "RectF"; }
		protected:
			virtual void toString(std::stringstream& ss) const {
			}
		};
	}
}
