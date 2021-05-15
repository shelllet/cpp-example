#include "Page2.h"
#include "QVBoxLayout"

#include "QPushButton"
#include "QMessageBox"
#include "QVariant"
Page2::Page2()
{
	setTitle("Page2");

	setSubTitle("this is page2");


	setLayout(new QVBoxLayout);

	auto* button = new QPushButton(this);

	layout()->addWidget(button);

	connect(button, &QPushButton::clicked, [this]() {
		QMessageBox::information(this, "display linedit value", field("lineEdit").toString());
		});
}
