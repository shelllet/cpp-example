import * as dec from "./decode.js"

export function create(data, filename){
	var declares = dec.declareFuncs("tpl", data.static);
	var bodies = dec.implFuncs(data.static, data.className);

    var code = `#pragma once
#include "framework.h"
#include <${data.className.toLowerCase()}.h>
#include "${data.className.toLowerCase().replace("_", "")}_p.h"
#include "${data.className.toLowerCase().replace("_", "")}_wrapper.h"

namespace shelllet {
	namespace ${data.namespace} {
		class ${data.name} : public ${data.className}Wrapper<${data.className}, ${data.name}, ${data.canNew}>
		{
			using ReturnType = ${data.className}Private<${data.className}, true>;
			using ReturnType2 = ${data.className}Private<${data.className}, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			${data.name}(const v8::FunctionCallbackInfo<v8::Value>& args) :${data.className}Wrapper(*Param(args), args)
			{
			}
			${data.name}(${data.className}* p, const v8::FunctionCallbackInfo<v8::Value>& args) :${data.className}Wrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			${data.name}(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ${data.className}Wrapper(isolate, tpl)
			{
				${declares}
			}

			${data.name}(v8::Isolate* isolate,  const v8::Local<v8::ObjectTemplate>& proto) : ${data.className}Wrapper(isolate, proto)
			{
				${declares}
			}

		protected:
			void toString(std::stringstream& ss) const {}
		public:
			static const char* Name() { return "${data.name}"; }
		protected:
			${bodies}
		};
	}
}
`
    writeFile(filename, code);
}
