#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, typename U, bool C>
		class ImgCodecsWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			ImgCodecsWrapper(ImgCodecsPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}

			ImgCodecsWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			ImgCodecsWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "imread", v8::FunctionTemplate::New(isolate, ImRead));
			}

		protected:
			static void ImRead(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					std::filesystem::path fixed = FixRelativePath(ToString({ isolate, args[0] }), args.GetIsolate());
					if (!std::filesystem::exists(fixed)) {
						LOG_FATAL("v8") << "# `" << fixed << "` not exist." << std::endl;
					}
					int flags = args[1]->Int32Value(context).FromMaybe(cv::IMREAD_COLOR);
					cv::Mat img = cv::imread(fixed.string(), flags);
					args.GetReturnValue().Set(Mat::New2(isolate, new cv::Mat(img)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
