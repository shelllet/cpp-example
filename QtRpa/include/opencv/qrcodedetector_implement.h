#pragma once
#include "framework.h"
#include <opencv2/objdetect.hpp>
#include "qrcodedetector_p.h"
#include "qrcodedetector_wrapper.h"

namespace shelllet {
	namespace opencv {
		class QRCodeDetector : public QRCodeDetectorWrapper<cv::QRCodeDetector, QRCodeDetector, true>
		{
			using ReturnType = QRCodeDetectorPrivate<cv::QRCodeDetector, true>;
			using ReturnType2 = QRCodeDetectorPrivate<cv::QRCodeDetector, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			QRCodeDetector(const v8::FunctionCallbackInfo<v8::Value>& args) :QRCodeDetectorWrapper(*Private(args), args)
			{
			}
			QRCodeDetector(cv::QRCodeDetector* p, const v8::FunctionCallbackInfo<v8::Value>& args) :QRCodeDetectorWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			QRCodeDetector(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QRCodeDetectorWrapper(isolate, tpl)
			{}
			QRCodeDetector(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QRCodeDetectorWrapper(isolate, proto)
			{
			}

		protected:
			void toString(std::stringstream& ss) const {}
		public:
			static const char* Name() { return "QRCodeDetector"; }
		protected:
		};
	}
}
