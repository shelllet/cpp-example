#include "qt_windows.h"
#include "delegatewindow.h"
#include "titlebarwidget.h"
#include "qapplication.h"
#include "qlibrary.h"
#include "wrl.h"
#include "d2d1.h"
#include "qoperatingsystemversion.h"
#include "qwindow.h"
#include "qdebug.h"
#include "common/logs.h"
namespace shelllet {
	using namespace Microsoft::WRL;
	namespace frameless {
#ifdef _DEBUG
#define JWF_RESOLVE_ERROR(funcName) Q_ASSERT(m_lp##funcName);
#else
#define JWF_RESOLVE_ERROR(funcName) \
    if (!m_lp##funcName) { \
        LOG_FATAL("frameless") << "Failed to resolve symbol: " #funcName << std::endl; \
    }
#endif

#define JWF_GENERATE_WINAPI(funcName, retType, ...) \
    using WINAPI_##funcName = retType(WINAPI *)(__VA_ARGS__); \
    static WINAPI_##funcName m_lp##funcName = nullptr;

#define JWF_RESOLVE_WINAPI(libName, funcName) \
    if (!m_lp##funcName) { \
        m_lp##funcName = reinterpret_cast<WINAPI_##funcName>( \
            QLibrary::resolve(QString::fromUtf8(#libName), #funcName)); \
        JWF_RESOLVE_ERROR(funcName) \
    }

		JWF_GENERATE_WINAPI(GetSystemMetricsForDpi, int, int, UINT)
			JWF_GENERATE_WINAPI(GetDpiForWindow, UINT, HWND)
			static	ComPtr<ID2D1Factory> m_pDirect2dFactory;

		enum AppbarAutohideEdge {
			EDGE_TOP = 1 << 0,
			EDGE_LEFT = 1 << 1,
			EDGE_BOTTOM = 1 << 2,
			EDGE_RIGHT = 1 << 3,
		};

		class DelegateWindowPrivate : public ObjectPrivate {
		public:
			TitleBarWidget* titleBar;
		};

		bool __MonitorHasAutohideTaskbarForEdge(UINT edge, HMONITOR monitor) {
			APPBARDATA taskbarData = { sizeof(APPBARDATA), NULL, 0, edge };
			taskbarData.hWnd = ::GetForegroundWindow();
			// MSDN documents an ABM_GETAUTOHIDEBAREX, which supposedly takes a monitor
			// rect and returns autohide bars on that monitor.  This sounds like a good
			// idea for multi-monitor systems.  Unfortunately, it appears to not work at
			// least some of the time (erroneously returning NULL) and there's almost no
			// online documentation or other sample code using it that suggests ways to
			// address this problem. We do the following:-
			// 1. Use the ABM_GETAUTOHIDEBAR message. If it works, i.e. returns a valid
			//    window we are done.
			// 2. If the ABM_GETAUTOHIDEBAR message does not work we query the auto hide
			//    state of the taskbar and then retrieve its position. That call returns
			//    the edge on which the taskbar is present. If it matches the edge we
			//    are looking for, we are done.
			// NOTE: This call spins a nested run loop.
			HWND taskbar = reinterpret_cast<HWND>(SHAppBarMessage(ABM_GETAUTOHIDEBAR, &taskbarData));
			if (!::IsWindow(taskbar)) {
				APPBARDATA taskbarData = { sizeof(APPBARDATA), 0, 0, 0 };
				unsigned int taskbar_state = SHAppBarMessage(ABM_GETSTATE, &taskbarData);
				if (!(taskbar_state & ABS_AUTOHIDE))
					return false;
				taskbarData.hWnd = ::FindWindowW(L"Shell_TrayWnd", NULL);
				if (!::IsWindow(taskbarData.hWnd))
					return false;
				SHAppBarMessage(ABM_GETTASKBARPOS, &taskbarData);
				if (taskbarData.uEdge == edge)
					taskbar = taskbarData.hWnd;
			}
			// There is a potential race condition here:
			// 1. A maximized chrome window is fullscreened.
			// 2. It is switched back to maximized.
			// 3. In the process the window gets a WM_NCCACLSIZE message which calls us to
			//    get the autohide state.
			// 4. The worker thread is invoked. It calls the API to get the autohide
			//    state. On Windows versions  earlier than Windows 7, taskbars could
			//    easily be always on top or not.
			//    This meant that we only want to look for taskbars which have the topmost
			//    bit set.  However this causes problems in cases where the window on the
			//    main thread is still in the process of switching away from fullscreen.
			//    In this case the taskbar might not yet have the topmost bit set.
			// 5. The main thread resumes and does not leave space for the taskbar and
			//    hence it does not pop when hovered.
			//
			// To address point 4 above, it is best to not check for the WS_EX_TOPMOST
			// window style on the taskbar, as starting from Windows 7, the topmost
			// style is always set. We don't support XP and Vista anymore.
			if (::IsWindow(taskbar)) {
				if (MonitorFromWindow(taskbar, MONITOR_DEFAULTTONEAREST) == monitor)
					return true;
				// In some cases like when the autohide taskbar is on the left of the
				// secondary monitor, the MonitorFromWindow call above fails to return the
				// correct monitor the taskbar is on. We fallback to MonitorFromPoint for
				// the cursor position in that case, which seems to work well.
				POINT cursorPos = { 0 };
				GetCursorPos(&cursorPos);
				if (MonitorFromPoint(cursorPos, MONITOR_DEFAULTTONEAREST) == monitor)
					return true;
			}
			return false;
		}
		int __GetAppbarAutohideEdges(HMONITOR monitor) {
			int edges = 0;
			if (__MonitorHasAutohideTaskbarForEdge(ABE_LEFT, monitor))
				edges |= EDGE_LEFT;
			if (__MonitorHasAutohideTaskbarForEdge(ABE_TOP, monitor))
				edges |= EDGE_TOP;
			if (__MonitorHasAutohideTaskbarForEdge(ABE_RIGHT, monitor))
				edges |= EDGE_RIGHT;
			if (__MonitorHasAutohideTaskbarForEdge(ABE_BOTTOM, monitor))
				edges |= EDGE_BOTTOM;
			return edges;
		}
		int __GetSystemMetricsForDpi(int nIndex, UINT dpi) {
			if (m_lpGetSystemMetricsForDpi)
				return m_lpGetSystemMetricsForDpi(nIndex, dpi);

			return GetSystemMetrics(nIndex);
		}
		UINT __GetDpiForWindow(HWND hWnd) {
			if (m_lpGetDpiForWindow)
				return m_lpGetDpiForWindow(hWnd);

			FLOAT dpiX = 96.0, dpiY = 96.0;
			if (m_pDirect2dFactory)
				m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

			return qRound(dpiX);
		}

		MONITORINFO __GetMonitorInfoForWindow(HWND hWnd)
		{
			HMONITOR mon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi = { .cbSize = sizeof mi };
			GetMonitorInfoW(mon, &mi);
			return mi;
		}

		int __GetBorderWidthForWindow(HWND hWnd) {
			uint dpi = __GetDpiForWindow(hWnd);
			return __GetSystemMetricsForDpi(SM_CXSIZEFRAME, dpi) + __GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
		}

	}
}


shelllet::frameless::DelegateWindow::DelegateWindow(TitleBarWidget* widget)
	: Object(*new DelegateWindowPrivate, nullptr)
{
	Q_D(DelegateWindow);

	d->titleBar = widget;

	if (QOperatingSystemVersion::current() >= QOperatingSystemVersion::Windows10) {
		JWF_RESOLVE_WINAPI(User32, GetSystemMetricsForDpi)
			JWF_RESOLVE_WINAPI(User32, GetDpiForWindow)
	}

	if (!m_pDirect2dFactory) {
		HRESULT hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_pDirect2dFactory.GetAddressOf());
		if (FAILED(hResult)) {
			LOG_FATAL("frameless") << "Failed to create d2d factory: " << std::system_category().message(hResult) << std::endl;
		}
	}
}

bool shelllet::frameless::DelegateWindow::calcNcSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Q_D(DelegateWindow);
	union {
		LPARAM lParam;
		RECT* rect;
	} params = { .lParam = lParam };
	RECT ncclient = *params.rect;
	DefWindowProcW(hWnd, WM_NCCALCSIZE, wParam, params.lParam);
	RECT client = *params.rect;
	if (::IsZoomed(hWnd))
	{
		int borderWidth = __GetBorderWidthForWindow(hWnd);
		*params.rect = {
			.left = client.left,
			.top = ncclient.top + static_cast<LONG>(borderWidth), // Maximized window always have a border around.
			.right = client.right,
			.bottom = client.bottom,
		};

		HMONITOR mon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = __GetMonitorInfoForWindow(hWnd);

		// reduce size when same monitor's rectangle.
		if (EqualRect(params.rect, &mi.rcMonitor)) {
			if (__GetAppbarAutohideEdges(mon) == EDGE_TOP) {
				params.rect->top++;
			}
			else if (__GetAppbarAutohideEdges(mon) == EDGE_LEFT) {
				params.rect->left++;
			}
			else if (__GetAppbarAutohideEdges(mon) == EDGE_BOTTOM) {
				params.rect->bottom--;
			}
			else if (__GetAppbarAutohideEdges(mon) == EDGE_RIGHT) {
				params.rect->right--;
			}
		}
		QWindow* window = QWindow::fromWinId(reinterpret_cast<WId>(hWnd));
		d->titleBar->setMaximumWidth(window->size().width());
	}
	else {
		*params.rect = ncclient;

		d->titleBar->setMaximumWidth(QWIDGETSIZE_MAX);
	}
	return true;
}


