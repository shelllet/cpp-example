#pragma once
#include <QWindow>

#include <qlibrary.h>
#include "scintilla_api_wrapper.h"
namespace shelllet {
	namespace scintilla {
#define FORMAT_CODE_ACTION_TEXT  "#FORMATCODE"
#define CHAR_ADDED_ACTION_TEXT  "#CHARADDED"

		class ScintillaModuleManager : public ScintillaApiWrapper
		{
		public:
			ScintillaModuleManager();
			virtual ~ScintillaModuleManager();
		public:
			void hookWndProc(HWND hwnd);
			intptr_t sendMessage(unsigned int message, uintptr_t wParam = 0, intptr_t lParam = 0) const;

			QWindow* createEditor(QWidget* parent);
	
		
			void destroyWndResource();
			//	std::vector<std::tuple<HWND, WNDPROC, sptr_t>>::iterator find(uint32_t sci);
		public:
		private:
			QLibrary libray;
			intptr_t sci_ = 0;
		};
	}
}
