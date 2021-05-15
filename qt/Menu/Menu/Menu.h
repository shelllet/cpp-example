#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Menu.h"

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = Q_NULLPTR);

private:
    Ui::MenuClass ui;

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    QMenu menu;
};
