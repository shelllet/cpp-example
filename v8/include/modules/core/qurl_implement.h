#pragma once
#include "framework.h"
#include <qurl.h>
#include "qurl_p.h"
#include "qurl_wrapper.h"

namespace shelllet {
	namespace core {
		class Url : public QUrlWrapper<QUrl, Url, true>
		{
		public:
			using ReturnType = QUrlPrivate<QUrl, true>;
			using ReturnType2 = QUrlPrivate<QUrl, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				if (args[0]->IsExternal()) {
					v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(args[0]);
					auto* url = wrap->Value();
					if (url)
						return new ReturnType(args.GetIsolate(), args.This(), *static_cast<QUrl*>(url));
				}
				else if (args[0]->IsString()) {
					QUrl::ParsingMode parsingMode = QUrl::TolerantMode;
					if (args[1]->IsNumber()) {
						parsingMode = static_cast<QUrl::ParsingMode>(args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust());
					}
					return new ReturnType(args.GetIsolate(), args.This(), ToString({ args.GetIsolate(), args[0] }), parsingMode);
				}

				return new ReturnType(args.GetIsolate(), args.This());
			}

			Url(const v8::FunctionCallbackInfo<v8::Value>& args) :QUrlWrapper(*Private(args), args)
			{
			}
			Url(QUrl* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QUrlWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Url(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QUrlWrapper(isolate, tpl) {}
			Url(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QUrlWrapper(isolate, proto)
			{}

			static const char* Name() { return "Url"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
