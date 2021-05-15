#include "Options.h"

Options::Options(QWidget *parent)
	: QWidget(parent)
	, setting("Shelllet")
	
{
	ui.setupUi(this);

	connect(ui.keySequenceEdit, &QKeySequenceEdit::keySequenceChanged, [this]() {
				setting.setValue("open", ui.keySequenceEdit->keySequence());
		
		});

	if (setting.contains("open")) {
		ui.keySequenceEdit->setKeySequence(setting.value("open").value<QKeySequence>());
	}
}

Options::~Options()
{
}

QKeySequence Options::getSequence()
{
	return ui.keySequenceEdit->keySequence();
}
