#pragma once
#include "qpaintdevice_wrapper.h"
namespace shelllet {
	namespace gui {
		template<typename T, typename U, bool C>
		class QImageWrapper : public QPaintDeviceWrapper<T, U, C>
		{
		public:

			template<bool M>
			QImageWrapper(QImagePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QPaintDeviceWrapper(d, args) {
			}
			QImageWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QPaintDeviceWrapper(isolate, tpl) {}
			QImageWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QPaintDeviceWrapper(isolate, proto) {
				{
					v8::Local<v8::ObjectTemplate> invertMode = v8::ObjectTemplate::New(isolate);
					invertMode->Set(isolate, "InvertRgb", v8::Int32::New(isolate, QImage::InvertMode::InvertRgb));
					invertMode->Set(isolate, " InvertRgba", v8::Int32::New(isolate, QImage::InvertMode::InvertRgba));
					tpl->Set(isolate, "InvertMode", invertMode);

					v8::Local<v8::ObjectTemplate> format = v8::ObjectTemplate::New(isolate);
					format->Set(isolate, "Format_Invalid", v8::Int32::New(isolate, QImage::Format::Format_Invalid));
					format->Set(isolate, "Format_Mono", v8::Int32::New(isolate, QImage::Format::Format_Mono));
					format->Set(isolate, "Format_MonoLSB", v8::Int32::New(isolate, QImage::Format::Format_MonoLSB));
					format->Set(isolate, "Format_Indexed8", v8::Int32::New(isolate, QImage::Format::Format_Indexed8));
					format->Set(isolate, "Format_RGB32", v8::Int32::New(isolate, QImage::Format::Format_RGB32));
					format->Set(isolate, "Format_ARGB32", v8::Int32::New(isolate, QImage::Format::Format_ARGB32));
					format->Set(isolate, "Format_ARGB32_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_ARGB32_Premultiplied));
					format->Set(isolate, "Format_RGB16", v8::Int32::New(isolate, QImage::Format::Format_RGB16));
					format->Set(isolate, "Format_ARGB8565_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_ARGB8565_Premultiplied));
					format->Set(isolate, "Format_RGB666", v8::Int32::New(isolate, QImage::Format::Format_RGB666));
					format->Set(isolate, "Format_ARGB6666_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_ARGB6666_Premultiplied));
					format->Set(isolate, "Format_RGB555", v8::Int32::New(isolate, QImage::Format::Format_RGB555));
					format->Set(isolate, "Format_ARGB8555_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_ARGB8555_Premultiplied));
					format->Set(isolate, "Format_RGB888", v8::Int32::New(isolate, QImage::Format::Format_RGB888));
					format->Set(isolate, "Format_RGB444", v8::Int32::New(isolate, QImage::Format::Format_RGB444));
					format->Set(isolate, "Format_ARGB4444_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_ARGB4444_Premultiplied));
					format->Set(isolate, "Format_RGBX8888", v8::Int32::New(isolate, QImage::Format::Format_RGBX8888));
					format->Set(isolate, "Format_RGBA8888", v8::Int32::New(isolate, QImage::Format::Format_RGBA8888));
					format->Set(isolate, "Format_RGBA8888_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_RGBA8888_Premultiplied));
					format->Set(isolate, "Format_BGR30", v8::Int32::New(isolate, QImage::Format::Format_BGR30));
					format->Set(isolate, "Format_A2BGR30_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_A2BGR30_Premultiplied));
					format->Set(isolate, "Format_RGB30", v8::Int32::New(isolate, QImage::Format::Format_RGB30));
					format->Set(isolate, "Format_A2RGB30_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_A2RGB30_Premultiplied));
					format->Set(isolate, "Format_Alpha8", v8::Int32::New(isolate, QImage::Format::Format_Alpha8));
					format->Set(isolate, "Format_Grayscale8", v8::Int32::New(isolate, QImage::Format::Format_Grayscale8));
					format->Set(isolate, "Format_RGBX64", v8::Int32::New(isolate, QImage::Format::Format_RGBX64));
					format->Set(isolate, "Format_RGBA64", v8::Int32::New(isolate, QImage::Format::Format_RGBA64));
					format->Set(isolate, "Format_RGBA64_Premultiplied", v8::Int32::New(isolate, QImage::Format::Format_RGBA64_Premultiplied));
					format->Set(isolate, "Format_Grayscale16", v8::Int32::New(isolate, QImage::Format::Format_Grayscale16));
					format->Set(isolate, "Format_BGR888", v8::Int32::New(isolate, QImage::Format::Format_BGR888));
					format->Set(isolate, "NImageFormats", v8::Int32::New(isolate, QImage::Format::NImageFormats));
					tpl->Set(isolate, "Format", format);

					tpl->Set(isolate, "fromData", v8::FunctionTemplate::New(isolate, FromData));
					tpl->Set(isolate, "toImageFormat", v8::FunctionTemplate::New(isolate, ToImageFormat));
					tpl->Set(isolate, "toPixelFormat", v8::FunctionTemplate::New(isolate, ToPixelFormat));
					tpl->Set(isolate, "trueMatrix", v8::FunctionTemplate::New(isolate, TrueMatrix));
				}
				{
					tpl->PrototypeTemplate()->Set(isolate, "allGray", v8::FunctionTemplate::New(isolate, AllGray));
					tpl->PrototypeTemplate()->Set(isolate, "alphaChannel", v8::FunctionTemplate::New(isolate, AlphaChannel));
					tpl->PrototypeTemplate()->Set(isolate, "applyColorTransform", v8::FunctionTemplate::New(isolate, ApplyColorTransform));
					tpl->PrototypeTemplate()->Set(isolate, "bitPlaneCount", v8::FunctionTemplate::New(isolate, BitPlaneCount));
					tpl->PrototypeTemplate()->Set(isolate, "bits", v8::FunctionTemplate::New(isolate, Bits));
					tpl->PrototypeTemplate()->Set(isolate, "bytesPerLine", v8::FunctionTemplate::New(isolate, BytesPerLine));
					tpl->PrototypeTemplate()->Set(isolate, "cacheKey", v8::FunctionTemplate::New(isolate, CacheKey));
					tpl->PrototypeTemplate()->Set(isolate, "color", v8::FunctionTemplate::New(isolate, Color));
					tpl->PrototypeTemplate()->Set(isolate, "colorSpace", v8::FunctionTemplate::New(isolate, ColorSpace));
					tpl->PrototypeTemplate()->Set(isolate, "colorTable", v8::FunctionTemplate::New(isolate, ColorTable));
					tpl->PrototypeTemplate()->Set(isolate, "convertedToColorSpace", v8::FunctionTemplate::New(isolate, ConvertedToColorSpace));
					tpl->PrototypeTemplate()->Set(isolate, "convertTo", v8::FunctionTemplate::New(isolate, ConvertTo));
					tpl->PrototypeTemplate()->Set(isolate, "convertToColorSpace", v8::FunctionTemplate::New(isolate, ConvertToColorSpace));
					tpl->PrototypeTemplate()->Set(isolate, "convertToFormat", v8::FunctionTemplate::New(isolate, ConvertToFormat));
					tpl->PrototypeTemplate()->Set(isolate, "copy", v8::FunctionTemplate::New(isolate, Copy));
					tpl->PrototypeTemplate()->Set(isolate, "createAlphaMask", v8::FunctionTemplate::New(isolate, CreateAlphaMask));
					tpl->PrototypeTemplate()->Set(isolate, "createHeuristicMask", v8::FunctionTemplate::New(isolate, CreateHeuristicMask));
					tpl->PrototypeTemplate()->Set(isolate, "createMaskFromColor", v8::FunctionTemplate::New(isolate, CreateMaskFromColor));
					tpl->PrototypeTemplate()->Set(isolate, "detach", v8::FunctionTemplate::New(isolate, Detach));
					tpl->PrototypeTemplate()->Set(isolate, "devType", v8::FunctionTemplate::New(isolate, DevType));
					tpl->PrototypeTemplate()->Set(isolate, "dotsPerMeterX", v8::FunctionTemplate::New(isolate, DotsPerMeterX));
					tpl->PrototypeTemplate()->Set(isolate, "dotsPerMeterY", v8::FunctionTemplate::New(isolate, DotsPerMeterY));
					tpl->PrototypeTemplate()->Set(isolate, "fill", v8::FunctionTemplate::New(isolate, Fill));
					tpl->PrototypeTemplate()->Set(isolate, "format", v8::FunctionTemplate::New(isolate, Format));
					tpl->PrototypeTemplate()->Set(isolate, "fromData", v8::FunctionTemplate::New(isolate, FromData));
					tpl->PrototypeTemplate()->Set(isolate, "hasAlphaChannel", v8::FunctionTemplate::New(isolate, HasAlphaChannel));
					tpl->PrototypeTemplate()->Set(isolate, "invertPixels", v8::FunctionTemplate::New(isolate, InvertPixels));
					tpl->PrototypeTemplate()->Set(isolate, "isDetached", v8::FunctionTemplate::New(isolate, IsDetached));
					tpl->PrototypeTemplate()->Set(isolate, "isGrayscale", v8::FunctionTemplate::New(isolate, IsGrayscale));
					tpl->PrototypeTemplate()->Set(isolate, "isNull", v8::FunctionTemplate::New(isolate, IsNull));
					tpl->PrototypeTemplate()->Set(isolate, "load", v8::FunctionTemplate::New(isolate, Load));
					tpl->PrototypeTemplate()->Set(isolate, "loadFromData", v8::FunctionTemplate::New(isolate, LoadFromData));
					tpl->PrototypeTemplate()->Set(isolate, "mirrored", v8::FunctionTemplate::New(isolate, Mirrored));
					tpl->PrototypeTemplate()->Set(isolate, "offset", v8::FunctionTemplate::New(isolate, Offset));
					tpl->PrototypeTemplate()->Set(isolate, "pixel", v8::FunctionTemplate::New(isolate, Pixel));
					tpl->PrototypeTemplate()->Set(isolate, "pixelColor", v8::FunctionTemplate::New(isolate, PixelColor));
					tpl->PrototypeTemplate()->Set(isolate, "pixelFormat", v8::FunctionTemplate::New(isolate, PixelFormat));
					tpl->PrototypeTemplate()->Set(isolate, "pixelIndex", v8::FunctionTemplate::New(isolate, PixelIndex));
					tpl->PrototypeTemplate()->Set(isolate, "rect", v8::FunctionTemplate::New(isolate, GetRect));
					tpl->PrototypeTemplate()->Set(isolate, "reinterpretAsFormat", v8::FunctionTemplate::New(isolate, ReinterpretAsFormat));
					tpl->PrototypeTemplate()->Set(isolate, "rgbSwapped", v8::FunctionTemplate::New(isolate, RgbSwapped));
					tpl->PrototypeTemplate()->Set(isolate, "save", v8::FunctionTemplate::New(isolate, Save));
					tpl->PrototypeTemplate()->Set(isolate, "scaled", v8::FunctionTemplate::New(isolate, Scaled));
					tpl->PrototypeTemplate()->Set(isolate, "scaledToHeight", v8::FunctionTemplate::New(isolate, ScaledToHeight));
					tpl->PrototypeTemplate()->Set(isolate, "scaledToWidth", v8::FunctionTemplate::New(isolate, ScaledToWidth));
					tpl->PrototypeTemplate()->Set(isolate, "scanLine", v8::FunctionTemplate::New(isolate, ScanLine));
					tpl->PrototypeTemplate()->Set(isolate, "setAlphaChannel", v8::FunctionTemplate::New(isolate, SetAlphaChannel));
					tpl->PrototypeTemplate()->Set(isolate, "setColor", v8::FunctionTemplate::New(isolate, SetColor));
					tpl->PrototypeTemplate()->Set(isolate, "setColorCount", v8::FunctionTemplate::New(isolate, SetColorCount));
					tpl->PrototypeTemplate()->Set(isolate, "setColorSpace", v8::FunctionTemplate::New(isolate, SetColorSpace));
					tpl->PrototypeTemplate()->Set(isolate, "setColorTable", v8::FunctionTemplate::New(isolate, SetColorTable));
					tpl->PrototypeTemplate()->Set(isolate, "setDevicePixelRatio", v8::FunctionTemplate::New(isolate, SetDevicePixelRatio));
					tpl->PrototypeTemplate()->Set(isolate, "setDotsPerMeterX", v8::FunctionTemplate::New(isolate, SetDotsPerMeterX));
					tpl->PrototypeTemplate()->Set(isolate, "setDotsPerMeterY", v8::FunctionTemplate::New(isolate, SetDotsPerMeterY));
					tpl->PrototypeTemplate()->Set(isolate, "setOffset", v8::FunctionTemplate::New(isolate, SetOffset));
					tpl->PrototypeTemplate()->Set(isolate, "setPixel", v8::FunctionTemplate::New(isolate, SetPixel));
					tpl->PrototypeTemplate()->Set(isolate, "setPixelColor", v8::FunctionTemplate::New(isolate, SetPixelColor));
					tpl->PrototypeTemplate()->Set(isolate, "setText", v8::FunctionTemplate::New(isolate, SetText));
					tpl->PrototypeTemplate()->Set(isolate, "size", v8::FunctionTemplate::New(isolate, GetSize));
					tpl->PrototypeTemplate()->Set(isolate, "sizeInBytes", v8::FunctionTemplate::New(isolate, SizeInBytes));
					tpl->PrototypeTemplate()->Set(isolate, "text", v8::FunctionTemplate::New(isolate, Text));
					tpl->PrototypeTemplate()->Set(isolate, "textKeys", v8::FunctionTemplate::New(isolate, TextKeys));
					tpl->PrototypeTemplate()->Set(isolate, "transformed", v8::FunctionTemplate::New(isolate, Transformed));
					tpl->PrototypeTemplate()->Set(isolate, "valid", v8::FunctionTemplate::New(isolate, Valid));
				}
			}

		protected:
			static void AllGray(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->allGray());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void AlphaChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->alphaChannel()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void ApplyColorTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto transform = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					(*p)->applyColorTransform(transform);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BitPlaneCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->bitPlaneCount());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Bits(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Uint32::New(isolate, reinterpret_cast<std::uintptr_t>((*p)->bits()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesPerLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->bytesPerLine());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CacheKey(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::BigInt::New(isolate, (*p)->cacheKey());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Color(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto i = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto result = v8::Uint32::New(isolate, (*p)->color(i));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void ColorSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Int32::New(isolate, (*p)->colorSpace());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ColorTable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto colors = (*p)->colorTable();
					std::vector<std::uint32_t> c(colors.size());
					std::transform(colors.begin(), colors.end(), c.begin(), [](const auto& v) { return v; });

					args.GetReturnValue().Set(NewArray(c));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void ConvertedToColorSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto QColorSpace = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						auto result = v8::Int32::New(isolate, (*p)->convertedToColorSpace(QColorSpace));
						args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ConvertTo(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto f = static_cast<QImage::Format>(args[0]->Int32Value(context).FromJust());

					auto flags = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::ImageConversionFlag>(args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlag>(Qt::AutoColor);
						});

					(*p)->convertTo(f, flags);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void ConvertToColorSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto QColorSpace = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						(*p)->convertToColorSpace(QColorSpace);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ConvertToFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto f = static_cast<QImage::Format>(args[0]->Int32Value(context).FromJust());
					v8::Local<v8::Value> result;

					if (args[1]->IsArray()) {
						auto colorTable = ToArray<std::uint32_t>(args[1]);
						QVector<QRgb> c(colorTable.size());
						std::transform(colorTable.begin(), colorTable.end(), c.begin(), [](const auto& v) { return v; });
						auto flags = std::invoke([&]() {
							if (args[1]->IsInt32())
								return static_cast<Qt::ImageConversionFlags>(args[1]->Int32Value(context).FromJust());
							return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
							});
						result = Image::New(isolate, v8::External::New(isolate, &(*p)->convertToFormat(f, c, flags)));
					}
					else {
						auto flags = std::invoke([&]() {
							if (args[1]->IsInt32())
								return static_cast<Qt::ImageConversionFlags>(args[1]->Int32Value(context).FromJust());
							return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
							});
						result = Image::New(isolate, v8::External::New(isolate, &(*p)->convertToFormat(f, flags)));
					}

					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Copy(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto rect = Rect::From(args[0]);
					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->copy(**rect)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CreateAlphaMask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto flags = std::invoke([&]() {
						if (args[0]->IsObject())
							return static_cast<Qt::ImageConversionFlags>(args[0]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->createAlphaMask(flags)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CreateHeuristicMask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto clipTight = std::invoke([&]() {
						if (args[0]->IsBoolean())
							return args[0]->BooleanValue(isolate);
						return true;
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->createHeuristicMask(clipTight)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CreateMaskFromColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto color = static_cast<QRgb>(args[0]->Uint32Value(context).FromJust());

					auto mode = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::MaskMode> (args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::MaskMode>(Qt::MaskInColor);
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->createMaskFromColor(color, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Detach(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					(*p)->detach();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DevType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->devType());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DotsPerMeterX(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->dotsPerMeterX());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DotsPerMeterY(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->dotsPerMeterY());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void Fill(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					if (args[0]->IsNumber()) {
						int color = args[0]->Int32Value(context).FromJust();

						(*p)->fill(color);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Format(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->format());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasAlphaChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->hasAlphaChannel());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void InvertPixels(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto invertMode = static_cast<QImage::InvertMode>(args[0]->Int32Value(context).FromJust());

					(*p)->invertPixels(invertMode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsDetached(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isDetached());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsGrayscale(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isGrayscale());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsNull(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isNull());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Load(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto fileName = ToString({ isolate, args[0] });
					auto format = ToString({ isolate, args[1] });

					auto result = v8::Boolean::New(isolate, (*p)->load(fileName, format));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LoadFromData(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto buf = ToArray<char>(args[0]);
					auto format = ToString({ isolate, args[1] });

					auto result = v8::Boolean::New(isolate, (*p)->loadFromData(QByteArray::fromRawData(&buf[0], buf.size()), format));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Mirrored(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto horizontally = std::invoke([&]() {
						if (args[0]->IsBoolean())
							return args[0]->BooleanValue(isolate);
						return false;
						});

					auto vertically = std::invoke([&]() {
						if (args[1]->IsBoolean())
							return args[1]->BooleanValue(isolate);
						return true;
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->mirrored(horizontally, vertically)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Offset(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Point::New(isolate, v8::External::New(isolate, &(*p)->offset()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Pixel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::From(args[0]);
					// delete.
					auto result = v8::Int32::New(isolate, (*p)->pixel(**pt));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void PixelColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*
					auto result = v8::Int32::New(isolate, (*p)->pixelColor(x, y));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void PixelFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Int32::New(isolate, (*p)->pixelFormat());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PixelIndex(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					int index = 0;
					auto pt = Point::From(args[0]);
					auto result = v8::Int32::New(isolate, (*p)->pixelIndex(**pt));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetRect(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Rect::New(isolate, v8::External::New(isolate, &(*p)->rect()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReinterpretAsFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto f = static_cast<QImage::Format>(args[0]->Int32Value(context).FromJust());
					auto result = v8::Boolean::New(isolate, (*p)->reinterpretAsFormat(f));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RgbSwapped(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->rgbSwapped()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Save(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto fileName = ToString({ isolate, args[0] });

					auto format = ToString({ isolate, args[0] });

					auto quality = std::invoke([&]() {
						if (args[2]->IsInt32())
							return args[2]->Int32Value(context).FromJust();
						return -1;
						});

					auto result = v8::Boolean::New(isolate, (*p)->save(fileName, format, quality));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Scaled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					int index = 0;
					auto s = Size::From(args[0]);
					if (!s) {
						throw std::invalid_argument("! require `Size` value.");
					}

					auto aspectMode = std::invoke([&]() {
						if (args[index]->IsObject())
							return  static_cast<Qt::AspectRatioMode>(args[index]->Int32Value(context).FromJust());
						return static_cast<Qt::AspectRatioMode>(Qt::IgnoreAspectRatio);
						});

					auto mode = std::invoke([&]() {
						if (args[index]->IsObject())
							return static_cast<Qt::TransformationMode>(args[index]->Int32Value(context).FromJust());
						return static_cast<Qt::TransformationMode>(Qt::FastTransformation);
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->scaled(**s, aspectMode, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScaledToHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto h = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto mode = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::TransformationMode>(args[1]->Int32Value(context).FromJust());
						return Qt::FastTransformation;
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->scaledToHeight(h, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScaledToWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto w = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto mode = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::TransformationMode>(args[1]->Int32Value(context).FromJust());
						return Qt::FastTransformation;
						});

					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->scaledToWidth(w, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScanLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto index = args[0]->Int32Value(context).FromJust();
					auto result = v8::Uint32::New(isolate, reinterpret_cast<std::uintptr_t>((*p)->scanLine(index)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetAlphaChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto* alphaChannel = Image::From(args[0]);
					(*p)->setAlphaChannel(**alphaChannel);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto i = args[0]->Int32Value(context).FromJust();

					auto c = static_cast<QRgb>(args[1]->Int32Value(context).FromJust());
					(*p)->setColor(i, c);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetColorCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto colorCount = args[0]->Int32Value(context).FromJust();

					(*p)->setColorCount(colorCount);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void SetColorSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto QColorSpace = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						(*p)->setColorSpace(QColorSpace);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetColorTable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto colors = ToArray<std::uint32_t>(args[0]);
					QVector<QRgb> c(colors.size());
					std::transform(colors.begin(), colors.end(), c.begin(), [](const auto& v) { return v; });
					(*p)->setColorTable(c);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDevicePixelRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto scaleFactor = args[0]->NumberValue(context).FromJust();
					(*p)->setDevicePixelRatio(scaleFactor);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDotsPerMeterX(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto x = args[0]->Int32Value(context).FromJust();
					(*p)->setDotsPerMeterX(x);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDotsPerMeterY(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto y = args[0]->Int32Value(context).FromJust();

					(*p)->setDotsPerMeterY(y);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto offset = Point::From(args[0]);
					(*p)->setOffset(**offset);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetPixel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::From(args[0]);
					auto index_or_rgb = args[1]->Int32Value(context).FromJust();
					(*p)->setPixel(**pt, index_or_rgb);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void SetPixelColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto pt = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto c = std::invoke([&]() {
						if (!args[1]->IsObject())
							throw std::invalid_argument("!`Object` required at [1].");
						return args[1]->Int32Value(context).FromJust();
						});

					(*p)->setPixelColor(pt, c);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetText(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto key = ToString({ isolate, args[0] });

					auto value = ToString({ isolate, args[1] });

					(*p)->setText(key, value);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Size::New(isolate, v8::External::New(isolate, &(*p)->size()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SizeInBytes(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->sizeInBytes());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Text(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto key = ToString({ isolate, args[0] });
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, (*p)->text(key).toUtf8().constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void TextKeys(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					const auto keys = (*p)->textKeys();
					std::vector<std::string> c(keys.size());
					std::transform(keys.begin(), keys.end(), c.begin(), [](auto& s) { return s.toStdString(); });
					args.GetReturnValue().Set(NewArray(c));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void Transformed(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto matrix = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto mode = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return Qt::FastTransformation;
						});

					auto result = v8::Int32::New(isolate, (*p)->transformed(matrix, mode));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Valid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QImageWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::From(args[0]);
					auto result = v8::Boolean::New(isolate, (*p)->valid(**pt));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FromData(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto data = ToArray<char>(args[0]);
					auto format = ToString({ isolate, args[1] });

					auto result = Image::New(isolate, v8::External::New(isolate, &QImage::fromData(QByteArray::fromRawData(&data[0], data.size()), format)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void ToImageFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*auto result = v8::Int32::New(isolate, (*p)->toImageFormat());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO
			static void ToPixelFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*auto result = v8::Int32::New(isolate, (*p)->toPixelFormat());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void TrueMatrix(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*auto QMatrix = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto w = std::invoke([&]() {
						if (!args[1]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [1].");
						return args[1]->Int32Value(context).FromJust();
						});

					auto h = std::invoke([&]() {
						if (!args[2]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [2].");
						return args[2]->Int32Value(context).FromJust();
						});

					auto result = v8::Int32::New(isolate, (*p)->trueMatrix(QMatrix, w, h));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
