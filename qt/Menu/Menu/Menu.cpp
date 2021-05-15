#include "Menu.h"
#include <qmenu.h>
#include "QLineEdit"
#include "QWidgetAction"

#include "qdebug.h"
Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


	menu.addSection(QIcon(":/Menu/gamer"), "Widget Menu Section");

	menu.addAction(QIcon(":/Menu/gamer"), "Options");
	menu.addAction("Exit");
	menu.addSection("Widget Menu Section");

	QWidgetAction* action = new QWidgetAction(&menu);

	action->setDefaultWidget(new QLineEdit());


	menu.addAction(action);


	qDebug() << menu.isTearOffEnabled();


	if (!menu.isTearOffEnabled()) {

		menu.setTearOffEnabled(true);


	}
}

void Menu::contextMenuEvent(QContextMenuEvent* event)
{
	//throw std::logic_error("The method or operation is not implemented.");


  


    menu.exec(QCursor::pos());
}
