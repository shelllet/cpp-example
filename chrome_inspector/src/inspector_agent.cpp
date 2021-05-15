#include <qevent.h>
#include <qapplication.h>
#include "framework.h"
#include "inspector_agent.h"
#include "native/global_implement.h"
#include "native/console_implement.h"
#include "qtcore/initialize.h"
#include "qtgui/initialize.h"
#include "opencv/initialize.h"
#include "native_library.h"
namespace shelllet {
	static v8::ScriptOrigin NewScriptOrigin(const char* resourceName, v8::Isolate* isolate) {
		return { V8_NEW_STRING_VAR(isolate, resourceName),
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
	using namespace engine;
	using namespace inspect;
	using namespace library;
	v8::Global<v8::Context> global_context;
}

void shelllet::engine::InspectorAgent::disconnectInspector()
{
	if (inspector_client_)
		inspector_client_->disconnectFrontend();
}

void shelllet::engine::InspectorAgent::postInspectorMessage(const QString& message)
{
	inspector_client_->postInspectorMessage(message.toStdString());
}

void shelllet::engine::InspectorAgent::pumpMessageLoop()
{
	if (inspector_client_)
		inspector_client_->pumpMessageLoop();
}

shelllet::engine::InspectorAgent::InspectorAgent(QObject* receiver, v8::Platform* platform, const std::string& filename, const std::string& source, const std::string& dir, bool inspect_brk)
	: receiver_(receiver)
	, platform_(platform)
	, name_(filename)
	, code_(source)
	, dir_(dir)
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

void shelllet::engine::InspectorAgent::evaluate()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	v8::TryCatch try_catch(isolate_);
	v8::Local<v8::Context> context = v8::Local<v8::Context>::New(isolate_, global_context);
	v8::Context::Scope context_scope(context);

	v8::ScriptOrigin origin = NewScriptOrigin(name_.c_str(), isolate_);
	v8::ScriptCompiler::Source sourceText(V8_NEW_STRING_VAR(isolate_, code_.c_str()), origin);

	v8::Local<v8::Module> module;

	if (!v8::ScriptCompiler::CompileModule(isolate_, &sourceText).ToLocal(&module) && try_catch.HasCaught()) {
		LOG_ERROR("engine") << GetException(isolate_, try_catch);
		return;
	}
	if (!module->InstantiateModule(context, [](v8::Local<v8::Context> context,
		v8::Local<v8::String> specifier,
		v8::Local<v8::Module> referrer)->v8::MaybeLocal<v8::Module> {
			v8::String::Utf8Value param(context->GetIsolate(), specifier);
			std::string filename = std::string(*param);
			v8::Isolate* isolate = context->GetIsolate();
			v8::TryCatch tryCatch(isolate);

			v8::String::Utf8Value u8(isolate, context->GetEmbedderData(static_cast<int>(ContextEmbedderData::WorkingDirectory)));
			std::filesystem::path path = std::filesystem::path(*u8).append(filename).lexically_normal();

			std::ifstream ifs(path);
			std::string code((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

			v8::ScriptOrigin origin = NewScriptOrigin(filename.c_str(), context->GetIsolate());
			v8::ScriptCompiler::Source source(V8_NEW_STRING_VAR(isolate, code.c_str()), origin);
			v8::MaybeLocal<v8::Module> result = v8::ScriptCompiler::CompileModule(context->GetIsolate(), &source);

			if (tryCatch.HasCaught()) {
				LOG_WARN("engine") << GetException(isolate, tryCatch);
				v8::ScriptCompiler::Source source(V8_NEW_STRING_VAR(isolate, ""), origin);
				return v8::ScriptCompiler::CompileModule(context->GetIsolate(), &source);
			}
			return result;
		}).IsNothing()) {
		module->Evaluate(context);
	}

	if (try_catch.HasCaught()) {
		LOG_ERROR("engine") << GetException(isolate_, try_catch);
	}
}

void shelllet::engine::InspectorAgent::run()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	v8::TryCatch try_catch(isolate_);
	{
		v8::Local<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(isolate_);
		{
			static_cast<void>(std::make_unique<Global>(isolate_, objectTemplate));
			qtcore::initialize(isolate_, objectTemplate);
		}

		v8::Local<v8::Context> context = v8::Context::New(isolate_, nullptr, objectTemplate);
		context->SetEmbedderData(static_cast<int>(ContextEmbedderData::WorkingDirectory), V8_NEW_STRING_VAR(isolate_, dir_.c_str()));

		v8::Context::Scope contextScope(context);

		{
			context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, Console::Name()), Console::WrapClass(isolate_)->GetFunction(context).ToLocalChecked());
		}

		// opencv
		{
			v8::Local<v8::ObjectTemplate> proto = v8::ObjectTemplate::New(isolate_);
			opencv::initialize(isolate_, proto);

			auto instance = proto->NewInstance(context);

			if (auto result = context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, "cv"), instance.ToLocalChecked()); result.IsNothing()) {
				LOG_ERROR("v8") << GetException(isolate_, try_catch);
				return;
			}
		}
		{
			v8::Local<v8::Array> args = v8::Array::New(isolate_, __argc);
			for (int i = 0; i < __argc; ++i) {
				args->Set(context, i, V8_NEW_STRING_VAR(isolate_, __argv[i]));
			}
			context->Global()->Set(context, V8_NEW_STRING_VAR(isolate_, "arguments"), args);
		}
		if (!loadModules(context) && try_catch.HasCaught()) {
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

void shelllet::engine::InspectorAgent::cleanup()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	if (inspect_brk_) {
		disconnectInspector();
	}

	global_native_library->cleanup();
#ifdef _DEBUG
	isolate_->RequestGarbageCollectionForTesting(v8::Isolate::kFullGarbageCollection);
#endif // _DEBUG

	global_context.Reset();
}