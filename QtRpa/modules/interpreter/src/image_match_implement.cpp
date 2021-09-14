//#include "framework.h"
//#include "context_module.h"
//#include "v8_object_wrapped.h"
//#include "image_wrapped.h"
//
//namespace shelllet {
//	const int kMax = 0xff;
//	static std::list<QRect> MatchingMethod(const cv::Mat& m1, const cv::Mat& tm, double threshold, std::uint32_t match_method, std::uint8_t max)
//	{
//		int result_cols = m1.cols - tm.cols + 1;
//		int result_rows = m1.rows - tm.rows + 1;
//
//		cv::Mat result;
//		result.create(result_rows, result_cols, CV_32FC1);
//
//		cv::matchTemplate(m1, tm, result, match_method);
//		std::list<QRect> rects;
//
//		if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED)
//		{
//			//cv::threshold(result, result, threshold, 0, THRESH_TOZERO_INV);
//
//			while (true)
//			{
//				double min_value;
//				cv::Point min_loc;
//
//				minMaxLoc(result, &min_value, 0, &min_loc, 0);
//
//				if (min_value <= threshold) {
//					floodFill(result, min_loc, cv::Scalar(1), 0, cv::Scalar(0), cv::Scalar(0));
//					rects.push_back({ min_loc.x, min_loc.y , tm.cols, tm.rows });
//					if (rects.size() >= max || rects.size() >= kMax) // avoid dead loop
//						break;
//				}
//				else {
//					break;
//				}
//			}
//
//			return rects;
//		}
//
//		// cv::threshold(result, result, threshold, 0, cv::THRESH_TOZERO);
//
//		while (true) {
//			double max_value;
//			cv::Point max_loc;
//			minMaxLoc(result, 0, &max_value, 0, &max_loc);
//
//			if (max_value >= threshold) {
//				floodFill(result, max_loc, cv::Scalar(0), 0, cv::Scalar(), cv::Scalar());
//				rects.push_back({ max_loc.x, max_loc.y,	tm.cols, tm.rows });
//				if (rects.size() >= max || rects.size() >= kMax)
//					break;
//			}
//			else {
//				break;
//			}
//		}
//
//		return rects;
//	}
//}
//
//std::list<QRect> shelllet::image::Image::match(const cv::Mat& tpl, double threshold, int method, int max)
//{
//	cv::Mat grey;
//	cv::Mat grey_template;
//
//	//	cvtColor(image_, grey, cv::COLOR_BGR2GRAY);
//	cvtColor(tpl, grey_template, cv::COLOR_BGR2GRAY);
//
//	return MatchingMethod(grey, grey_template, threshold, method, max);
//}
//
//void shelllet::image::Image::Match(const v8::FunctionCallbackInfo<v8::Value>& args)
//{
//	V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
//	{
//		cv::Mat template_image;
//
//		if (args.Length() < 1 || !args[0]->IsString()) {
//			//THROW_EXCEPTION_VAR(isolate, CONTEXT_CAST(isolate)->getLanguageText("plugin.l1").c_str());
//			return;
//		}
//
//		v8::String::Utf8Value value(isolate, args[0]);
//		if (std::filesystem::exists(std::filesystem::path(*value))) {
//			try
//			{
//				template_image = cv::imread(*value);
//			}
//			catch (const cv::Exception& exception)
//			{
//				//THROW_EXCEPTION_VAR(isolate, exception.msg.c_str());
//				return;
//			}
//		}
//		else {
//			//auto& images = CONTEXT_CAST(isolate)->getModel()->images;
//		}
//		//auto itor = images.find(*value);
//		//if (itor == images.end()) {
//			//boost::format format = boost::format(CONTEXT_CAST(isolate)->getLanguageText("model.image.l1").c_str()) % *value;
//			//THROW_EXCEPTION_VAR(isolate, format.str().c_str());
//		//	return;
//	//	}
//	//	else {
//		try
//		{
//			//	template_image = cv::imdecode(cv::Mat(1, static_cast<int>(itor->second.size()), CV_8UC1, itor->second.data()), cv::IMREAD_UNCHANGED);
//		}
//		catch (const cv::Exception& exception)
//		{
//			//THROW_EXCEPTION_VAR(isolate, exception.msg.c_str());
//			return;
//		}
//		//}
//
//		if (template_image.empty()) {
//			//THROW_EXCEPTION_VAR(isolate, CONTEXT_CAST(isolate)->getLanguageText("image.l1").c_str());
//			return;
//		}
//
//		double threshold = 1.0;
//		std::uint32_t method = cv::TM_CCORR_NORMED;
//		std::uint8_t max = 1;
//
//		if (args.Length() > 1 && args[1]->IsNumber())
//		{
//			threshold = args[1]->NumberValue(isolate->GetCurrentContext()).FromJust();
//		}
//
//		if (args.Length() > 2 && args[2]->IsUint32())
//		{
//			method = args[2]->Uint32Value(isolate->GetCurrentContext()).FromJust();
//		}
//
//		if (args.Length() > 3 && args[3]->IsUint32())
//		{
//			max = args[3]->Uint32Value(isolate->GetCurrentContext()).FromJust();
//		}
//
//		Image* image = UnWrap<Image>(args.This());
//
//		std::list<QRect> rects = image->match(template_image, threshold, method, max);
//
//		v8::Local< v8::Array> array = v8::Array::New(isolate, rects.size());
//		int i = 0;
//
//		while (!rects.empty())
//		{
//			auto& rc = rects.front();
//			v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, rc.x()),
//				v8::Int32::New(isolate, rc.y()),
//				v8::Int32::New(isolate, rc.width()),
//				v8::Int32::New(isolate, rc.height())
//			};
//			array->Set(context, i++, Wrap(isolate, context, "Rect", std::size(argv), argv));
//			rects.pop_front();
//		}
//
//		args.GetReturnValue().Set(array);
//	}
//}