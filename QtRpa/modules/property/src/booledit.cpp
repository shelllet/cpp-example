#include "property/framework.h"
#include "qcheckbox.h"
#include "qlayout.h"
#include "property/booledit.h"
#include "private/qwidget_p.h"
#include "property/private/booledit_p.h"

namespace shelllet{
    namespace property{
        
    }
}
using namespace shelllet::property;
BoolEdit::BoolEdit(Object* parent /*= nullptr*/)
    :BoolEdit(*new BoolEditPrivate, nullptr)
{

}
BoolEdit::BoolEdit(BoolEditPrivate& d, QWidget* parent /*= nullptr*/)
	: QWidget(d, parent, Qt::WindowFlags())
	, m_checkBox(new QCheckBox(this)),
	m_textVisible(true)
{
	QHBoxLayout* lt = new QHBoxLayout;
	if (QApplication::layoutDirection() == Qt::LeftToRight)
		lt->setContentsMargins(4, 0, 0, 0);
	else
		lt->setContentsMargins(0, 0, 4, 0);
	lt->addWidget(m_checkBox);
	setLayout(lt);
	connect(m_checkBox, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
	setFocusProxy(m_checkBox);
	m_checkBox->setText(tr("True"));
}



void BoolEdit::setTextVisible(bool textVisible)
{
	if (m_textVisible == textVisible)
		return;

	m_textVisible = textVisible;
	if (m_textVisible)
		m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
	else
		m_checkBox->setText(QString());
}

Qt::CheckState BoolEdit::checkState() const
{
	return m_checkBox->checkState();
}

void BoolEdit::setCheckState(Qt::CheckState state)
{
	m_checkBox->setCheckState(state);
}

bool BoolEdit::isChecked() const
{
	return m_checkBox->isChecked();
}

void BoolEdit::setChecked(bool c)
{
	m_checkBox->setChecked(c);
	if (!m_textVisible)
		return;
	m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
}

bool BoolEdit::blockCheckBoxSignals(bool block)
{
	return m_checkBox->blockSignals(block);
}

void BoolEdit::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton) {
		m_checkBox->click();
		event->accept();
	}
	else {
		QWidget::mousePressEvent(event);
	}
}