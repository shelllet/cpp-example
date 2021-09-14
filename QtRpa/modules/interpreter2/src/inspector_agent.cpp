#include "common.hpp"
#include <qevent.h>
#include <qapplication.h>
#include <libzippp/libzippp.h>
#include "interpreter/error.h"
#include "interpreter/inspector_agent.h"
#include "interpreter/global/global_implement.h"
#include "interpreter/global/console_implement.h"
//#include "modules/core/initialize.h"
//#include "modules/gui/initialize.h"
//#include "opencv/initialize.h"
#include "interpreter/native_library.h"
#include "properties.hpp"
namespace shelllet {
	static v8::ScriptOrigin NewScriptOrigin(const std::string& resourceName, v8::Isolate* isolate) {
		return { V8_NEW_STRING_VAR(isolate, resourceName.c_str()),
			v8::Integer::New(isolate, 0),
			v8::Integer::New(isolate, 0),
			v8::False(isolate),
			v8::Local<v8::Integer>(),
			v8::Local<v8::Value>(),
			False(isolate),
			False(isolate),
			True(isolate)
		};
	}

	using namespace global;
	using namespace interpreter;
	using namespace inspect;
	using namespace library;
	using namespace pugi;
	v8::Global<v8::Context> global_context;
	static void WalkCodeCall(std::ostringstream& ss, const xml_object_range<xml_node_iterator>& items) {
		for (const auto& i : items) {

			auto prop = CompositeProperty::CreateNode(i);

			if (prop) {
				prop->getCode(ss);
			}
			ss << std::endl;


			WalkCodeCall(ss, i.children());
		}
	}

}

void shelllet::interpreter::InspectorAgent::disconnectInspector()
{
	if (inspector_client_)
		inspector_client_->disconnectFrontend();
}

void shelllet::interpreter::InspectorAgent::postInspectorMessage(const QString& message)
{
	inspector_client_->postInspectorMessage(message.toStdString());
}

void shelllet::interpreter::InspectorAgent::pumpMessageLoop()
{
	if (inspector_client_)
		inspector_client_->pumpMessageLoop();
}

shelllet::interpreter::InspectorAgent::InspectorAgent(QObject* receiver, v8::Platform* platform, const std::filesystem::path& filename, bool inspect_brk)
	: receiver_(receiver)
	, platform_(platform)
	, filename_(filename)
	, inspect_brk_(inspect_brk)
{
	create_params_.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

	isolate_ = v8::Isolate::New(create_params_);
	isolate_->SetData(static_cast<uint32_t>(IsolateData::GlobalContext), &global_context);
	//isolate->SetData(static_cast<uint32_t>(IsolateData::GlobalValue), &resources);
	isolate_->SetData(static_cast<uint32_t>(IsolateData::SetErrorAddress), error::SetLastErrorMessage);
}

shelllet::InspectorAgent::~InspectorAgent()
{
	{
		v8::Locker locker(isolate_);
		v8::Isolate::Scope isolate_scope(isolate_);
		v8::HandleScope handle_scope(isolate_);
		while (v8::platform::PumpMessageLoop(platform_, isolate_)) {
			QCoreApplication::processEvents();
		}
		inspector_client_.reset(nullptr);
	}
	isolate_->Dispose();

	delete create_params_.array_buffer_allocator;
}

void shelllet::interpreter::InspectorAgent::evaluate()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	v8::TryCatch try_catch(isolate_);
	v8::Local<v8::Context> context = v8::Local<v8::Context>::New(isolate_, global_context);
	v8::Context::Scope context_scope(context);

	v8::ScriptOrigin origin = NewScriptOrigin(filename_.string(), isolate_);
	v8::ScriptCompiler::Source sourceText(V8_NEW_STRING_VAR(isolate_, translate(index_code_).c_str()), origin);

	v8::Local<v8::Module> js_module;

	if (!v8::ScriptCompiler::CompileModule(isolate_, &sourceText).ToLocal(&js_module) && try_catch.HasCaught()) {
		LOG_ERROR("engine") << GetException(isolate_, try_catch);
		return;
	}
	if (!js_module->InstantiateModule(context, [](v8::Local<v8::Context> context,
		v8::Local<v8::String> specifier,
		v8::Local<v8::Module> referrer)->v8::MaybeLocal<v8::Module> {
		v8::String::Utf8Value param(context->GetIsolate(), specifier);
		std::string filename = *param;
		v8::Isolate* isolate = context->GetIsolate();
		v8::TryCatch tryCatch(isolate);
		std::string code;
		if (context->GetEmbedderData(static_cast<int>(ContextEmbedderData::IsZip))->BooleanValue(isolate))
		{
			v8::String::Utf8Value u8(isolate, context->GetEmbedderData(static_cast<int>(ContextEmbedderData::ZipSource)));
			std::filesystem::path path = std::filesystem::path(*u8).append(filename).lexically_normal();

			libzippp::ZipArchive zf(path.string());

			zf.open(libzippp::ZipArchive::ReadOnly);

			libzippp::ZipEntry entry2 = zf.getEntry(common::Environment::getInstance()->getOptions()->pkg_src.toStdString() + filename);
			code = entry2.readAsText();
		}
		else {
			v8::String::Utf8Value u8(isolate, context->GetEmbedderData(static_cast<int>(ContextEmbedderData::WorkingDirectory)));
			std::filesystem::path path = std::filesystem::path(*u8).append(filename).lexically_normal();

			std::ifstream ifs(path);
			code = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
		}

		v8::ScriptOrigin origin = NewScriptOrigin(filename, context->GetIsolate());
		v8::ScriptCompiler::Source source(V8_NEW_STRING_VAR(isolate, translate(code).c_str()), origin);
		v8::MaybeLocal<v8::Module> result = v8::ScriptCompiler::CompileModule(context->GetIsolate(), &source);

		if (tryCatch.HasCaught()) {
			LOG_WARN("engine") << GetException(isolate, tryCatch);
			v8::ScriptCompiler::Source source(V8_NEW_STRING_VAR(isolate, ""), origin);
			return v8::ScriptCompiler::CompileModule(context->GetIsolate(), &source);
		}
		return result;
	}).IsNothing()) {
		auto value = js_module->Evaluate(context);
		if (auto tmp = value.ToLocalChecked())
		{
			v8::Local<v8::Function> f;
			f->IsAsyncFunction();
			v8::Isolate::wai

		}
	}

	if (try_catch.HasCaught()) {
		LOG_ERROR("engine") << GetException(isolate_, try_catch);
	}
}

