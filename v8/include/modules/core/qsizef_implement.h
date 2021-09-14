#pragma once
#include "framework.h"
#include <qsize.h>
#include "qsize_p.h"
#include "qsize_wrapper.h"

namespace shelllet {
	namespace core {
		class SizeF : public QSizeFWrapper<QSizeF, SizeF, true>
		{
		public:
			using ReturnType = QSizeFPrivate<QSizeF, true>;
			using ReturnType2 = QSizeFPrivate<QSizeF, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				auto w = args[0]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();
				auto h = args[1]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();

				return new ReturnType(args.GetIsolate(), args.This(), w, h);
			}

			SizeF(const v8::FunctionCallbackInfo<v8::Value>& args) :QSizeFWrapper(*Private(args), args)
			{
			}
			SizeF(QSizeF* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QSizeFWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			SizeF(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QSizeFWrapper(isolate, tpl) {}
			SizeF(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QSizeFWrapper(isolate, proto)
			{}

			static const char* Name() { return "SizeF"; }
		protected:
			virtual void toString(std::stringstream& ss) const {
				//ss << "(" << (*this)->x() << ", " << (*this)->y() << ")";
			}
		};
	}
}
