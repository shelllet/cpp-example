#pragma once
#include "qobject_wrapper.h"
namespace shelllet {
	namespace gui {
		template<typename T, bool> class QWindowPrivate;
		template<typename T, typename U, bool C>
		class QWindowWrapper : public core::QObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			QWindowWrapper(QWindowPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QWindowWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QWindowWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "setSurfaceType", v8::FunctionTemplate::New(isolate, SetSurfaceType));
				tpl->PrototypeTemplate()->Set(isolate, "surfaceType", v8::FunctionTemplate::New(isolate, SurfaceType));
				tpl->PrototypeTemplate()->Set(isolate, "create", v8::FunctionTemplate::New(isolate, Create));
				tpl->PrototypeTemplate()->Set(isolate, "winId", v8::FunctionTemplate::New(isolate, WinId));
				tpl->PrototypeTemplate()->Set(isolate, "parent", v8::FunctionTemplate::New(isolate, Parent));
				tpl->PrototypeTemplate()->Set(isolate, "setParent", v8::FunctionTemplate::New(isolate, SetParent));
				tpl->PrototypeTemplate()->Set(isolate, "isTopLevel", v8::FunctionTemplate::New(isolate, IsTopLevel));
				tpl->PrototypeTemplate()->Set(isolate, "isModal", v8::FunctionTemplate::New(isolate, IsModal));
				tpl->PrototypeTemplate()->Set(isolate, "setFormat", v8::FunctionTemplate::New(isolate, SetFormat));
				tpl->PrototypeTemplate()->Set(isolate, "format", v8::FunctionTemplate::New(isolate, Format));
				tpl->PrototypeTemplate()->Set(isolate, "requestedFormat", v8::FunctionTemplate::New(isolate, RequestedFormat));
				tpl->PrototypeTemplate()->Set(isolate, "setFlag", v8::FunctionTemplate::New(isolate, SetFlag));
				tpl->PrototypeTemplate()->Set(isolate, "type", v8::FunctionTemplate::New(isolate, Type));
				tpl->PrototypeTemplate()->Set(isolate, "setMask", v8::FunctionTemplate::New(isolate, SetMask));
				tpl->PrototypeTemplate()->Set(isolate, "mask", v8::FunctionTemplate::New(isolate, Mask));
				tpl->PrototypeTemplate()->Set(isolate, "contentOrientation", v8::FunctionTemplate::New(isolate, ContentOrientation));
				tpl->PrototypeTemplate()->Set(isolate, "devicePixelRatio", v8::FunctionTemplate::New(isolate, DevicePixelRatio));
				tpl->PrototypeTemplate()->Set(isolate, "windowState", v8::FunctionTemplate::New(isolate, WindowState));
				tpl->PrototypeTemplate()->Set(isolate, "windowStates", v8::FunctionTemplate::New(isolate, WindowStates));
				tpl->PrototypeTemplate()->Set(isolate, "setWindowState", v8::FunctionTemplate::New(isolate, SetWindowState));
				tpl->PrototypeTemplate()->Set(isolate, "setWindowStates", v8::FunctionTemplate::New(isolate, SetWindowStates));
				tpl->PrototypeTemplate()->Set(isolate, "setTransientParent", v8::FunctionTemplate::New(isolate, SetTransientParent));
				tpl->PrototypeTemplate()->Set(isolate, "transientParent", v8::FunctionTemplate::New(isolate, TransientParent));
				tpl->PrototypeTemplate()->Set(isolate, "isAncestorOf", v8::FunctionTemplate::New(isolate, IsAncestorOf));
				tpl->PrototypeTemplate()->Set(isolate, "isExposed", v8::FunctionTemplate::New(isolate, IsExposed));
				tpl->PrototypeTemplate()->Set(isolate, "baseSize", v8::FunctionTemplate::New(isolate, BaseSize));
				tpl->PrototypeTemplate()->Set(isolate, "sizeIncrement", v8::FunctionTemplate::New(isolate, SizeIncrement));
				tpl->PrototypeTemplate()->Set(isolate, "setBaseSize", v8::FunctionTemplate::New(isolate, SetBaseSize));
				tpl->PrototypeTemplate()->Set(isolate, "setSizeIncrement", v8::FunctionTemplate::New(isolate, SetSizeIncrement));
				tpl->PrototypeTemplate()->Set(isolate, "geometry", v8::FunctionTemplate::New(isolate, Geometry));
				tpl->PrototypeTemplate()->Set(isolate, "frameMargins", v8::FunctionTemplate::New(isolate, FrameMargins));
				tpl->PrototypeTemplate()->Set(isolate, "frameGeometry", v8::FunctionTemplate::New(isolate, FrameGeometry));
				tpl->PrototypeTemplate()->Set(isolate, "framePosition", v8::FunctionTemplate::New(isolate, FramePosition));
				tpl->PrototypeTemplate()->Set(isolate, "setFramePosition", v8::FunctionTemplate::New(isolate, SetFramePosition));
				tpl->PrototypeTemplate()->Set(isolate, "position", v8::FunctionTemplate::New(isolate, Position));
				tpl->PrototypeTemplate()->Set(isolate, "setPosition", v8::FunctionTemplate::New(isolate, SetPosition));
				tpl->PrototypeTemplate()->Set(isolate, "resize", v8::FunctionTemplate::New(isolate, Resize));
				tpl->PrototypeTemplate()->Set(isolate, "setFilePath", v8::FunctionTemplate::New(isolate, SetFilePath));
				tpl->PrototypeTemplate()->Set(isolate, "filePath", v8::FunctionTemplate::New(isolate, FilePath));
				tpl->PrototypeTemplate()->Set(isolate, "setIcon", v8::FunctionTemplate::New(isolate, SetIcon));
				tpl->PrototypeTemplate()->Set(isolate, "icon", v8::FunctionTemplate::New(isolate, Icon));
				tpl->PrototypeTemplate()->Set(isolate, "destroy", v8::FunctionTemplate::New(isolate, Destroy));
				tpl->PrototypeTemplate()->Set(isolate, "setKeyboardGrabEnabled", v8::FunctionTemplate::New(isolate, SetKeyboardGrabEnabled));
				tpl->PrototypeTemplate()->Set(isolate, "setMouseGrabEnabled", v8::FunctionTemplate::New(isolate, SetMouseGrabEnabled));
				tpl->PrototypeTemplate()->Set(isolate, "screen", v8::FunctionTemplate::New(isolate, Screen));
				tpl->PrototypeTemplate()->Set(isolate, "setScreen", v8::FunctionTemplate::New(isolate, SetScreen));
				tpl->PrototypeTemplate()->Set(isolate, "mapToGlobal", v8::FunctionTemplate::New(isolate, MapToGlobal));
				tpl->PrototypeTemplate()->Set(isolate, "mapFromGlobal", v8::FunctionTemplate::New(isolate, MapFromGlobal));
				tpl->PrototypeTemplate()->Set(isolate, "cursor", v8::FunctionTemplate::New(isolate, Cursor));
				tpl->PrototypeTemplate()->Set(isolate, "setCursor", v8::FunctionTemplate::New(isolate, SetCursor));
				tpl->PrototypeTemplate()->Set(isolate, "unsetCursor", v8::FunctionTemplate::New(isolate, UnsetCursor));
				tpl->PrototypeTemplate()->Set(isolate, "setVulkanInstance", v8::FunctionTemplate::New(isolate, SetVulkanInstance));
				tpl->PrototypeTemplate()->Set(isolate, "vulkanInstance", v8::FunctionTemplate::New(isolate, VulkanInstance));
				tpl->PrototypeTemplate()->Set(isolate, "show", v8::FunctionTemplate::New(isolate, Show));
				tpl->PrototypeTemplate()->Set(isolate, "hide", v8::FunctionTemplate::New(isolate, Hide));
				tpl->PrototypeTemplate()->Set(isolate, "showMinimized", v8::FunctionTemplate::New(isolate, ShowMinimized));
				tpl->PrototypeTemplate()->Set(isolate, "showMaximized", v8::FunctionTemplate::New(isolate, ShowMaximized));
				tpl->PrototypeTemplate()->Set(isolate, "showFullScreen", v8::FunctionTemplate::New(isolate, ShowFullScreen));
				tpl->PrototypeTemplate()->Set(isolate, "showNormal", v8::FunctionTemplate::New(isolate, ShowNormal));
				tpl->PrototypeTemplate()->Set(isolate, "close", v8::FunctionTemplate::New(isolate, Close));
				tpl->PrototypeTemplate()->Set(isolate, "raise", v8::FunctionTemplate::New(isolate, Raise));
				tpl->PrototypeTemplate()->Set(isolate, "lower", v8::FunctionTemplate::New(isolate, Lower));
				tpl->PrototypeTemplate()->Set(isolate, "setGeometry", v8::FunctionTemplate::New(isolate, SetGeometry));
				tpl->PrototypeTemplate()->Set(isolate, "reportContentOrientationChange", v8::FunctionTemplate::New(isolate, ReportContentOrientationChange));

				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "isVisible"), IsVisible, SetVisible);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "visibility"), Visibility, SetVisibility);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "modality"), Modality, SetModality);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "flags"), Flags, SetFlags);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "title"), Title, SetTitle);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "isActive"), IsActive, SetActive);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "minimumWidth"), MinimumWidth, SetMinimumWidth);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "minimumHeight"), MinimumHeight, SetMinimumHeight);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "maximumWidth"), MaximumWidth, SetMaximumWidth);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "maximumHeight"), MaximumHeight, SetMaximumHeight);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "width"), Width, SetWidth);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "height"), Height, SetHeight);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "x"), X, SetX);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "y"), Y, SetY);

				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "screenChanged"), nullptr, ScreenChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "modalityChanged"), nullptr, ModalityChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "windowStateChanged"), nullptr, WindowStateChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "xChanged"), nullptr, XChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "yChanged"), nullptr, YChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "widthChanged"), nullptr, WidthChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "heightChanged"), nullptr, HeightChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "minimumWidthChanged"), nullptr, MinimumWidthChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "minimumHeightChanged"), nullptr, MinimumHeightChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "maximumWidthChanged"), nullptr, MaximumWidthChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "maximumHeightChanged"), nullptr, MaximumHeightChanged);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "visibleChanged"), nullptr, VisibleChanged);
				{
					v8::Local<v8::ObjectTemplate> visibility = v8::ObjectTemplate::New(isolate);
					visibility->Set(isolate, "Hidden", v8::Int32::New(isolate, QWindow::Visibility::Hidden));
					visibility->Set(isolate, "AutomaticVisibility", v8::Int32::New(isolate, QWindow::Visibility::AutomaticVisibility));
					visibility->Set(isolate, "Windowed", v8::Int32::New(isolate, QWindow::Visibility::Windowed));
					visibility->Set(isolate, "Minimized", v8::Int32::New(isolate, QWindow::Visibility::Minimized));
					visibility->Set(isolate, "Maximized", v8::Int32::New(isolate, QWindow::Visibility::Maximized));
					visibility->Set(isolate, "FullScreen", v8::Int32::New(isolate, QWindow::Visibility::FullScreen));
					tpl->Set(isolate, "Visibility", visibility);

					v8::Local<v8::ObjectTemplate> ancestorMode = v8::ObjectTemplate::New(isolate);
					ancestorMode->Set(isolate, "ExcludeTransients", v8::Int32::New(isolate, QWindow::AncestorMode::ExcludeTransients));
					ancestorMode->Set(isolate, "IncludeTransients", v8::Int32::New(isolate, QWindow::AncestorMode::IncludeTransients));
					tpl->Set(isolate, "AncestorMode", ancestorMode);
					tpl->Set(isolate, "fromWinId", v8::FunctionTemplate::New(isolate, FromWinId));
				}
			}
		protected:
			QObject* focusObject() const
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> result = call(isolate, context, "focusObject", 0, {});
					if (!result->IsObject()) {
						throw std::logic_error("!return type error.");
					}
					auto* p = convert::Object::UnWrap<core::Object>(result->ToObject(context).ToLocalChecked());
					if (p)
						return **p;
					return nullptr;
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void exposeEvent(QExposeEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
					return convert::Object::Wrap(isolate, context, "ExposeEvent", std::size(argv), argv);
					}) };
					call(isolate, context, "exposeEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void resizeEvent(QResizeEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
					return convert::Object::Wrap(isolate, context, "ResizeEvent", std::size(argv), argv);
					}) };
					call(isolate, context, "resizeEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void moveEvent(QMoveEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "MoveEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "QMoveEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void focusInEvent(QFocusEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
					return convert::Object::Wrap(isolate, context, "FocusEvent", std::size(argv), argv);
					}) };
					call(isolate, context, "focusInEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void focusOutEvent(QFocusEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "FocusEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "focusOutEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void showEvent(QShowEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "ShowEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "showEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void hideEvent(QHideEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
							v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
							return convert::Object::Wrap(isolate, context, "HideEvent", std::size(argv), argv);
							}) };
					call(isolate, context, "hideEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void keyPressEvent(QKeyEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "KeyEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "keyPressEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void keyReleaseEvent(QKeyEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "KeyEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "keyReleaseEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void mousePressEvent(QMouseEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "MouseEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "mousePressEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void mouseReleaseEvent(QMouseEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
							v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
							return convert::Object::Wrap(isolate, context, "MouseEvent", std::size(argv), argv);
							}) };
					call(isolate, context, "mouseReleaseEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void mouseDoubleClickEvent(QMouseEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "MouseEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "mouseDoubleClickEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void mouseMoveEvent(QMouseEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "MouseEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "mouseMoveEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void wheelEvent(QWheelEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "WheelEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "wheelEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void touchEvent(QTouchEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "TouchEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "touchEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			void tabletEvent(QTabletEvent* e)
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Value> argv[] = { std::invoke([&]() {
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, e) };
						return convert::Object::Wrap(isolate, context, "TabletEvent", std::size(argv), argv);
						}) };
					call(isolate, context, "tabletEvent", std::size(argv), argv);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

		protected:
			static void SetSurfaceType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto surfaceType = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return static_cast<QSurface::SurfaceType>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QWindow::setSurfaceType>(std::move(surfaceType));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SurfaceType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::surfaceType>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsVisible(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isVisible>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetVisible(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto visible = std::invoke([&]() {
						if (!value->IsBoolean())
							throw std::invalid_argument("!`Boolean` required.");
						return value->BooleanValue(isolate);
						});
					p->d_func()->invoke<&QWindow::setVisible>(std::move(visible));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Visibility(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::visibility>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetVisibility(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto visibility = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Object` required.");
						return static_cast<QWindow::Visibility>(value->Int32Value(context).FromJust());
						});
					p->d_func()->invoke<&QWindow::setVisibility>(std::move(visibility));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Create(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::create>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WinId(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::winId>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Parent(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					QWindow* w = nullptr;

					if (args.Length() > 0) {
						auto mode = std::invoke([&]() {
							if (!args[0]->IsInt32())
								throw std::invalid_argument("!`Object` required at [0].");
							return static_cast<QWindow::AncestorMode>(args[0]->Int32Value(context).FromJust());
							});
						w = p->d_func()->invoke<qOverload<QWindow::AncestorMode>(&QWindow::parent)>(std::move(mode));
					}
					else {
						w = p->d_func()->invoke<qOverload<>(&QWindow::parent)>();
					}

					v8::Local<v8::Value>argv[] = { v8::External::New(isolate, w) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Window", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetParent(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					p->d_func()->setParent(**Window::FromValue(isolate, args[0]));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsTopLevel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isTopLevel>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsModal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isModal>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Modality(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::modality>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetModality(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto modality = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Object` required.");
						return static_cast<Qt::WindowModality>(value->Int32Value(context).FromJust());
						});
					p->d_func()->invoke<&QWindow::setModality>(std::move(modality));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void SetFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto format = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					//p->d_func()->invoke2<&QWindow::setFormat>( format);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void Format(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void RequestedFormat(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Flags(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::flags>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetFlags(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto flags = std::invoke([&]() {
						if (!value->IsObject())
							throw std::invalid_argument("!`Object` required.");
						return static_cast<Qt::WindowFlags>(value->Int32Value(context).FromJust());
						});
					p->d_func()->invoke<&QWindow::setFlags>(std::move(flags));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Flags(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::flags>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetFlag(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto flag = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return static_cast<Qt::WindowType>(args[0]->Int32Value(context).FromJust());
						});

					auto on = std::invoke([&]() {
						if (args[1]->IsBoolean())
							return args[1]->BooleanValue(isolate);
						return true;
						});

					p->d_func()->setFlag(flag, on);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Type(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::type>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Title(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = convert::String::New(isolate, p->d_func()->title());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetTitle(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto title = std::invoke([&]() {
						if (!value->IsString())
							throw std::invalid_argument("!`String` required.");
						return  convert::String::To(isolate, value);
						});
					p->d_func()->invoke<&QWindow::setTitle>(std::move(title));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetOpacity(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto opacity = std::invoke([&]() {
						if (!value->IsNumber())
							throw std::invalid_argument("!`Object` required.");
						return value->NumberValue(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setOpacity>(std::move(opacity));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Opacity(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Number::New(isolate, p->d_func()->invoke<&QWindow::opacity>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO:
			static void SetMask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto region = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QRegion>(args[0]);
						});
					p->d_func()->setMask(*region);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void Mask(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					auto region = p->d_func()->invoke<&QWindow::mask>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &region) };

					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Region", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsActive(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isActive>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void SetActive(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto title = std::invoke([&]() {
						if (!value->IsString())
							throw std::invalid_argument("!`String` required.");
						return  convert::String::To(isolate, value);
						});
					p->d_func()->invoke<&QWindow::setTitle>(std::move(title));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ContentOrientation(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::contentOrientation>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DevicePixelRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Number::New(isolate, p->d_func()->invoke<&QWindow::devicePixelRatio>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WindowState(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::windowState>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WindowStates(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::windowStates>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWindowState(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto state = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<Qt::WindowState>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QWindow::setWindowState>(std::move(state));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWindowStates(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto states = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<Qt::WindowStates>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QWindow::setWindowStates>(std::move(states));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetTransientParent(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					p->d_func()->setTransientParent(**Window::FromValue(isolate, args[0]));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void TransientParent(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					QWindow* w = p->d_func()->invoke<&QWindow::transientParent>();

					v8::Local<v8::Value>argv[] = { v8::External::New(isolate, w) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Window", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsAncestorOf(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto child = Window::FromValue(isolate, args[0]);

					auto mode = QWindow::IncludeTransients;
					if (args[1]->IsNumber())
						mode = static_cast<QWindow::AncestorMode>(args[1]->Int32Value(context).FromJust());

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isAncestorOf>(**child, mode));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsExposed(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::isExposed>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MinimumWidth(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::minimumWidth>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetMinimumWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto minimumWidth = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setMinimumWidth>(std::move(minimumWidth));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MinimumHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::minimumHeight>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetMinimumHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto minimumHeight = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setMinimumHeight>(std::move(minimumHeight));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MaximumWidth(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::maximumWidth>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetMaximumWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto maximumWidth = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setMaximumWidth>(std::move(maximumWidth));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MaximumHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::maximumHeight>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetMaximumHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto maximumHeight = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setMaximumHeight>(std::move(maximumHeight));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MinimumSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto size = p->d_func()->invoke<&QWindow::minimumSize>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &size) };

					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Size", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MaximumSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto size = p->d_func()->invoke<&QWindow::maximumSize>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &size) };

					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Size", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BaseSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto size = p->d_func()->invoke<&QWindow::baseSize>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &size) };

					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Size", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SizeIncrement(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto size = p->d_func()->invoke<&QWindow::sizeIncrement>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &size) };

					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Size", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void SetMinimumSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto size = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QSize>(args[0]);
						});

					p->d_func()->setMinimumSize(*size);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void SetMaximumSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto size = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return convert::Object::UnWrap<QSize>(args[0]);
							});

						p->d_func()->setMaximumSize(*size);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void SetBaseSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto size = std::invoke([&]() {
							if (!args[0]->IsObject())
								throw std::invalid_argument("!`Object` required at [0].");
							return convert::Object::UnWrap<QSize>(args[0]);
							});

						p->d_func()->setBaseSize(*size);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO:
			static void SetSizeIncrement(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto size = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QSize>(args[0]);
						});

					p->d_func()->setSizeIncrement(*size);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Geometry(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto rect = p->d_func()->invoke<&QWindow::geometry>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &rect) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Rect", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void FrameMargins(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					auto margins = p->d_func()->invoke<&QWindow::frameMargins>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &margins) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Margins", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FrameGeometry(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto rect = p->d_func()->invoke<&QWindow::frameGeometry>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &rect) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Rect", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FramePosition(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto point = p->d_func()->invoke<&QWindow::framePosition>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &point) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Point", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetFramePosition(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::FromValue(isolate, args[0]);
					p->d_func()->setFramePosition((***pt).toPoint());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Width(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::width>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto width = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setWidth>(std::move(width));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Height(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::height>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto height = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setHeight>(std::move(height));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void X(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::x>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetX(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto x = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setX>(std::move(x));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Y(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QWindow::y>());
					info.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetY(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());

					if (!p) {
						return;
					}
					auto y = std::invoke([&]() {
						if (!value->IsInt32())
							throw std::invalid_argument("!`Int32` required.");
						return value->Int32Value(context).FromJust();
						});
					p->d_func()->invoke<&QWindow::setY>(std::move(y));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Position(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto position = p->d_func()->invoke<&QWindow::position>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &position) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Point", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetPosition(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::FromValue(isolate, args[0]);
					p->d_func()->setPosition((***pt).toPoint());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void Resize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto newSize = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QSize>(args[0]);
						});

					p->d_func()->resize(*newSize);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetFilePath(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					QString filePath = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					p->d_func()->invoke<&QWindow::setFilePath>(filePath);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FilePath(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::String::New(isolate, p->d_func()->invoke<&QWindow::filePath>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO
			static void SetIcon(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto icon = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QIcon>(args[0]);
						});

					p->d_func()->setIcon(*icon);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void Icon(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					auto icon = p->d_func()->invoke<&QWindow::icon>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &icon) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Icon", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::destroy>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetKeyboardGrabEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto grab = std::invoke([&]() {
						if (!args[0]->IsBoolean())
							throw std::invalid_argument("!`Boolean` required at [0].");
						return args[0]->BooleanValue(isolate);
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::setKeyboardGrabEnabled>(std::move(grab)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetMouseGrabEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto grab = std::invoke([&]() {
						if (!args[0]->IsBoolean())
							throw std::invalid_argument("!`Boolean` required at [0].");
						return args[0]->BooleanValue(isolate);
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::setMouseGrabEnabled>(std::move(grab)));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			// TODO
			static void Screen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto screen = p->d_func()->invoke<&QWindow::screen>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &screen) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Screen", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void SetScreen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto* screen = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QScreen>(args[0]);
						});

					p->d_func()->invoke2<&QWindow::setScreen>( screen);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MapToGlobal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pt = Point::FromValue(isolate, args[0]);
					auto point = p->d_func()->mapToGlobal((***pt).toPoint());
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &point) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Point", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MapFromGlobal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto param = Point::FromValue(isolate, args[0]);
					auto point = p->d_func()->mapFromGlobal((***param).toPoint());
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &point) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Point", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			//TODO
			static void Cursor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto cursor = p->d_func()->invoke<&QWindow::cursor>();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &cursor) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Cursor", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void SetCursor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto cursor = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QCursor>(args[0]);
						});

					p->d_func()->setCursor(*cursor);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void UnsetCursor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::unsetCursor>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetVulkanInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto* instance = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QVulkanInstance>(args[0]);
						});

					p->d_func()->invoke2<&QWindow::setVulkanInstance>( instance);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void VulkanInstance(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					//auto result = v8::Int32::New(isolate, p->d_func()->invoke2<&QWindow::vulkanInstance>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Show(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::show>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Hide(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::hide>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowMinimized(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::showMinimized>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowMaximized(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::showMaximized>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowFullScreen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::showFullScreen>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowNormal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::showNormal>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QWindow::close>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Raise(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::raise>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Lower(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QWindow::lower>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			// TODO
			static void SetGeometry(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto rect = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QRect>(args[0]);
						});

					p->d_func()->setGeometry(*rect);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReportContentOrientationChange(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto orientation = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<Qt::ScreenOrientation>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QWindow::reportContentOrientationChange>(std::move(orientation));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FromWinId(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto id = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto* w = QWindow::fromWinId(id);
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, w) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Window", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ContentOrientationChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::contentOrientationChanged, [weakPersistent](Qt::ScreenOrientation orientation) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, orientation) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::contentOrientationChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FocusObjectChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::focusObjectChanged, [weakPersistent](QObject* object) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { std::invoke([&]() {
									v8::Local<v8::Value> argv[] = {v8::External::New(isolate, object) };
									return convert::Object::Wrap(isolate, context, "Object",  std::size(argv), argv);
									})
								};
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::focusObjectChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HeightChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::heightChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::heightChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WidthChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::widthChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::widthChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void XChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::xChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::xChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void YChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::yChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::yChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MaximumHeightChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::maximumHeightChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::maximumHeightChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MaximumWidthChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::maximumWidthChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::maximumWidthChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MinimumHeightChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::minimumHeightChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::minimumHeightChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MinimumWidthChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::minimumWidthChanged, [weakPersistent](int arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::minimumWidthChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ModalityChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::modalityChanged, [weakPersistent](Qt::WindowModality modality) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, modality) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::modalityChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScreenChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::screenChanged, [weakPersistent](QScreen* screen) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { std::invoke([&]() {
									v8::Local<v8::Value> argv[] = { v8::External::New(isolate, screen) };
									return convert::Object::Wrap(isolate, context, "Screen", std::size(argv), argv);
									}) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::screenChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void VisibleChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::visibleChanged, [weakPersistent](bool arg) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Boolean::New(isolate, arg) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::visibleChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WindowStateChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::windowStateChanged, [weakPersistent](Qt::WindowState windowState) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, windowState) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::windowStateChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WindowTitleChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QWindowWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QWindow::windowTitleChanged, [weakPersistent](const QString& title) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { convert::String::New(isolate, title) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_window) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QWindow::windowTitleChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
