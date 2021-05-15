#pragma once
#include <qlibrary.h>
namespace shelllet {
	namespace library {
		class NativeLibrary {
		public:
			NativeLibrary() = default;
			~NativeLibrary();
			bool initialize(v8::Isolate* isolate, const v8::Local<v8::Context>& context);
			void cleanup();
		private:
			std::vector<std::unique_ptr<QLibrary>> libraries;
		};
		Q_GLOBAL_STATIC(NativeLibrary, global_native_library)
	}
}