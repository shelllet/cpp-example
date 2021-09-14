#pragma once
#include "framework.h"
#include <qpoint.h>
#include "qpoint_p.h"
#include "qpoint_wrapper.h"

namespace shelllet {
	namespace core {
		class Point : public QPointWrapper<QPoint, Point, true>
		{
		public:
			using ReturnType = QPointPrivate<QPoint, true>;
			using ReturnType2 = QPointPrivate<QPoint, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				auto w = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
				auto h = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
				return new ReturnType(args.GetIsolate(), args.This(), w, h);
			}
			Point(const v8::FunctionCallbackInfo<v8::Value>& args) :QPointWrapper(*Private(args), args)
			{
			}
			Point(QPoint* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QPointWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Point(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QPointWrapper(isolate, tpl) {}
			Point(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QPointWrapper(isolate, proto)
			{}

			static const char* Name() { return "Point"; }
		protected:

			virtual void toString(std::stringstream& ss) const {
				ss << "(" << (*this)->x() << ", " << (*this)->y() << ")";
			}
		};
	}
}