std::string shelllet::InspectorAgent::translate(const std::string& xml)
{

	std::ostringstream ss;
	xml_document doc;
	doc.load_string(xml.c_str());

	//ss << "await (async () => {" << std::endl;

	//WalkCodeCall(ss, doc.document_element().children());

	//ss << "})();" << std::endl;

	ss << R"(await (async () =>{})())";
	LOG_TRACE("Velkhana") << "# generate code: " << std::endl
		<< ss.str();
	return ss.str();
}

void shelllet::interpreter::InspectorAgent::run()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	v8::TryCatch try_catch(isolate_);

	std::filesystem::path src = filename_;
	std::filesystem::path dir = src.parent_path();
	if (std::filesystem::is_directory(src)) {
		dir = src;
		src /= "src/index.xml";
	}

	std::string name = src.filename().string();

	bool is_zip = false;
	if (src.extension() == common::Environment::getInstance()->getOptions()->pkg_extension.toStdWString()) {
		libzippp::ZipArchive zf(src.string());
		zf.open(libzippp::ZipArchive::ReadOnly);

		libzippp::ZipEntry entry2 = zf.getEntry(common::Environment::getInstance()->indexJsPath().string());
		index_code_ = entry2.readAsText();
		is_zip = true;
	}
	else {
		std::ifstream stream(src);
		index_code_ = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

	}

	{
		v8::Local<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(isolate_);
		{
			static_cast<void>(std::make_unique<Global>(isolate_, objectTemplate));
			//	qtcore::initialize(isolate_, objectTemplate);
			NativeLibrary::getInstance()->initialize(isolate_, objectTemplate);
		}

		v8::Local<v8::Context> context = v8::Context::New(isolate_, nullptr, objectTemplate);
		context->SetEmbedderData(static_cast<int>(ContextEmbedderData::WorkingDirectory), V8_NEW_STRING_VAR(isolate_, dir.string().c_str()));
		context->SetEmbedderData(static_cast<int>(ContextEmbedderData::IsZip), v8::Boolean::New(isolate_, is_zip));
		context->SetEmbedderData(static_cast<int>(ContextEmbedderData::ZipSource), V8_NEW_STRING_VAR(isolate_, filename_.string().c_str()));

		v8::Context::Scope contextScope(context);

		{
			context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, Console::Name()), Console::WrapClass(isolate_)->GetFunction(context).ToLocalChecked());
		}

		//// opencv
		//{
		//	v8::Local<v8::ObjectTemplate> proto = v8::ObjectTemplate::New(isolate_);
		//	opencv::initialize(isolate_, proto);

		//	auto instance = proto->NewInstance(context);

		//	if (auto result = context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, "cv"), instance.ToLocalChecked()); result.IsNothing()) {
		//		LOG_ERROR("v8") << GetException(isolate_, try_catch);
		//		return;
		//	}
		//}
		{
			v8::Local<v8::Array> args = v8::Array::New(isolate_, __argc);
			for (int i = 0; i < __argc; ++i) {
				args->Set(context, i, V8_NEW_STRING_VAR(isolate_, __argv[i]));
			}
			context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, "arguments"), args);
		}
		if (try_catch.HasCaught()) {
			LOG_ERROR("engine") << GetException(isolate_, try_catch);
			return;
		}
		global_context.Reset(isolate_, context);
	}

	if (inspect_brk_) {
		inspector_client_.reset(new InspectorClient(receiver_, global_context.Get(isolate_), platform_));
		isolate_->RequestInterrupt([](v8::Isolate* isolate, void* data) {
			InspectorAgent* agent = static_cast<InspectorAgent*>(data);
			agent->pumpMessageLoop();
		}, this);
	}
	else {
		QCoreApplication::postEvent(receiver_, new ContinueRunEvent);
	}
}

void shelllet::interpreter::InspectorAgent::cleanup()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	if (inspect_brk_) {
		disconnectInspector();
	}

#ifdef _DEBUG
	isolate_->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
#endif // _DEBUG

	global_context.Reset();
}