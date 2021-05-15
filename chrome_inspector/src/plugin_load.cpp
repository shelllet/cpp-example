#include "framework.h"
#include "inspector_agent.h"
#include "native_library.h"
namespace shelllet {
	using namespace library;
	extern v8::Global<v8::Context> global_context;
}
bool shelllet::engine::InspectorAgent::loadModules(v8::Local<v8::Context> context)
{
	return global_native_library->initialize(isolate_, context);
}