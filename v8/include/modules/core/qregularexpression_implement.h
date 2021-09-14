#pragma once
#include "framework.h"
#include <qregularexpression.h>
#include "qregularexpression_p.h"
#include "qregularexpression_wrapper.h"

namespace shelllet {
	namespace core {
		class RegularExpression : public RegularExpressionWrapper<QRegularExpression, RegularExpression, false>
		{
			using ReturnType = RegularExpressionPrivate<QRegularExpression, true>;
			using ReturnType2 = RegularExpressionPrivate<QRegularExpression, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			RegularExpression(const v8::FunctionCallbackInfo<v8::Value>& args) : RegularExpressionWrapper(*Param(args), args) {}
			RegularExpression(QRegularExpression* p, const v8::FunctionCallbackInfo<v8::Value>& args) : RegularExpressionWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			RegularExpression(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : RegularExpressionWrapper(isolate, tpl) {}
			RegularExpression(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : RegularExpressionWrapper(isolate, proto) {}

			static const char* Name() { return "regex"; }
			static bool Test(v8::Isolate* isolate, const v8::Local<v8::RegExp>& regex, const std::wstring& str)
			{
				v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(regex->Get(isolate->GetCurrentContext(), V8_NEW_STRING_VAR(isolate, "test")).ToLocalChecked());
				v8::Local<v8::Value> argv[] = { V8_NEW_WSTRING_VAR(isolate, str.c_str()) };
				auto result = f->CallAsFunction(isolate->GetCurrentContext(), regex, std::size(argv), argv);
				if (result.IsEmpty()) {
					return false;
				}
				return result.ToLocalChecked()->BooleanValue(isolate);
			}
		public:
		};
	}
}
