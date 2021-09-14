#pragma once
namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QDirWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QDirWrapper(QDirPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QDirWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl)
			{
				auto filter = v8::FunctionTemplate::New(isolate);
				filter->Set(isolate, "Dirs", v8::Int32::New(isolate, QDir::Dirs));
				filter->Set(isolate, "Files", v8::Int32::New(isolate, QDir::Files));
				filter->Set(isolate, "AllDirs", v8::Int32::New(isolate, QDir::AllDirs));
				filter->Set(isolate, "NoDotAndDotDot", v8::Int32::New(isolate, QDir::NoDotAndDotDot));

				tpl->Set(isolate, "Filter", filter);
			}

			QDirWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
			}

		protected:
		};
	}
}