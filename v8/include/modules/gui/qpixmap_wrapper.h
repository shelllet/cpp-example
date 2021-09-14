#pragma once
#include "qpaintdevice_wrapper.h"
namespace shelllet {
	namespace gui {
		template<typename T, typename U, bool C>
		class QPixmapWrapper : public QPaintDeviceWrapper<T, U, C>
		{
		public:
			template<bool M>
			QPixmapWrapper(QPixmapPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QPaintDeviceWrapper(d, args) {
			}
			QPixmapWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QPaintDeviceWrapper(isolate, tpl) {}
			QPixmapWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QPaintDeviceWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "cacheKey", v8::FunctionTemplate::New(isolate, CacheKey));
				tpl->PrototypeTemplate()->Set(isolate, "convertFromImage", v8::FunctionTemplate::New(isolate, ConvertFromImage));
				tpl->PrototypeTemplate()->Set(isolate, "copy", v8::FunctionTemplate::New(isolate, Copy));
				tpl->PrototypeTemplate()->Set(isolate, "createHeuristicMask", v8::FunctionTemplate::New(isolate, CreateHeuristicMask));
				tpl->PrototypeTemplate()->Set(isolate, "createMaskFromColor", v8::FunctionTemplate::New(isolate, CreateMaskFromColor));
				tpl->PrototypeTemplate()->Set(isolate, "detach", v8::FunctionTemplate::New(isolate, Detach));
				tpl->PrototypeTemplate()->Set(isolate, "devType", v8::FunctionTemplate::New(isolate, DevType));
				tpl->PrototypeTemplate()->Set(isolate, "fill", v8::FunctionTemplate::New(isolate, Fill));
				tpl->PrototypeTemplate()->Set(isolate, "hasAlpha", v8::FunctionTemplate::New(isolate, HasAlpha));
				tpl->PrototypeTemplate()->Set(isolate, "hasAlphaChannel", v8::FunctionTemplate::New(isolate, HasAlphaChannel));
				tpl->PrototypeTemplate()->Set(isolate, "isDetached", v8::FunctionTemplate::New(isolate, IsDetached));
				tpl->PrototypeTemplate()->Set(isolate, "isNull", v8::FunctionTemplate::New(isolate, IsNull));
				tpl->PrototypeTemplate()->Set(isolate, "isQBitmap", v8::FunctionTemplate::New(isolate, IsQBitmap));
				tpl->PrototypeTemplate()->Set(isolate, "load", v8::FunctionTemplate::New(isolate, Load));
				tpl->PrototypeTemplate()->Set(isolate, "loadFromData", v8::FunctionTemplate::New(isolate, LoadFromData));
				tpl->PrototypeTemplate()->Set(isolate, "mask", v8::FunctionTemplate::New(isolate, Mask));
				tpl->PrototypeTemplate()->Set(isolate, "rect", v8::FunctionTemplate::New(isolate, GetRect));
				tpl->PrototypeTemplate()->Set(isolate, "save", v8::FunctionTemplate::New(isolate, Save));
				tpl->PrototypeTemplate()->Set(isolate, "scaled", v8::FunctionTemplate::New(isolate, Scaled));
				tpl->PrototypeTemplate()->Set(isolate, "scaledToHeight", v8::FunctionTemplate::New(isolate, ScaledToHeight));
				tpl->PrototypeTemplate()->Set(isolate, "scaledToWidth", v8::FunctionTemplate::New(isolate, ScaledToWidth));
				tpl->PrototypeTemplate()->Set(isolate, "scroll", v8::FunctionTemplate::New(isolate, Scroll));
				tpl->PrototypeTemplate()->Set(isolate, "setDevicePixelRatio", v8::FunctionTemplate::New(isolate, SetDevicePixelRatio));
				tpl->PrototypeTemplate()->Set(isolate, "setMask", v8::FunctionTemplate::New(isolate, SetMask));
				tpl->PrototypeTemplate()->Set(isolate, "size", v8::FunctionTemplate::New(isolate, GetSize));
				tpl->PrototypeTemplate()->Set(isolate, "toImage", v8::FunctionTemplate::New(isolate, ToImage));
				tpl->PrototypeTemplate()->Set(isolate, "transformed", v8::FunctionTemplate::New(isolate, Transformed));
				{
					tpl->Set(isolate, "defaultDepth", v8::FunctionTemplate::New(isolate, DefaultDepth));
					tpl->Set(isolate, "fromImage", v8::FunctionTemplate::New(isolate, FromImage));
					tpl->Set(isolate, "fromImageReader", v8::FunctionTemplate::New(isolate, FromImageReader));
					tpl->Set(isolate, "trueMatrix", v8::FunctionTemplate::New(isolate, TrueMatrix));
				}
			}

		protected:

