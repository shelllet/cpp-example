#pragma once
#include <qlibrary.h>
namespace shelllet {
	namespace library {
		class NativeLibrary {
		public:
			NativeLibrary() = default;
			~NativeLibrary();
			bool initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& global);

			static NativeLibrary* getInstance();

		private:
		};
	}
}