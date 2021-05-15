#pragma once

#include <QWidget>
#include "ui_QtNewWidgets.h"

class QtNewWidgets : public QWidget
{
	Q_OBJECT

public:
	QtNewWidgets(QWidget *parent = Q_NULLPTR);
	~QtNewWidgets();

signals:
	void closed();
private:
	Ui::QtNewWidgets ui;

protected:
	void closeEvent(QCloseEvent* event) override;

};
