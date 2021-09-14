#include <Scintilla.h>
#include "scintilla/scintilla_api_wrapper.h"
#include "scintilla/scintilla_module_manager.h"
#include "SciLexer.h"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/join.hpp>

void shelllet::scintilla::ScintillaApiWrapper::setText(const String& text)
{
	sendMessage(SCI_SETTEXT, 0, (sptr_t)text.data());
}

String shelllet::scintilla::ScintillaApiWrapper::text() const
{
	sptr_t n = sendMessage(SCI_GETTEXT);
	if (n > 0) {
		std::vector<char> block(--n);

		sendMessage(SCI_GETTEXT, n, (sptr_t)&block[0]);

		return std::string(block.begin(), block.end());
	}
	return "";
}

void shelllet::scintilla::ScintillaApiWrapper::setSavePoint()
{
	sendMessage(SCI_SETSAVEPOINT);
}

void shelllet::scintilla::ScintillaApiWrapper::setStyleJavaScript()
{
	const char* keywords = "var break require new";
	sendMessage(SCI_SETLEXER, SCLEX_ESCRIPT);
	sendMessage(SCI_SETKEYWORDS, 0, (sptr_t)keywords);

	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_DEFAULT, 0x222222);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_COMMENT, 0x00008000);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_COMMENTLINE, 0x007500);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_COMMENTDOC, 0x007500);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_NUMBER, 0x6500D4);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_WORD, 0x222286);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_STRING, 0x4b505d);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_OPERATOR, 0x994500);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_IDENTIFIER, 0xAB0D9E);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_BRACE, 0x222222);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_WORD2, 0x91CDFF);
	sendMessage(SCI_STYLESETFORE, SCE_ESCRIPT_WORD3, 0xC9E4FF);

	sendMessage(SCI_SETCARETLINEVISIBLE, true);
	sendMessage(SCI_SETCARETLINEBACK, 0xb0ffff);
	sendMessage(SCI_SETTABWIDTH, 4);

	sendMessage(SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER);
	sendMessage(SCI_SETMARGINWIDTHN, 0, 20);
}

void shelllet::scintilla::ScintillaApiWrapper::setUtf8Encode()
{
	sendMessage(SCI_SETCODEPAGE, SC_CP_UTF8);
}

void shelllet::scintilla::ScintillaApiWrapper::disablePopup()
{
	sendMessage(SCI_USEPOPUP, SC_POPUP_NEVER);
}

int shelllet::scintilla::ScintillaApiWrapper::get_current_pos() const
{
	return sendMessage(SCI_GETCURRENTPOS);
}

int shelllet::scintilla::ScintillaApiWrapper::get_word_start_pos(int pos) const
{
	return sendMessage(SCI_WORDSTARTPOSITION, pos);
}

int shelllet::scintilla::ScintillaApiWrapper::get_word_end_pos(int pos) const
{
	return sendMessage(SCI_WORDENDPOSITION, pos);
}

bool shelllet::scintilla::ScintillaApiWrapper::isModified() const
{
	return sendMessage(SCI_GETMODIFY);
}

void shelllet::scintilla::ScintillaApiWrapper::showAuto(const char* items, int lengthEntered)
{
	sendMessage(SCI_AUTOCSHOW, lengthEntered, (sptr_t)items);
}

String shelllet::scintilla::ScintillaApiWrapper::getAutoCurrentText()
{
	int len = sendMessage(SCI_AUTOCGETCURRENTTEXT, 0, 0);

	std::vector<char> text(len + 1);

	sendMessage(SCI_AUTOCGETCURRENTTEXT, 0, (sptr_t)text.data());

	return text.data();
}

String shelllet::scintilla::ScintillaApiWrapper::get_text_range(int cpMin, int cpMax) const
{
	Sci_TextRange textRange;
	// including the terminating 0
	std::vector<char> text(cpMax - cpMin + 1);
	textRange.chrg.cpMin = cpMin;
	textRange.chrg.cpMax = cpMax;
	textRange.lpstrText = text.data();

	sendMessage(SCI_GETTEXTRANGE, 0, (sptr_t)&textRange);
	//std::set delim = { ' \0','\t','\r','\n' };

	boost::trim_if(text, boost::is_any_of("\r\n" + std::string("\0", 1)));

	if (text.empty()) {
		return "";
	}

	return text;
}

void shelllet::scintilla::ScintillaApiWrapper::formatText()
{
}