#include "qmenu.h"
#include "framelesswindow.h"
#include "titlebarwidget.h"
#include "delegatewindow.h"
#include "private/qwidget_p.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qgraphicseffect.h"
#include "qscreen.h"
#include "qboxlayout.h"
#include "qstyleoption.h"
#include "qt_windows.h"
#include "windowsx.h"
#include "qstackedwidget.h"
#include "dwmapi.h"
#include "private/framelesswindow_p.h"



shelllet::frameless::FramelessWindow::FramelessWindow(QWidget* parent /*= nullptr*/, WindowTypeFlags flags /*= {}*/)
	: FramelessWindow(*new FramelessWindowPrivate, parent, flags)
{
	Q_D(FramelessWindow);
	setObjectName("app-main-window");
}
shelllet::frameless::FramelessWindow::FramelessWindow(FramelessWindowPrivate& d, QWidget* parent /*= nullptr*/, WindowTypeFlags flags /*= WindowFlags()*/)
	: QMainWindow(parent, Qt::FramelessWindowHint)
	, Object(d, nullptr)
{
	d.flags = flags;
	HWND hWnd = reinterpret_cast<HWND>(winId());
	d.currentStyle = GetWindowLong(hWnd, GWL_STYLE);
	d.currentExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	setContentsMargins(1, 1, 1, 1);
	disableNativeTitleBar();
}

shelllet::frameless::FramelessWindow::~FramelessWindow() {
	Q_D(FramelessWindow);
	delete d->delegateWindow;
}

void shelllet::frameless::FramelessWindow::setCustomButton(QWidget* c)
{
	Q_D(FramelessWindow);
	if (d->titleBar)
		d->titleBar->setCustomButton(c);
}



void shelllet::frameless::FramelessWindow::setContextMenu(QMenu* menu)
{
	Q_D(FramelessWindow);
	d->menu = menu;
}

void shelllet::frameless::FramelessWindow::setTitleTextBlurRadius(qreal blurRadius)
{
	Q_D(FramelessWindow);
	if (d->titleBar)
		d->titleBar->setTitleTextBlurRadius(blurRadius);
}


void shelllet::frameless::FramelessWindow::enableNativeTitleBar()
{
	Q_D(FramelessWindow);
	HWND hWnd = reinterpret_cast<HWND>(winId());
	{
		SetWindowLongW(hWnd, GWL_STYLE, d->currentStyle);
		SetWindowLongW(hWnd, GWL_EXSTYLE, d->currentExStyle);

		MARGINS margins = { 0 };
		DwmExtendFrameIntoClientArea(hWnd, &margins);
	}
	d->delegateWindow->updateWindow(hWnd, true, true);
	if (d->titleBar) {
		delete d->titleBar;
		d->titleBar = nullptr;
	}
	setMenuWidget(nullptr);
	if (d->delegateWindow) {
		delete d->delegateWindow;
		d->delegateWindow = nullptr;
	}
	setWindowFlag(Qt::Window, true);
	setWindowFlag(Qt::FramelessWindowHint, false);
}


