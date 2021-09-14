#pragma once
namespace shelllet::gui {
	template<typename T, typename U, bool C>
	class QColorWrapper : public ObjectWrapper<T, U, C>
	{
	public:

		template<bool M>
		QColorWrapper(QColorPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
			: ObjectWrapper(d, args)
		{
		}
		QColorWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
		QColorWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
			tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "red"), Red, SetRed);
			tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "green"), Green, SetGreen);
			tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "blue"), Blue, SetBlue);
			tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "alpha"), Alpha, SetAlpha);

			tpl->PrototypeTemplate()->Set(isolate, "black", v8::FunctionTemplate::New(isolate, Black));
			tpl->PrototypeTemplate()->Set(isolate, "convertTo", v8::FunctionTemplate::New(isolate, ConvertTo));
			tpl->PrototypeTemplate()->Set(isolate, "cyan", v8::FunctionTemplate::New(isolate, Cyan));
			tpl->PrototypeTemplate()->Set(isolate, "darker", v8::FunctionTemplate::New(isolate, Darker));
			tpl->PrototypeTemplate()->Set(isolate, "fromCmyk", v8::FunctionTemplate::New(isolate, FromCmyk));
			tpl->PrototypeTemplate()->Set(isolate, "fromHsl", v8::FunctionTemplate::New(isolate, FromHsl));
			tpl->PrototypeTemplate()->Set(isolate, "fromHsv", v8::FunctionTemplate::New(isolate, FromHsv));
			tpl->PrototypeTemplate()->Set(isolate, "fromRgb", v8::FunctionTemplate::New(isolate, FromRgb));
			tpl->PrototypeTemplate()->Set(isolate, "fromRgba", v8::FunctionTemplate::New(isolate, FromRgba));
			tpl->PrototypeTemplate()->Set(isolate, "fromRgba64", v8::FunctionTemplate::New(isolate, FromRgba64));

			tpl->PrototypeTemplate()->Set(isolate, "hslHue", v8::FunctionTemplate::New(isolate, HslHue));
			tpl->PrototypeTemplate()->Set(isolate, "hslSaturation", v8::FunctionTemplate::New(isolate, HslSaturation));
			tpl->PrototypeTemplate()->Set(isolate, "hsvHue", v8::FunctionTemplate::New(isolate, HsvHue));
			tpl->PrototypeTemplate()->Set(isolate, "hsvSaturation", v8::FunctionTemplate::New(isolate, HsvSaturation));
			tpl->PrototypeTemplate()->Set(isolate, "hue", v8::FunctionTemplate::New(isolate, Hue));
			tpl->PrototypeTemplate()->Set(isolate, "isValid", v8::FunctionTemplate::New(isolate, IsValid));
			tpl->PrototypeTemplate()->Set(isolate, "isValidColor", v8::FunctionTemplate::New(isolate, IsValidColor));
			tpl->PrototypeTemplate()->Set(isolate, "lighter", v8::FunctionTemplate::New(isolate, Lighter));
			tpl->PrototypeTemplate()->Set(isolate, "lightness", v8::FunctionTemplate::New(isolate, Lightness));
			tpl->PrototypeTemplate()->Set(isolate, "magenta", v8::FunctionTemplate::New(isolate, Magenta));
			tpl->PrototypeTemplate()->Set(isolate, "name", v8::FunctionTemplate::New(isolate, Name));
			tpl->PrototypeTemplate()->Set(isolate, "rgb", v8::FunctionTemplate::New(isolate, Rgb));
			tpl->PrototypeTemplate()->Set(isolate, "rgba", v8::FunctionTemplate::New(isolate, Rgba));
			tpl->PrototypeTemplate()->Set(isolate, "rgba64", v8::FunctionTemplate::New(isolate, Rgba64));
			tpl->PrototypeTemplate()->Set(isolate, "saturation", v8::FunctionTemplate::New(isolate, Saturation));
			tpl->PrototypeTemplate()->Set(isolate, "setCmyk", v8::FunctionTemplate::New(isolate, SetCmyk));
			tpl->PrototypeTemplate()->Set(isolate, "setHsl", v8::FunctionTemplate::New(isolate, SetHsl));
			tpl->PrototypeTemplate()->Set(isolate, "setHsv", v8::FunctionTemplate::New(isolate, SetHsv));
			tpl->PrototypeTemplate()->Set(isolate, "setNamedColor", v8::FunctionTemplate::New(isolate, SetNamedColor));
			tpl->PrototypeTemplate()->Set(isolate, "setRgb", v8::FunctionTemplate::New(isolate, SetRgb));
			tpl->PrototypeTemplate()->Set(isolate, "setRgba", v8::FunctionTemplate::New(isolate, SetRgba));
			tpl->PrototypeTemplate()->Set(isolate, "setRgba64", v8::FunctionTemplate::New(isolate, SetRgba64));
			tpl->PrototypeTemplate()->Set(isolate, "spec", v8::FunctionTemplate::New(isolate, Spec));
			tpl->PrototypeTemplate()->Set(isolate, "toCmyk", v8::FunctionTemplate::New(isolate, ToCmyk));
			tpl->PrototypeTemplate()->Set(isolate, "toExtendedRgb", v8::FunctionTemplate::New(isolate, ToExtendedRgb));
			tpl->PrototypeTemplate()->Set(isolate, "toHsl", v8::FunctionTemplate::New(isolate, ToHsl));
			tpl->PrototypeTemplate()->Set(isolate, "toHsv", v8::FunctionTemplate::New(isolate, ToHsv));
			tpl->PrototypeTemplate()->Set(isolate, "toRgb", v8::FunctionTemplate::New(isolate, ToRgb));
			tpl->PrototypeTemplate()->Set(isolate, "value", v8::FunctionTemplate::New(isolate, Value));
			tpl->PrototypeTemplate()->Set(isolate, "yellow", v8::FunctionTemplate::New(isolate, Yellow));

			{
				tpl->Set(isolate, "colorNames", v8::FunctionTemplate::New(isolate, ColorNames));
				tpl->Set(isolate, "fromCmyk", v8::FunctionTemplate::New(isolate, FromCmyk));
				tpl->Set(isolate, "fromHsl", v8::FunctionTemplate::New(isolate, FromHsl));
				tpl->Set(isolate, "fromHsv", v8::FunctionTemplate::New(isolate, FromHsv));
				tpl->Set(isolate, "fromRgb", v8::FunctionTemplate::New(isolate, FromRgb));
				tpl->Set(isolate, "fromRgba64", v8::FunctionTemplate::New(isolate, FromRgba64));
				tpl->Set(isolate, "fromRgba", v8::FunctionTemplate::New(isolate, FromRgba));
				tpl->Set(isolate, "isValidColor", v8::FunctionTemplate::New(isolate, IsValidColor));
			}
		}

	public:
		qreal red() const noexcept { return d_func()->redF(); }
		qreal green() const noexcept { return d_func()->greenF(); }
		qreal blue() const noexcept { return d_func()->blueF(); }
		qreal alpha() const noexcept { return d_func()->alphaF(); }
		void setRed(qreal red) { d_func()->setRedF(red); }
		void setGreen(qreal green) { d_func()->setGreenF(green); }
		void setBlue(qreal blue) { d_func()->setBlueF(blue); }
		void setAlpha(qreal alpha) { d_func()->setAlphaF(alpha); }

	public:

		static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->isValid();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Name(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					QString name;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						QColor::NameFormat format = static_cast<QColor::NameFormat>(args[0]->Int32Value(context).FromJust());
						name = (*p)->name(format);
					}
					else {
						name = (*p)->name();
					}
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, qPrintable(name)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetNamedColor(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value name(isolate, args[0]);
						(*p)->setNamedColor(*name);
					}
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ColorNames(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->colorNames();
					v8::Local<v8::Array> array = v8::Array::New(isolate, result.length());

					for (int i = 0; i < result.length(); ++i)
					{
						array->Set(context, i, V8_NEW_STRING_VAR(isolate, qPrintable(result[i])));
					}

					args.GetReturnValue().Set(array);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Spec(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->spec();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Alpha(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				info.GetReturnValue().Set((*p)->alpha());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Red(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				info.GetReturnValue().Set((*p)->red());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Green(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				info.GetReturnValue().Set((*p)->green());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Blue(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				info.GetReturnValue().Set((*p)->blue());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetRed(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());

				(*p)->setRed(value->NumberValue(context).ToChecked());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetGreen(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());

				(*p)->setGreen(value->NumberValue(context).ToChecked());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetBlue(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				(*p)->setBlue(value->NumberValue(context).ToChecked());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetAlpha(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(info.This());
				(*p)->setAlpha(value->NumberValue(context).ToChecked());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetRgb(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					std::array<int, 4> rgba = { 0, 0, 0, 255 };

					for (int i = 0; i < args.Length(); ++i) {
						if (args[i]->IsNumber()) {
							rgba[i] = args[i]->Int32Value(context).FromJust();
						}
					}
					(*p)->setRgb(rgba[0], rgba[1], rgba[2], rgba[3]);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Rgba64(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->rgba64();
					//args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetRgba64(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Rgba(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->rgba();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetRgba(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Rgb(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->rgb();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Hue(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->hue();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Saturation(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->saturation();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void HsvHue(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->hsvHue();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void HsvSaturation(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->hsvSaturation();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Value(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->value();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetHsv(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					std::array<int, 4> hsva = { 0, 0, 0, 255 };

					for (int i = 0; i < args.Length(); ++i) {
						if (args[i]->IsNumber()) {
							hsva[i] = args[i]->Int32Value(context).FromJust();
						}
					}
					(*p)->setHsv(hsva[0], hsva[1], hsva[2], hsva[3]);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Cyan(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->cyan();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Magenta(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->magenta();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Yellow(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->yellow();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Black(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->black();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetCmyk(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					std::array<int, 5> rgba = { 0, 0, 0, 0, 255 };

					for (int i = 0; i < args.Length(); ++i) {
						if (args[i]->IsNumber()) {
							rgba[i] = args[i]->Int32Value(context).FromJust();
						}
					}
					(*p)->setCmyk(rgba[0], rgba[1], rgba[2], rgba[3], rgba[4]);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void HslHue(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->hslHue();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void HslSaturation(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->hslSaturation();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Lightness(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->lightness();
					args.GetReturnValue().Set(result);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void SetHsl(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					std::array<int, 4> hsl = { 0, 0, 0, 255 };

					for (int i = 0; i < args.Length(); ++i) {
						if (args[i]->IsNumber()) {
							hsl[i] = args[i]->Int32Value(context).FromJust();
						}
					}
					(*p)->setHsl(hsl[0], hsl[1], hsl[2], hsl[3]);
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ToRgb(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->toRgb();
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ToHsv(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->toHsv();
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ToCmyk(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->toCmyk();
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ToHsl(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->toHsl();
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ToExtendedRgb(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					auto result = (*p)->toExtendedRgb();
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void ConvertTo(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromRgb(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromRgba(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int r = 0, g = 0, b = 0, a = 255;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						r = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						g = args[1]->Int32Value(context).FromJust();
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						b = args[2]->Int32Value(context).FromJust();
					}
					if (args.Length() > 3 && args[3]->IsNumber()) {
						a = args[3]->Int32Value(context).FromJust();
					}
					QColor color = QColor::fromRgb(r, g, b, a);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromRgba64(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					short r = 0, g = 0, b = 0, a = USHRT_MAX;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						r = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						g = args[1]->Int32Value(context).FromJust();
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						b = args[2]->Int32Value(context).FromJust();
					}
					if (args.Length() > 3 && args[3]->IsNumber()) {
						a = args[3]->Int32Value(context).FromJust();
					}
					QColor color = QColor::fromRgba64(r, g, b, a);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromHsv(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int r = 0, g = 0, b = 0, a = 255;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						r = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						g = args[1]->Int32Value(context).FromJust();
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						b = args[2]->Int32Value(context).FromJust();
					}
					if (args.Length() > 3 && args[3]->IsNumber()) {
						a = args[3]->Int32Value(context).FromJust();
					}
					QColor color = QColor::fromHsv(r, g, b, a);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromCmyk(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int c = 0, m = 0, y = 0, k = 0, a = 255;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						c = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						m = args[1]->Int32Value(context).FromJust();
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						y = args[2]->Int32Value(context).FromJust();
					}
					if (args.Length() > 3 && args[3]->IsNumber()) {
						k = args[3]->Int32Value(context).FromJust();
					}
					if (args.Length() > 4 && args[4]->IsNumber()) {
						a = args[4]->Int32Value(context).FromJust();
					}
					QColor color = QColor::fromCmyk(c, m, y, k, a);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void FromHsl(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int r = 0, g = 0, b = 0, a = 255;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						r = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						g = args[1]->Int32Value(context).FromJust();
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						b = args[2]->Int32Value(context).FromJust();
					}
					if (args.Length() > 3 && args[3]->IsNumber()) {
						a = args[3]->Int32Value(context).FromJust();
					}
					QColor color = QColor::fromHsl(r, g, b, a);
					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Lighter(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int factor = 150;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						factor = args[0]->Int32Value(context).FromJust();
					}
					QColor color = (*p)->lighter(factor);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void Darker(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				auto* p = UnWrap<QColorWrapper<T, U, C>>(args.This());
				if (p)
				{
					int factor = 200;
					if (args.Length() > 0 && args[0]->IsNumber()) {
						factor = args[0]->Int32Value(context).FromJust();
					}
					QColor color = (*p)->darker(factor);

					args.GetReturnValue().Set(Color::New(isolate, v8::External::New(isolate, &color)));
				};
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

		static void IsValidColor(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				if (args.Length() > 0 && args[0]->IsString()) {
					v8::String::Utf8Value name(isolate, args[0]);
					args.GetReturnValue().Set(QColor::isValidColor(*name));
				}
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}
	};
}
