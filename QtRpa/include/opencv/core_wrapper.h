#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, typename U, bool C>
		class CoreWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			CoreWrapper(CorePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}

			CoreWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			CoreWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "minMaxLoc", v8::FunctionTemplate::New(isolate, minMaxLoc));
			}

		protected:
			static void minMaxLoc(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* src = Mat::From(args[0]);
					if (!src)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					int flags = cv::IMREAD_COLOR;
					cv::InputArray mask = cv::noArray();

					if (args.Length() > 1) {
						mask = **Mat::From(args[1]);
					}
					double minVal, maxVal, minLoc, maxLoc;
					cv::minMaxLoc(**src, &minVal, &maxVal, &minLoc, &maxLoc, mask);

					v8::Local<v8::Array> result = v8::Array::New(isolate, 4);
					result->Set(context, 0, v8::Number::New(isolate, minVal));
					result->Set(context, 1, v8::Number::New(isolate, maxVal));
					result->Set(context, 2, v8::Number::New(isolate, minLoc));
					result->Set(context, 3, v8::Number::New(isolate, maxLoc));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
