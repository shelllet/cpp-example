#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, typename U, bool C>
		class QRCodeDetectorWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QRCodeDetectorWrapper(QRCodeDetectorPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QRCodeDetectorWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl)
			{
			}
			QRCodeDetectorWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "decode", v8::FunctionTemplate::New(isolate, Decode));
				proto->Set(isolate, "detectAndDecode", v8::FunctionTemplate::New(isolate, DetectAndDecode));
			}

		protected:
			static void Decode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QRCodeDetectorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					auto* image = Mat::From(args[0]);
					if (!image)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					auto* points = Mat::From(args[0]);
					if (!points)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					cv::OutputArray straight_qrcode = cv::noArray();
					auto retval = (*self)->decode(**image, **points, straight_qrcode);

					v8::Local<v8::Array> result = v8::Array::New(isolate, 2);
					result->Set(context, 0, V8_NEW_STRING_VAR(isolate, retval.c_str()));
					result->Set(context, 1, Mat::New(isolate, v8::External::New(isolate, &straight_qrcode.getMatRef())));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void DetectAndDecode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QRCodeDetectorWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto* image = Mat::From(args[0]);
					if (!image)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					cv::Mat points;
					cv::Mat straight_qrcode;

					auto retval = (*self)->detectAndDecode(**image, points, straight_qrcode);

					v8::Local<v8::Array> result = v8::Array::New(isolate, 3);
					result->Set(context, 0,V8_NEW_STRING_VAR(isolate, retval.c_str()));
					result->Set(context, 1, Mat::New2(isolate, new cv::Mat(points)));
					result->Set(context, 2, Mat::New2(isolate, new cv::Mat(straight_qrcode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}