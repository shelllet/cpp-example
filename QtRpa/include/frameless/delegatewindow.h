#pragma once
#include "common.hpp"
#include "qt_windows.h"
#include "flags.h"
namespace shelllet {
	namespace frameless {
		class TitleBarWidget;
		class DelegateWindowPrivate;
		class DelegateWindow : public Object
		{
			Q_DECLARE_PRIVATE(DelegateWindow)
		public:
			DelegateWindow(TitleBarWidget* widget);

			long hitNcTest(HWND hWnd, const QPoint& pos, const QRect& geometry, const SizePolicyFlags& flags);
			bool calcNcSize(HWND hWnd, WPARAM wParam, LPARAM lParam);

			void updateWindow(HWND hWnd, bool frameChange, bool redraw);

			int getSystemTitleBarHeight(HWND hWnd);
		};
	}
}