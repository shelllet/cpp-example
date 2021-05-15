#include "framework.h"
#include "native_library.h"
#include "options_manager.h"
namespace shelllet {
	typedef void (*Initialize)(v8::Isolate*, const v8::Local<v8::ObjectTemplate>&);
	typedef const char* (*Name)();
}
bool shelllet::library::NativeLibrary::initialize(v8::Isolate* isolate, const v8::Local<v8::Context>& context)
{
	std::filesystem::path exe = options::options_manager::get_const_instance().options.modules_path;
	try
	{
		for (auto& p : std::filesystem::directory_iterator(exe))
		{
			if (!p.is_regular_file())
				continue;
			auto& path = p.path();
			LOG_DEBUG("engine") << "# modules: " << path;
			if (path.extension() != options::options_manager::get_const_instance().options.extension)
				continue;

			std::unique_ptr< QLibrary> lib = std::make_unique<QLibrary>(QString::fromStdString(path.string()));
			v8::Local<v8::ObjectTemplate> proto = v8::ObjectTemplate::New(isolate);

			if (!lib->load()) {
				//	qCDebug(shelllet_engine) << "# initialize " << library->fileName();
				return false;
			}
			auto initialize = (Initialize)lib->resolve("initialize");
			if (!initialize) {
				return false;
			}
			initialize(isolate, proto);

			auto instance = proto->NewInstance(context);
			if (instance.IsEmpty()) {
				return false;
			}
			auto name = (Name)lib->resolve("name");

			if (auto result = context->Global()->Set(context, V8_NEW_STRING_VAR(isolate, name()), instance.ToLocalChecked()); result.IsNothing())
				return false;

			libraries.push_back(std::move(lib));
		}
	}
	catch (const std::exception& err)
	{
		LOG_WARN("engine") << "# modules loaded: " << QString::fromLocal8Bit(err.what()).toStdString() << std::endl;
	}
	return true;
}

void shelllet::library::NativeLibrary::cleanup()
{
	for (auto& lib : libraries)
	{
		typedef void (*CleanupFunction)();
		CleanupFunction cleanup = nullptr;

		if (lib->isLoaded()) {
			auto cleanup = (CleanupFunction)lib->resolve("cleanup");
			if (cleanup) {
				cleanup();
			}
			lib->unload();
		}
	}
}

shelllet::library::NativeLibrary::~NativeLibrary()
{
	cleanup();
}