#include "KeySequence.h"
#include "QtNewWidgets.h"

KeySequence::KeySequence(QWidget* parent)
	: QMainWindow(parent)
	, shortcut(this)
{
	ui.setupUi(this);

	connect(ui.actionopen, &QAction::triggered, [this]() {
		options.show();		
		});
	
	

	shortcut.setKey(options.getSequence());

	connect(&shortcut, &QShortcut::activated, [this]() {
		QtNewWidgets* widget = new QtNewWidgets();
		widget->show();

		connect(widget, &QtNewWidgets::closed, [widget]() { widget->deleteLater(); });
		});
}