void shelllet::frameless::DelegateWindow::updateWindow(HWND hWnd, bool frameChange, bool redraw)
{
	if (frameChange) {
		SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}
	if (redraw) {
		//RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
		RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_ERASENOW | RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_NOCHILDREN);
	}
}

int shelllet::frameless::DelegateWindow::getSystemTitleBarHeight(HWND hWnd)
{
	const UINT dpi = 96;

	if (IsZoomed(hWnd)) {
		return qRound(__GetSystemMetricsForDpi(SM_CYCAPTION, dpi) * 0.75) + 5;
	}

	return __GetSystemMetricsForDpi(SM_CYCAPTION, dpi) +5;
}

long shelllet::frameless::DelegateWindow::hitNcTest(HWND hWnd, const QPoint& pos, const QRect& geometry, const SizePolicyFlags& flags)
{
	Q_D(DelegateWindow);
	int borderWidth = __GetBorderWidthForWindow(hWnd);
	QRect rcMax = geometry;
	QRect rcMin = geometry.marginsRemoved({ borderWidth, borderWidth, borderWidth, borderWidth });

	QRect rcLeft = { QPoint{rcMax.left(), rcMin.top()}, rcMin.bottomLeft() };
	QRect rcTop = { QPoint{rcMin.left(), rcMax.top()}, rcMin.topRight() };

	QRect rctRight = { rcMin.topRight(),QPoint(rcMax.right(), rcMin.bottom()) };
	QRect rcBottom = { rcMin.bottomLeft(), QPoint(rcMin.right(), rcMax.bottom()) };


	QRect rcTopLeft = { rcMax.topLeft(), rcMin.topLeft() };
	QRect rcTopRight = { QPoint{rcMin.right(), rcMax.top()}, QPoint(rcMax.right(), rcMin.top()) };

	QRect rcBottomLeft = { QPoint(rcMax.left(), rcMin.bottom()),QPoint(rcMin.left(), rcMax.bottom()) };
	QRect rcBottomRight = { rcMin.bottomRight(), rcMax.bottomRight() };

	if (rcLeft.contains(pos)) {
		return flags.testFlag(SizePolicy::FixedWidth) ? HTCLIENT : HTLEFT;
	}
	else if (rctRight.contains(pos)) {
		return flags.testFlag(SizePolicy::FixedWidth) ? HTCLIENT : HTRIGHT;
	}
	else if (rcBottom.contains(pos)) {
		return flags.testFlag(SizePolicy::FixedHeigth) ? HTCLIENT : HTBOTTOM;
	}
	else if (rcTop.contains(pos)) {
		return flags.testFlag(SizePolicy::FixedHeigth) ? HTCLIENT : HTTOP;
	}
	else if (rcBottomLeft.contains(pos)) {
		return (flags.testFlag(SizePolicy::FixedHeigth) || flags.testFlag(SizePolicy::FixedWidth)) ? HTCLIENT : HTBOTTOMLEFT;
	}
	else if (rcBottomRight.contains(pos)) {
		return (flags.testFlag(SizePolicy::FixedHeigth) || flags.testFlag(SizePolicy::FixedWidth)) ? HTCLIENT : HTBOTTOMRIGHT;
	}
	else if (rcTopRight.contains(pos)) {
		return (flags.testFlag(SizePolicy::FixedHeigth) || flags.testFlag(SizePolicy::FixedWidth)) ? HTCLIENT : HTTOPRIGHT;
	}
	else if (rcTopLeft.contains(pos)) {
		return (flags.testFlag(SizePolicy::FixedHeigth) || flags.testFlag(SizePolicy::FixedWidth)) ? HTCLIENT : HTTOPLEFT;
	}
	else if (d->titleBar->underMouse()) {
		return HTCAPTION;
	}

	return HTCLIENT;
}
