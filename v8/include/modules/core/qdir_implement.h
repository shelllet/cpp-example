#pragma once
#include "framework.h"
#include <qdir.h>
#include "qdir_p.h"
#include "qdir_wrapper.h"

namespace shelllet {
	namespace core {
		class Dir : public QDirWrapper<QDir, Dir, true>
		{
			using ReturnType = QDirPrivate<QDir, true>;
			using ReturnType2 = QDirPrivate<QDir, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			Dir(const v8::FunctionCallbackInfo<v8::Value>& args) :QDirWrapper(*Param(args), args)
			{
			}
			Dir(QDir* p, const v8::FunctionCallbackInfo<v8::Value>& args) :QDirWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Dir(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QDirWrapper(isolate, tpl)
			{
				
			}

			Dir(v8::Isolate* isolate,  const v8::Local<v8::ObjectTemplate>& proto) : QDirWrapper(isolate, proto)
			{
				
			}

		protected:
			void toString(std::stringstream& ss) const {}
		public:
			static const char* Name() { return "Dir"; }
		protected:
			
		};
	}
}
