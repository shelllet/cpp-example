#pragma once
namespace shelllet {
	namespace gui {
		template<typename T, typename U, bool C>
		class QPaintDeviceWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QPaintDeviceWrapper(QPaintDevicePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QPaintDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QPaintDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
				{
					v8::Local<v8::ObjectTemplate> paintDeviceMetric = v8::ObjectTemplate::New(isolate);
					paintDeviceMetric->Set(isolate, "PdmWidth", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmWidth));
					paintDeviceMetric->Set(isolate, "PdmHeight", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmHeight));
					paintDeviceMetric->Set(isolate, "PdmWidthMM", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmWidthMM));
					paintDeviceMetric->Set(isolate, "PdmHeightMM", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmHeightMM));
					paintDeviceMetric->Set(isolate, "PdmNumColors", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmNumColors));
					paintDeviceMetric->Set(isolate, "PdmDepth", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmDepth));
					paintDeviceMetric->Set(isolate, "PdmDpiX", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmDpiX));
					paintDeviceMetric->Set(isolate, "PdmDpiY", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmDpiY));
					paintDeviceMetric->Set(isolate, "PdmPhysicalDpiX", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmPhysicalDpiX));
					paintDeviceMetric->Set(isolate, "PdmPhysicalDpiY", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmPhysicalDpiY));
					paintDeviceMetric->Set(isolate, "PdmDevicePixelRatio", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmDevicePixelRatio));
					paintDeviceMetric->Set(isolate, "PdmDevicePixelRatioScaled", v8::Int32::New(isolate, QPaintDevice::PaintDeviceMetric::PdmDevicePixelRatioScaled));
					tpl->Set(isolate, "PaintDeviceMetric", paintDeviceMetric);
				}
				{
					tpl->PrototypeTemplate()->Set(isolate, "paintingActive", v8::FunctionTemplate::New(isolate, PaintingActive));
					tpl->PrototypeTemplate()->Set(isolate, "width", v8::FunctionTemplate::New(isolate, Width));
					tpl->PrototypeTemplate()->Set(isolate, "height", v8::FunctionTemplate::New(isolate, Height));
					tpl->PrototypeTemplate()->Set(isolate, "widthMM", v8::FunctionTemplate::New(isolate, WidthMM));
					tpl->PrototypeTemplate()->Set(isolate, "heightMM", v8::FunctionTemplate::New(isolate, HeightMM));
					tpl->PrototypeTemplate()->Set(isolate, "logicalDpiX", v8::FunctionTemplate::New(isolate, LogicalDpiX));
					tpl->PrototypeTemplate()->Set(isolate, "logicalDpiY", v8::FunctionTemplate::New(isolate, LogicalDpiY));
					tpl->PrototypeTemplate()->Set(isolate, "physicalDpiX", v8::FunctionTemplate::New(isolate, PhysicalDpiX));
					tpl->PrototypeTemplate()->Set(isolate, "physicalDpiY", v8::FunctionTemplate::New(isolate, PhysicalDpiY));
					tpl->PrototypeTemplate()->Set(isolate, "devicePixelRatio", v8::FunctionTemplate::New(isolate, DevicePixelRatio));
					tpl->PrototypeTemplate()->Set(isolate, "colorCount", v8::FunctionTemplate::New(isolate, ColorCount));
					tpl->PrototypeTemplate()->Set(isolate, "depth", v8::FunctionTemplate::New(isolate, Depth));
					tpl->PrototypeTemplate()->Set(isolate, "metric", v8::FunctionTemplate::New(isolate, Metric));
				}
			}

		protected:
			static void PaintingActive(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->paintingActive());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Width(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->width());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Height(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->height());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WidthMM(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->widthMM());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HeightMM(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->heightMM());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LogicalDpiX(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->logicalDpiX());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LogicalDpiY(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->logicalDpiY());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PhysicalDpiX(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->physicalDpiX());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PhysicalDpiY(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->physicalDpiY());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DevicePixelRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Number::New(isolate, (*p)->devicePixelRatioF());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ColorCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->colorCount());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Depth(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->depth());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Metric(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPaintDeviceWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto metric = static_cast<QPaintDevice::PaintDeviceMetric>(args[0]->Int32Value(context).FromJust());
					//auto result = v8::Int32::New(isolate, dynamic_cast<QPaintDevicePrivate<T, true>*>(*p)->metric(metric));
				//	args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
