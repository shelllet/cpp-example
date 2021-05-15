#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KeySequence.h"
#include <QShortcut>
#include "Options.h"
class KeySequence : public QMainWindow
{
    Q_OBJECT

public:
    KeySequence(QWidget *parent = Q_NULLPTR);

private:
    Ui::KeySequenceClass ui;

    QShortcut shortcut;

    Options options;
};
