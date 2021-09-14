#include "creator.hpp"
#include <windows.h>
#include <QVBoxLayout>
#include "scintilla/scintilla_component.h"
#include <commctrl.h>


shelllet::scintilla::scintilla_component::scintilla_component(QWidget* parent)
	: QWidget(parent) {
	setLayout(new QVBoxLayout());
	layout()->addWidget(createWindowContainer(createEditor(this), this));
}

shelllet::scintilla::scintilla_component::~scintilla_component()
{
	destroyWndResource();
}

bool shelllet::scintilla::scintilla_component::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	if (eventType == "windows_generic_MSG") {
		MSG* msg = static_cast<MSG*>(message);

		switch (msg->message)
		{
		case WM_NOTIFY:
			LOG_INFO("rpa") << "# wm_notify";
			break;
		default:
			break;
		}
	}

	return false;
}