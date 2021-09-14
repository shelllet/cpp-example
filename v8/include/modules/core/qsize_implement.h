#pragma once
#include "framework.h"
#include <qsize.h>
#include "qsize_p.h"
#include "qsize_wrapper.h"

namespace shelllet {
	namespace core {
		class Size : public QSizeWrapper<QSize, Size, true>
		{
		public:
			using ReturnType = QSizePrivate<QSize, true>;
			using ReturnType2 = QSizePrivate<QSize, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				auto w = args[0]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();
				auto h = args[1]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();

				return new ReturnType(args.GetIsolate(), args.This(), w, h);
			}

			Size(const v8::FunctionCallbackInfo<v8::Value>& args) :QSizeWrapper(*Private(args), args)
			{
			}
			Size(QSize* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QSizeWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Size(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QSizeWrapper(isolate, tpl) {}
			Size(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QSizeWrapper(isolate, proto)
			{}

			static const char* Name() { return "Size"; }
		protected:
			virtual void toString(std::stringstream& ss) const {
				//ss << "(" << (*this)->x() << ", " << (*this)->y() << ")";
			}
		};
	}
}
