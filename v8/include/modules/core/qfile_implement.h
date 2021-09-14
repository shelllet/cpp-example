#pragma once
#include "framework.h"
#include <qfile.h>
#include "qfile_p.h"
#include "qfile_wrapper.h"

namespace QT_NAMESPACE { class QFile; }

namespace shelllet {
	namespace core {
		class File : public  QFileWrapper<QFile, File, true>
		{
			using ReturnType = QFilePrivate<QFile, true>;
			using ReturnType2 = QFilePrivate<QFile, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			File::File(const v8::FunctionCallbackInfo<v8::Value>& args) : QFileWrapper(*Private(args), args)
			{
			}
			File(QFile* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QFileWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			File::File(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl, const v8::Local<v8::ObjectTemplate>& proto) : QFileWrapper(isolate, tpl)
			{
			}

		public:
			static const char* Name() { return "QFile"; }
		};
	}
}
