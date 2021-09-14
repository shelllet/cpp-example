#pragma once
namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QDirIteratorWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QDirIteratorWrapper(QDirIteratorPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QDirIteratorWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl)
			{
			}

			QDirIteratorWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "fileInfo", v8::FunctionTemplate::New(isolate, FileInfo));
				proto->Set(isolate, "fileName", v8::FunctionTemplate::New(isolate, FileName));
				proto->Set(isolate, "filePath", v8::FunctionTemplate::New(isolate, FilePath));
				proto->Set(isolate, "hasNext", v8::FunctionTemplate::New(isolate, HasNext));
				proto->Set(isolate, "next", v8::FunctionTemplate::New(isolate, Next));
				proto->Set(isolate, "path", v8::FunctionTemplate::New(isolate, Path));
			}

		protected:

			static void FileInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FileName(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto retval = (*self)->fileName().toUtf8();
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, retval.constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FilePath(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto retval = (*self)->filePath().toUtf8();
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, retval.constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasNext(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set((*self)->hasNext());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Next(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto retval = (*self)->next().toUtf8();
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, retval.constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Path(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QDirIteratorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto retval = (*self)->path().toUtf8();
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, retval.constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}