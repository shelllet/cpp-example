#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrayIcon.h"
#include "QSystemTrayIcon"
#include "qmenu.h"
class TrayIcon : public QMainWindow
{
    Q_OBJECT

public:
    TrayIcon(QWidget *parent = Q_NULLPTR);

private:
    Ui::TrayIconClass ui;

  
    QSystemTrayIcon trayIcon;
    QMenu menu;
};
