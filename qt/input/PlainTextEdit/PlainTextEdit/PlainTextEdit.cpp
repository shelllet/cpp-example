#include "PlainTextEdit.h"
#include "MyHighlighter.h"

PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    MyHighlighter* highlighter = new MyHighlighter(this);

    highlighter->setDocument(ui.plainTextEdit->document());

    //ui.plainTextEdit->setReadOnly(true);
	ui.plainTextEdit->installEventFilter(this);
}
bool PlainTextEdit::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ui.plainTextEdit && event->type() == QEvent::Wheel)
	{
		QWheelEvent* wheel = static_cast<QWheelEvent*>(event);
		if (wheel->modifiers() == Qt::ControlModifier)
			if (wheel->delta() > 0)
				ui.plainTextEdit->zoomIn(2);
			else
				ui.plainTextEdit->zoomOut(2);
		
	}
	return false;
}