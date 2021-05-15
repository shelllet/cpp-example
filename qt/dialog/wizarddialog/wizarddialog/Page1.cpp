#include "Page1.h"
#include "QVBoxLayout"
#include "QLineEdit"
Page1::Page1()
{
	setTitle("Page1");

	setSubTitle("this is page1");

	setLayout(new QVBoxLayout);

	auto* lineEdit = new QLineEdit(this);
	lineEdit->setFixedWidth(200);
	layout()->addWidget(lineEdit);


	registerField("lineEdit*", lineEdit);

}
