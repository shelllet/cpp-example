#include <qcoreapplication.h>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "wizard/createpage.h"
#include "wizard/framework.h"


shelllet::wizard::CreatePage::CreatePage(QWidget* parent)
	: QWizardPage(parent)
{
	auto* vLayout = new QVBoxLayout;

	vLayout->addWidget(new QLabel(tr("Project Name")));

	lineEdit_ = new QLineEdit(this);
	vLayout->addWidget(lineEdit_);

	vLayout->addWidget(new QLabel(tr("Location")));

	auto* layout = new QFormLayout;
	comboBox_ = new QComboBox(this);
	QPushButton* button = new QPushButton(this);

	layout->addRow(comboBox_, button);

	vLayout->addLayout(layout);

	setLayout(vLayout);
}

shelllet::wizard::CreatePage::~CreatePage()
{
}
