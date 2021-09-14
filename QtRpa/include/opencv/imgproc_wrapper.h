#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, typename U, bool C>
		class ImgProcWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			ImgProcWrapper(ImgProcPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}

			ImgProcWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			ImgProcWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "threshold", v8::FunctionTemplate::New(isolate, Threshold));
				proto->Set(isolate, "cvtColor", v8::FunctionTemplate::New(isolate, CvtColor));
				proto->Set(isolate, "matchTemplate", v8::FunctionTemplate::New(isolate, MatchTemplate));
				proto->Set(isolate, "floodFill", v8::FunctionTemplate::New(isolate, FloodFill));
			}

		protected:
			static void Threshold(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					Mat* src = Mat::From(args[0]);
					if (!src)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					cv::Mat dst;
					double thresh = args[1]->NumberValue(context).FromJust();
					double maxval = args[2]->NumberValue(context).FromJust();
					int type = args[3]->Int32Value(context).FromJust();
					double retval = cv::threshold(**src, dst, thresh, maxval, type);
					v8::Local<v8::Array> result = v8::Array::New(isolate, 2);
					result->Set(context, 0, v8::Number::New(isolate, retval));
					result->Set(context, 1, Mat::New2(isolate, new cv::Mat(dst)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void CvtColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* src = Mat::From(args[0]);
					if (!src)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					cv::Mat dst;
					int code, dstCn = 0;
					code = args[1]->Int32Value(context).FromJust();
					dstCn = args[2]->Int32Value(context).FromMaybe(dstCn);

					cv::cvtColor(**src, dst, code, dstCn);

					args.GetReturnValue().Set(Mat::New2(isolate, new cv::Mat(dst)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void MatchTemplate(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* image = Mat::From(args[0]);
					if (!image)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto* templ = Mat::From(args[1]);
					if (!templ)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					cv::Mat result;
					int method;
					method = args[2]->Int32Value(context).FromJust();

					cv::matchTemplate(**image, **templ, result, method);

					args.GetReturnValue().Set(Mat::New(isolate, v8::External::New(isolate, &result)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void FloodFill(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* image = Mat::From(args[0]);
					if (!image)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					int index = 1;
					auto* mask = Mat::From(args[index]);
					if (mask) {
						index++;
					}

					auto* seed = Point::From(args[index++]);
					auto newVal = Scalar::From(args[index++]);
					auto loDiff = Scalar::From(args[index++]);
					auto upDiff = Scalar::From(args[index++]);
					int flags = args[index++]->Int32Value(context).FromMaybe(4);
					cv::Rect rect;

					if (mask) {
						int n = cv::floodFill(**image, **mask, { (*seed)->x(), (*seed)->y() }, **newVal, &rect, **loDiff, **upDiff, flags);
						v8::Local<v8::Array> result = v8::Array::New(isolate, 4);
						result->Set(context, 0, v8::Int32::New(isolate, n));
						result->Set(context, 1, Mat::New(isolate, v8::External::New(isolate, *image)));
						result->Set(context, 2, Mat::New(isolate, v8::External::New(isolate, *mask)));
						result->Set(context, 3, Rect::New(isolate, v8::Int32::New(isolate, rect.x), v8::Int32::New(isolate, rect.y), v8::Int32::New(isolate, rect.width), v8::Int32::New(isolate, rect.height)));
						args.GetReturnValue().Set(result);
					}
					else {
						int n = cv::floodFill(**image, { (*seed)->x(), (*seed)->y() }, **newVal, &rect, **loDiff, **upDiff, flags);
						v8::Local<v8::Array> result = v8::Array::New(isolate, 4);
						result->Set(context, 0, v8::Int32::New(isolate, n));
						result->Set(context, 1, Mat::New(isolate, v8::External::New(isolate, *image)));
						result->Set(context, 2, Rect::New(isolate, v8::Int32::New(isolate, rect.x), v8::Int32::New(isolate, rect.y), v8::Int32::New(isolate, rect.width), v8::Int32::New(isolate, rect.height)));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
