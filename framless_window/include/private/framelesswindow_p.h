#pragma once
#include <intsafe.h>
namespace QT_NAMESPACE {
	class QMenu;
}
namespace shelllet {
	namespace frameless {
		class DelegateWindow;
		class TitleBarWidget;
		class FramelessWindowPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(FramelessWindow)
		public:
			DelegateWindow* delegateWindow = nullptr;
			QMenu* menu = nullptr;
			TitleBarWidget* titleBar = nullptr;
			WindowTypeFlags flags;
			LONG currentStyle;
			LONG currentExStyle;
		};
	}
}