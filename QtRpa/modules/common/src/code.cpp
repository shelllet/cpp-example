#include "common.hpp"
#include "common/code.h"


void shelllet::common::code::process_start(std::stringstream& stream)
{
	stream << "{";
}

void shelllet::common::code::process_end(std::stringstream& stream)
{
	stream << "}";
}

//std::string shelllet::activities::code::format(const std::string& js)
//{
//	v8::Isolate* isolate = (dynamic_cast<Aplication*>(juce::JUCEApplication::getInstance()))->get_isolate();
//	{
//		v8::TryCatch try_catch(isolate);
//		v8::Isolate::Scope isolate_scope(isolate);
//
//		// Create a stack-allocated handle scope.
//		v8::HandleScope handle_scope(isolate);
//
//		// Create a new context.
//		v8::Local<v8::Context> context = v8::Context::New(isolate);
//
//		// Enter the context for compiling and running the hello world script.
//		v8::Context::Scope context_scope(context);
//		v8::ScriptOrigin origin = make_script_origin("no", isolate);
//		{
//			// Create a string containing the JavaScript source code.
//
//			std::string src = R"(
//
//import * from 'C:/Users/Admin/Downloads/js-beautify-master/js/bin/js-beautify.js';
//
//var myCodeMirror = CodeMirror("let ddd  = 10")
//
////highlight('javascript', 'console.log(" sss ")'))";
//
//			v8::Local<v8::Module> module;
//			v8::ScriptCompiler::Source source_text(convert::String::New(isolate, src.c_str()), origin);
//
//			if (!v8::ScriptCompiler::CompileModule(isolate, &source_text).ToLocal(&module)) {
//				LOG_WARN(kMainModuleName) << *(v8::String::Utf8Value(isolate, try_catch.Exception())) << std::endl;
//				return js;
//			}
//
//			auto result = module->InstantiateModule(context, [](v8::Local<v8::Context> context, v8::Local<v8::String> specifier,
//				v8::Local<v8::Module> referrer)->v8::MaybeLocal<v8::Module> {
//					v8::String::Utf8Value param(context->GetIsolate(), specifier);
//					std::string filename = std::string(*param);
//
//					v8::Isolate* isolate = context->GetIsolate();
//
//					std::ifstream stream(filename);
//
//					std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
//
//					v8::ScriptOrigin origin = make_script_origin(filename.c_str(), context->GetIsolate());
//
//					v8::ScriptCompiler::Source source(convert::String::New(isolate, str.c_str()), origin);
//
//					return v8::ScriptCompiler::CompileModule(context->GetIsolate(), &source);
//				});
//
//			if (result.IsNothing()) {
//				LOG_WARN(kMainModuleName) << *(v8::String::Utf8Value(isolate, try_catch.Exception())) << std::endl;
//				return js;
//			}
//
//			v8::Local<v8::Value> value;
//
//			module->Evaluate(context).ToLocal(&value);
//
//			if (try_catch.HasCaught()) {
//				LOG_WARN(kMainModuleName) << *(v8::String::Utf8Value(isolate, try_catch.Exception())) << std::endl;
//				return js;
//			}
//			// Convert the result to an UTF8 string and print it.
//
//			return *(v8::String::Utf8Value(isolate, value));
//		}
//	}
//}
