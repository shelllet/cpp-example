#pragma once
#include "common.hpp"
namespace shelllet {
	namespace scintilla {
		class ScintillaApiWrapper
		{
		public:
			void setText(const String& text);
			String text() const;
			void setSavePoint();
			void setStyleJavaScript();
			void setUtf8Encode();
			void disablePopup();
			virtual intptr_t sendMessage(unsigned int message, uintptr_t wParam = 0, intptr_t lParam = 0) const = 0;
			int get_current_pos() const;
			int get_word_start_pos(int pos) const;
			int get_word_end_pos(int pos) const;
			bool isModified() const;
			void showAuto(const char* items, int lengthEntered);
			String getAutoCurrentText();
			String get_text_range(int cpMin, int cpMax) const;
			void formatText();
		};
	}
}