void shelllet::frameless::FramelessWindow::disableNativeTitleBar()
{
	Q_D(FramelessWindow);
	HWND hWnd = reinterpret_cast<HWND>(winId());
	{
		SetWindowLongW(hWnd, GWL_STYLE, d->currentStyle | WS_OVERLAPPEDWINDOW | WS_SIZEBOX);
		//SetWindowLongW(hWnd, GWL_EXSTYLE, d->currentExStyle | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, RGB(255, 0, 0), 0, LWA_COLORKEY);

		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
		DwmSetWindowAttribute(hWnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
		MARGINS margins = { 0, 0, 0, 0 };
		DwmExtendFrameIntoClientArea(hWnd, &margins);
	}

	d->titleBar = new TitleBarWidget;
	d->delegateWindow = new DelegateWindow(d->titleBar);
	d->titleBar->setWindowTypes(d->flags);

	d->titleBar->setFixedHeight(d->delegateWindow->getSystemTitleBarHeight(hWnd));
	connect(d->titleBar, &TitleBarWidget::closeButtonClicked, this, &FramelessWindow::closeButtonClicked);
	connect(d->titleBar, &TitleBarWidget::minimizeButtonClicked, this, &FramelessWindow::minimizeButtonClicked);
	connect(d->titleBar, &TitleBarWidget::maximizeButtonClicked, this, &FramelessWindow::maximizeButtonClicked);
	connect(d->titleBar, &TitleBarWidget::restoreButtonClicked, this, &FramelessWindow::restoreButtonClicked);
	connect(d->titleBar, &TitleBarWidget::iconDoubleClicked, this, &FramelessWindow::iconDoubleClicked);

	connect(this, &FramelessWindow::windowTitleChanged, d->titleBar, &TitleBarWidget::windowTitleChanged);
	connect(this, &FramelessWindow::windowIconChanged, d->titleBar, &TitleBarWidget::windowIconChanged);

	setMenuWidget(d->titleBar);
	setWindowFlag(Qt::FramelessWindowHint, true);
	setWindowFlag(Qt::Window, false);
}

void shelllet::frameless::FramelessWindow::minimizeButtonClicked() {
	Q_D(FramelessWindow);
	showMinimized();
}

void shelllet::frameless::FramelessWindow::restoreButtonClicked() {
	Q_D(FramelessWindow);
	showNormal();
}

void shelllet::frameless::FramelessWindow::maximizeButtonClicked() {
	Q_D(FramelessWindow);

	showMaximized();
}

void shelllet::frameless::FramelessWindow::closeButtonClicked() { close(); }


void shelllet::frameless::FramelessWindow::iconDoubleClicked()
{
	close();
}

void shelllet::frameless::FramelessWindow::paintEvent(QPaintEvent* event)
{
	Q_D(FramelessWindow);
	if (d->titleBar) {
		QStyleOption styleOption;
		styleOption.initFrom(this);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		QPen pen;
		pen.setColor(QColor(58, 58, 58));
		QBrush brush(QColor(58, 58, 58));
		painter.setPen(pen);
		painter.setBrush(brush);
		painter.drawRect(rect());
		//QPainterPath path;
		//path.addRoundedRect(rect(), 0, 0);

		//painter.drawPath(path);
	}
	else {
		__super::paintEvent(event);
	}
}

void shelllet::frameless::FramelessWindow::changeEvent(QEvent* event)
{
	Q_D(FramelessWindow);
	if (event->type() == QEvent::WindowStateChange)
	{
		QWindowStateChangeEvent* e = dynamic_cast<QWindowStateChangeEvent*>(event);
		if (!(e->oldState() & Qt::WindowMaximized) && (windowState() & Qt::WindowMaximized))
		{
			if (d->titleBar) {
				d->titleBar->setFixedHeight(d->delegateWindow->getSystemTitleBarHeight(reinterpret_cast<HWND>(winId())));
				d->titleBar->switchToRestoreButton();
			}
		}
		else if ((e->oldState() & Qt::WindowMaximized) && (windowState() != Qt::WindowMaximized))
		{
			if (d->titleBar) {
				d->titleBar->setFixedHeight(d->delegateWindow->getSystemTitleBarHeight(reinterpret_cast<HWND>(winId())));
				if (!isMaximized())
					d->titleBar->switchToMaxButton();
			}
		}
	}
	__super::changeEvent(event);
}

bool shelllet::frameless::FramelessWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_D(FramelessWindow);
	LPMSG lpMsg = reinterpret_cast<LPMSG>(message);
	if (!d->titleBar) {
		return __super::nativeEvent(eventType, message, result);
	}
	switch (lpMsg->message) {
	case WM_NCCALCSIZE:
		if (lpMsg->wParam) {

			d->delegateWindow->calcNcSize(lpMsg->hwnd, lpMsg->wParam, lpMsg->lParam);
			*result = WVR_REDRAW;
			return true;
		}
		break;
	case WM_NCHITTEST:
	{
		POINT pt = { GET_X_LPARAM(lpMsg->lParam), GET_Y_LPARAM(lpMsg->lParam) };

		ScreenToClient(lpMsg->hwnd, &pt);
		RECT rc;
		GetClientRect(lpMsg->hwnd, &rc);
		*result = d->delegateWindow->hitNcTest(lpMsg->hwnd, { pt.x, pt.y }, { rc.left,rc.top, rc.right - rc.left, rc.bottom - rc.top }, fixedSizeTypes());
		return *result != 0;
	}
	case WM_DPICHANGED:
		d->delegateWindow->updateWindow(lpMsg->hwnd, true, true);
		break;
	case WM_GETMINMAXINFO:
		*result = ::DefWindowProc(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
		return true;
	case WM_MOVE:
		d->delegateWindow->updateWindow(lpMsg->hwnd, true, true);
		break;
	case WM_NCACTIVATE:
		*result = DefWindowProcW(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, -1);
		return true;
	case WM_NCLBUTTONDBLCLK:
		if (!d->flags.testFlag(WindowType::MaximizeButtonHint))
			return true;
		*result = DefWindowProcW(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, -1);
		return true;
	case WM_NCRBUTTONDOWN:
		if (d->menu)
			d->menu->exec(QCursor::pos());
	}
	return false;
}
