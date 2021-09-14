#pragma once
#include "framework.h"
#include <qpoint.h>
#include "qpointf_p.h"
#include "qpointf_wrapper.h"

namespace shelllet {
	namespace core {
		class PointF : public QPointFWrapper<QPointF, PointF, true>
		{
		public:
			using ReturnType = QPointFPrivate<QPointF, true>;
			using ReturnType2 = QPointFPrivate<QPointF, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				auto w = args[0]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();
				auto h = args[1]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromJust();
				return new ReturnType(args.GetIsolate(), args.This(), w, h);
			}
			PointF(const v8::FunctionCallbackInfo<v8::Value>& args) :QPointFWrapper(*Private(args), args)
			{
			}
			PointF(QPointF* p, const v8::FunctionCallbackInfo<v8::Value>& args) :QPointFWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			PointF(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QPointFWrapper(isolate, tpl)
			{
			}
			PointF(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QPointFWrapper(isolate, proto)
			{
			}

		protected:
			void toString(std::stringstream& ss) const { ss << "(" << (*this)->x() << ", " << (*this)->y() << ")"; }
		public:
			static const char* Name() { return "PointF"; }
		protected:
		};
	}
}
