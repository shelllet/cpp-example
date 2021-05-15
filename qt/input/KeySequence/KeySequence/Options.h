#pragma once

#include <QWidget>
#include "ui_Options.h"
#include <QKeySequence>
#include <QSettings>

class Options : public QWidget
{
	Q_OBJECT

public:
	Options(QWidget *parent = Q_NULLPTR);
	~Options();

	QKeySequence getSequence();
private:
	Ui::Options ui;

	QSettings setting;
};
