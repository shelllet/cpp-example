#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Thread.h"
#include <QFile>
#include <QMutex>
#include <QReadWriteLock>
class Thread : public QMainWindow
{
    Q_OBJECT

public:
    Thread(QWidget *parent = Q_NULLPTR);


public slots:
    void save();
    void set();
    void test();
    void mainTest();
    void moveToThread();
public:
    QString text() const;
private:
    Ui::ThreadClass ui;
    QFile file = { "./setting.txt" };
    QMutex mutex;
    QReadWriteLock locker;
};