			static void CacheKey(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::BigInt::New(isolate, (*p)->cacheKey());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ConvertFromImage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto* img = Image::From(args[0]);

					auto flags = std::invoke([&]() {
						if (args[1]->IsInt32())
							return static_cast<Qt::ImageConversionFlags>(args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
						});

					auto result = v8::Boolean::New(isolate, (*p)->convertFromImage(**img, flags));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Copy(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto rect = Rect::From(args[0]);

					auto result = Pixmap::New(isolate, v8::External::New(isolate, &(*p)->copy(**rect)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void CreateHeuristicMask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					/*auto clipTight = std::invoke([&]() {
						if (args[0]->IsBoolean())
							return args[0]->BooleanValue(isolate);
						return true;
						});

					auto result = v8::Int32::New(isolate, (*p)->createHeuristicMask(clipTight));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void CreateMaskFromColor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					v8::Local<v8::Value> result;
					/*if (args[0]->IsObject()) {
						auto maskColor = Color::From(args[0]);
						auto mode = std::invoke([&]() {
							if (args[1]->IsNumber())
								return static_cast<Qt::MaskMode>(args[1]->Int32Value(context).FromJust());
							return static_cast<Qt::MaskMode>(Qt::MaskInColor);
							});

						result = v8::Int32::New(isolate, (*p)->createMaskFromColor(maskColor, mode));
					}
					else {
						auto color = static_cast<QRgb>(args[0]->Int32Value(context).FromJust());
						auto mode = std::invoke([&]() {
							if (args[1]->IsNumber())
								return static_cast<Qt::MaskMode>(args[1]->Int32Value(context).FromJust());
							return static_cast<Qt::MaskMode>(Qt::MaskInColor);
							});
						result = v8::Int32::New(isolate, (*p)->createMaskFromColor(color, mode));
					}*/

					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Detach(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
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
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, (*p)->devType());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Fill(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					if (args[0]->IsNumber()) {
						auto fillColor = args[0]->Int32Value(context).FromJust();
						(*p)->fill(fillColor);
					}
					else if (args[0]->IsObject()) {
						auto* fillColor = Color::From(args[0]);
						(*p)->fill(**fillColor);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasAlpha(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->hasAlpha());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasAlphaChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->hasAlphaChannel());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsDetached(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isDetached());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsNull(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isNull());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsQBitmap(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, (*p)->isQBitmap());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Load(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					// TODO:
					auto fileName = ToString({ isolate, args[0] });
					auto format = ToString({ isolate, args[1] });

					auto flags = std::invoke([&]() {
						if (args[2]->IsObject())
							return static_cast<Qt::ImageConversionFlags>(args[2]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
						});

					auto result = v8::Boolean::New(isolate, (*p)->load(fileName, format, flags));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LoadFromData(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto data = ToArray<char>(args[0]);
					auto format = ToString({ isolate, args[1] });

					auto flags = std::invoke([&]() {
						if (args[2]->IsNumber())
							return static_cast<Qt::ImageConversionFlags>(args[2]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
						});

					auto result = v8::Boolean::New(isolate, (*p)->loadFromData(QByteArray::fromRawData(&data[0], data.size()), format, flags));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void Mask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Int32::New(isolate, (*p)->mask());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetRect(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Rect::New(isolate, v8::External::New(isolate, &(*p)->rect()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Save(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					QString fileName;
					if (args[0]->IsString()) {
						fileName = QString::fromStdWString(ToWString({ isolate, args[0] }));
					}

					auto format = ToString({ isolate, args[1] });
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
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
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
							return static_cast<Qt::AspectRatioMode>(args[index]->Int32Value(context).FromJust());
						return static_cast<Qt::AspectRatioMode>(Qt::IgnoreAspectRatio);
						});
					index++;
					auto mode = std::invoke([&]() {
						if (args[index]->IsObject())
							return static_cast<Qt::TransformationMode>(args[index]->Int32Value(context).FromJust());
						return static_cast<Qt::TransformationMode>(Qt::FastTransformation);
						});

					auto result = Pixmap::New(isolate, v8::External::New(isolate, &(*p)->scaled(**s, aspectMode, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScaledToHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto h = args[0]->Int32Value(context).FromJust();

					auto mode = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::TransformationMode>(args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::TransformationMode>(Qt::FastTransformation);
						});

					auto result = Pixmap::New(isolate, v8::External::New(isolate, &(*p)->scaledToHeight(h, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScaledToWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto w = args[0]->Int32Value(context).FromJust();

					auto mode = std::invoke([&]() {
						if (args[1]->IsNumber())
							return static_cast<Qt::TransformationMode>(args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::TransformationMode>(Qt::FastTransformation);
						});

					auto result = Pixmap::New(isolate, v8::External::New(isolate, &(*p)->scaledToWidth(w, mode)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Scroll(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto dx = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto dy = std::invoke([&]() {
						if (!args[1]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [1].");
						return args[1]->Int32Value(context).FromJust();
						});

					auto rect = Rect::From(args[2]);

					(*p)->scroll(dx, dy, **rect, nullptr);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDevicePixelRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto scaleFactor = args[0]->NumberValue(context).FromJust();

					(*p)->setDevicePixelRatio(scaleFactor);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void SetMask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto QBitmap = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						(*p)->setMask(QBitmap);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Size::New(isolate, v8::External::New(isolate, &(*p)->size()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToImage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = Image::New(isolate, v8::External::New(isolate, &(*p)->toImage()));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void Transformed(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QPixmapWrapper<T, U, C>>(args.This());
					if (!p)
						return;
					/*	}
						auto QTransform = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						auto mode = std::invoke([&]() {
							if (args[1]->IsObject())
								return args[1]->Int32Value(context).FromJust();
							return Qt::FastTransformation;
							});

						auto result = v8::Int32::New(isolate, (*p)->transformed(QTransform, mode));
						args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DefaultDepth(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto result = v8::Int32::New(isolate, QPixmap::defaultDepth());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FromImage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto image = Image::From(args[0]);

					auto flags = std::invoke([&]() {
						if (args[1]->IsObject())
							return static_cast<Qt::ImageConversionFlags>(args[1]->Int32Value(context).FromJust());
						return static_cast<Qt::ImageConversionFlags>(Qt::AutoColor);
						});

					auto result = Pixmap::New(isolate, v8::External::New(isolate, &QPixmap::fromImage(**image, flags)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void FromImageReader(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*auto* imageReader = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto flags = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return Qt::AutoColor;
						});

					auto result = v8::Int32::New(isolate, (*p)->fromImageReader(*imageReader, flags));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void TrueMatrix(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					/*auto m = std::invoke([&]() {
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

					auto result = v8::Int32::New(isolate, (*p)->trueMatrix(m, w, h));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
