#include <Scintilla.h>
#include "scintilla/scintilla_module_manager.h"
#include <windows.h>
#include "qwidget.h"
extern "C" {
	extern sptr_t Scintilla_DirectFunction(sptr_t sci, UINT iMessage, uptr_t wParam, sptr_t lParam);
}
namespace shelllet {
	using namespace scintilla;
	typedef sptr_t(*F)(sptr_t, unsigned int, uptr_t, sptr_t);

	//F Scintilla_DirectFunction;

	std::vector<std::pair<HWND, ScintillaModuleManager*>> ScintillaInOnePeer;
}

shelllet::scintilla::ScintillaModuleManager::ScintillaModuleManager()
{
	libray.setFileName("SciLexer.dll");

	//Scintilla_DirectFunction = reinterpret_cast<F>(libray.resolve("Scintilla_DirectFunction"));
}

shelllet::scintilla::ScintillaModuleManager::~ScintillaModuleManager()
{
	destroyWndResource();
}
namespace shelllet {
	LRESULT CALLBACK HookWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		using namespace scintilla;

		auto iter = std::find_if(ScintillaInOnePeer.begin(), ScintillaInOnePeer.end(), [hwnd](const std::pair<HWND, ScintillaModuleManager*>& p)
		{
			return hwnd == p.first;
		});

		BOOST_ASSERT(iter != ScintillaInOnePeer.end());

		if (message == WM_COMMAND) {
			WORD wNotification = HIWORD(wParam);

			if (wNotification == SCEN_CHANGE)
			{
			}
		}
		else if (message == WM_NOTIFY) {
			SCNotification* notify = (SCNotification*)lParam;

			//(*iter).second->emit2(notify->nmhdr.code);
		}
		else if (message == WM_DESTROY) {
			//LOG_SEV_TRACE << "# WM_DESTROY" << std::endl;
		}

		//	return CallWindowProc((*iter).second->getPeerWndProc(), hwnd, message, wParam, lParam);
		return 0;
	}

	LRESULT ScintillaProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		using namespace scintilla;
		LONG_PTR lPtr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		ScintillaModuleManager* scintilla = reinterpret_cast<ScintillaModuleManager*>(lPtr);

		if (message == WM_ERASEBKGND) {
			return TRUE;
		}
		else if (message == WM_CONTEXTMENU) {
			//PopupMenu m;
		//	m.addItem(1, "format code");
			//const int result = m.show();
			//if (result == 1)
			{
				// user dismissed the menu without picking anything
				//instance->getActionBroadcaster().sendActionMessage(FORMAT_CODE_ACTION_TEXT);
			}
		}
		else if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN) {
			//if (KeyPress::isKeyCurrentlyDown('f')
			//	&& ModifierKeys::getCurrentModifiersRealtime().testFlags(ModifierKeys::altModifier
			//		| ModifierKeys::shiftModifier)) {
			//	//instance->getActionBroadcaster().sendActionMessage(FORMAT_CODE_ACTION_TEXT);
			//}
		}

		else if (message == WM_SIZE) {
			RedrawWindow(hwnd,
				NULL, NULL,
				RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_FRAME);
		}

		//		return CallWindowProc(scintilla->getWndProc(), hwnd, message, wParam, lParam);
	}
}
QWindow* shelllet::scintilla::ScintillaModuleManager::createEditor(QWidget* parent)
{
	//if (!::IsWindow(wndProc_.first)) {
		//LOG_SEV_ERROR << "the style `WS_CHILD` must have owner window" << std::endl;
	//	return NULL;
	//}
	WId wid = parent->winId();
	auto hwnd = CreateWindowExW(0,
		L"Scintilla", L"", WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN,
		0, 0,
		1, 1, reinterpret_cast<HWND>(wid), NULL, (NULL), NULL);

	int n = GetLastError();
	if (hwnd == NULL || !::IsWindow(hwnd)) {
		LOG_WARNING("rpa") << std::system_error(n, std::system_category()).what();
		return nullptr;
	}

	sci_ = ::SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0i64);

	SetLastError(0);
	if (SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this) == 0 && GetLastError() != 0) {
		//boost::system::system_error err(GetLastError(), boost::system::detail::system_error_category());
		//qCCritical("rpa") << err.what();
		return nullptr;
	}
	//WNDPROC proc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
	//SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)ScintillaProc);
	//data_ = std::make_tuple(hwnd, proc, sci);

	return QWindow::fromWinId(WId(hwnd));
}
//
//std::vector<std::tuple<HWND, WNDPROC, sptr_t>>::iterator shelllet::core::ScintillaModuleManager::find(uint32_t sci)
//{
//	return std::find_if(hWndDatas.begin(), hWndDatas.end(), [sci](const std::tuple<HWND, WNDPROC, sptr_t>& p)
//		{
//			return sci == reinterpret_cast<uint32_t>(std::get<0>(p));
//		});
//}

//void shelllet::core::ScintillaModuleManager::removeEditor(HWND hWnd)
//{
	//std::remove_if(hWndDatas.begin(), hWndDatas.end(), [this, hWnd](const HwndData& p)
	//	{
	//		if (hWnd == p.hWnd) {
	//
	//			return true;
	//		}
	//		return false;
	//	});

	//destroyWndResource(&p);
//}

void shelllet::scintilla::ScintillaModuleManager::hookWndProc(HWND hwnd)
{
	//	if (!wndProc_.first) {
		//	wndProc_.first = hWnd;

	auto iter = std::find_if(ScintillaInOnePeer.begin(), ScintillaInOnePeer.end(), [this](const std::pair<HWND, ScintillaModuleManager*>& p)
	{
		return this == p.second;
	});

	if (iter != ScintillaInOnePeer.end()) {
		return;
	}

	ScintillaInOnePeer.push_back(std::make_pair(hwnd, this));
	WNDPROC proc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);

	if (HookWndProc != proc) {
		//		peerWndProc = std::make_pair(hwnd, proc);
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)HookWndProc);
		//SetWindowLongPtr(hwnd, DWLP_USER_PEER, (LONG_PTR)&ScintillaInOnePeer);
	}

	//	}
}

void shelllet::scintilla::ScintillaModuleManager::destroyWndResource()
{
	//	if (::IsWindow(peerWndProc.first)) {
		//	SetWindowLongPtr(peerWndProc.first, GWLP_WNDPROC, (LONG_PTR)peerWndProc.second);
		//}

		//if (::IsWindow(getHwnd())) {
	//		DestroyWindow(getHwnd());
	//	}
	static_cast<void>(std::remove_if(ScintillaInOnePeer.begin(), ScintillaInOnePeer.end(), [this](const std::pair<HWND, ScintillaModuleManager*>& p) {
		return this == p.second;
	}));
}

intptr_t shelllet::scintilla::ScintillaModuleManager::sendMessage(unsigned int message, uintptr_t wParam /*= 0*/, intptr_t lParam /*= 0*/) const
{
	if (sci_)
		return Scintilla_DirectFunction(sci_, message, wParam, lParam);

	throw std::runtime_error("error@ scintilla");
}