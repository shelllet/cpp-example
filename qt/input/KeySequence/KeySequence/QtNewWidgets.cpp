#include "QtNewWidgets.h"

QtNewWidgets::QtNewWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtNewWidgets::~QtNewWidgets()
{
}

void QtNewWidgets::closeEvent(QCloseEvent* event)
{
	emit closed();
}