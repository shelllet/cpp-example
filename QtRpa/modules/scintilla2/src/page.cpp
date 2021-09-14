#include "scintilla/page.h"
#include "common/code.h"
#include "common/format.h"


shelllet::scintilla::ScintillaPage::ScintillaPage( QWidget* parent /*= nullptr*/)
	: ScintillaPage("", parent)

{
	
}

shelllet::scintilla::ScintillaPage::ScintillaPage(const String& text, QWidget* parent /*= nullptr*/)
	: scintilla_component(parent)
{
	setUtf8Encode();
	setStyleJavaScript();
	setSavePoint();

	setText(text);
}

shelllet::scintilla::ScintillaPage::~ScintillaPage()
{
}


