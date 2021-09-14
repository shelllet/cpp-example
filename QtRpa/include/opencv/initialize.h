#pragma once
#include "framework.h"
#include "qtcore/qpoint_implement.h"
#include "qtcore/qrect_implement.h"
#include "imgcodecs_implement.h"
#include "mat_implement.h"
#include "imgproc_implement.h"
#include "qrcodedetector_implement.h"

namespace shelllet {
	using namespace core;
	namespace opencv {
		void initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) {
			using namespace shelllet::opencv;
			proto->Set(isolate, Mat::Name(), Mat::WrapClass(isolate));
			proto->Set(isolate, QRCodeDetector::Name(), QRCodeDetector::WrapClass(isolate));
			{
				static_cast<void>(std::make_unique<ImgCodecs>(isolate, proto));
				static_cast<void>(std::make_unique<ImgProc>(isolate, proto));
			}

			proto->Set(isolate, "THRESH_BINARY", v8::Int32::New(isolate, cv::THRESH_BINARY));
			proto->Set(isolate, "THRESH_BINARY_INV", v8::Int32::New(isolate, cv::THRESH_BINARY_INV));
			proto->Set(isolate, "THRESH_TRUNC", v8::Int32::New(isolate, cv::THRESH_TRUNC));
			proto->Set(isolate, "THRESH_TOZERO", v8::Int32::New(isolate, cv::THRESH_TOZERO));
			proto->Set(isolate, "THRESH_TOZERO_INV", v8::Int32::New(isolate, cv::THRESH_TOZERO_INV));
			proto->Set(isolate, "THRESH_MASK", v8::Int32::New(isolate, cv::THRESH_MASK));
			proto->Set(isolate, "THRESH_OTSU", v8::Int32::New(isolate, cv::THRESH_OTSU));
			proto->Set(isolate, "THRESH_TRIANGLE", v8::Int32::New(isolate, cv::THRESH_TRIANGLE));

			proto->Set(isolate, "COLOR_RGB2GRAY", v8::Int32::New(isolate, cv::COLOR_RGB2GRAY));
		}
	}
}