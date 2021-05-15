import * as dec from "./decode.js"


export function create(data, filename) {
	var normal = dec.declareFuncs("proto", data.public);
	var normalBodies = dec.implFuncs(data.public, data.className);

	var signals = dec.declareSignals(data.signals);
	var sginalBodies = dec.implSignals(data.signals, data.className);
	
	var props = dec.declareProps(data.propeties);
	var propsBodies = dec.implProps(data.propeties, data.className);

	var code = `#pragma once
namespace shelllet {
	namespace ${data.namespace} {
		template<typename T, typename U, bool C>
		class ${data.className}Wrapper : public ${data.parent}Wrapper<T, U, C>
		{	
		public:
			template <bool M>
			${data.className}Wrapper(${data.className}Private<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ${data.parent}Wrapper(d, args) {
			}
			${data.className}Wrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ${data.parent}Wrapper(isolate, tpl)
			{
			}

		
			${data.className}Wrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ${data.parent}Wrapper(isolate, proto)
			{
				${props}
				${normal}
				${signals}
			}

		protected:
			${propsBodies}
			${normalBodies}
			${sginalBodies}
		};
	}
}`;
	writeFile(filename, code);

}
