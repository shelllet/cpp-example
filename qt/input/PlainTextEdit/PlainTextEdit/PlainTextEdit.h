#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlainTextEdit.h"

class PlainTextEdit : public QMainWindow
{
    Q_OBJECT

public:
    PlainTextEdit(QWidget *parent = Q_NULLPTR);
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::PlainTextEditClass ui;
};
