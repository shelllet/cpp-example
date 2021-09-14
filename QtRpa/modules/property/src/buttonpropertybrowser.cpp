#include "property/framework.h"
#include "qwidget.h"
#include "qtoolbutton.h"
#include "qlabel.h"
#include "qgridlayout.h"
#include "qtimer.h"
#include "property/propertysheet.h"
#include "property/browseritem.h"
#include "property/abstracteditorfactorybase.h"
#include "property/abstracteditorfactory.h"
#include "property/abstractpropertybrowser.h"
#include "property/buttonpropertybrowser.h"
#include "private/qwidget_p.h"
#include "property/private/abstractpropertybrowser_p.h"
#include "property/private/buttonpropertybrowser_p.h"

namespace shelllet{
    namespace property{
        
    }
}
using namespace shelllet::property;
ButtonPropertyBrowser::ButtonPropertyBrowser(Object* parent /*= nullptr*/)
    :ButtonPropertyBrowser(*new ButtonPropertyBrowserPrivate, nullptr, parent)
{

}
ButtonPropertyBrowser::ButtonPropertyBrowser(ButtonPropertyBrowserPrivate& d, QWidget* parent1, Object* parent /*= nullptr*/)
	: AbstractPropertyBrowser(d, parent1)
{
	d.init(this);

}



QToolButton* ButtonPropertyBrowserPrivate::createButton(QWidget* parent) const
{
	QToolButton* button = new QToolButton(parent);
	button->setCheckable(true);
	button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
	button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	button->setArrowType(Qt::DownArrow);
	button->setIconSize(QSize(3, 16));
	/*
	QIcon icon;
	icon.addPixmap(q_ptr->style()->standardPixmap(QStyle::SP_ArrowDown), QIcon::Normal, QIcon::Off);
	icon.addPixmap(q_ptr->style()->standardPixmap(QStyle::SP_ArrowUp), QIcon::Normal, QIcon::On);
	button->setIcon(icon);
	*/
	return button;
}

int ButtonPropertyBrowserPrivate::gridRow(WidgetItem* item) const
{
	QList<WidgetItem*> siblings;
	if (item->parent)
		siblings = item->parent->children;
	else
		siblings = m_children;

	int row = 0;
	for (WidgetItem* sibling : qAsConst(siblings)) {
		if (sibling == item)
			return row;
		row += gridSpan(sibling);
	}
	return -1;
}

int ButtonPropertyBrowserPrivate::gridSpan(WidgetItem* item) const
{
	if (item->container && item->expanded)
		return 2;
	return 1;
}

void ButtonPropertyBrowserPrivate::init(QWidget* parent)
{
	m_mainLayout = new QGridLayout();
	parent->setLayout(m_mainLayout);
	QLayoutItem* item = new QSpacerItem(0, 0,
		QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_mainLayout->addItem(item, 0, 0);
}

void ButtonPropertyBrowserPrivate::slotEditorDestroyed()
{
	Q_Q(ButtonPropertyBrowser);
	QWidget* editor = qobject_cast<QWidget*>(q->sender());
	if (!editor)
		return;
	if (!m_widgetToItem.contains(editor))
		return;
	m_widgetToItem[editor]->widget = 0;
	m_widgetToItem.remove(editor);
}

void ButtonPropertyBrowserPrivate::slotUpdate()
{
	Q_Q(ButtonPropertyBrowser);
	for (WidgetItem* item : qAsConst(m_recreateQueue)) {
		WidgetItem* parent = item->parent;
		QWidget* w = 0;
		QGridLayout* l = 0;
		const int oldRow = gridRow(item);
		if (parent) {
			w = parent->container;
			l = parent->layout;
		}
		else {
			w = q;
			l = m_mainLayout;
		}

		int span = 1;
		if (!item->widget && !item->widgetLabel)
			span = 2;
		item->label = new QLabel(w);
		item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
		l->addWidget(item->label, oldRow, 0, 1, span);

		updateItem(item);
	}
	m_recreateQueue.clear();
}

void ButtonPropertyBrowserPrivate::setExpanded(WidgetItem* item, bool expanded)
{
	if (item->expanded == expanded)
		return;

	if (!item->container)
		return;

	item->expanded = expanded;
	const int row = gridRow(item);
	WidgetItem* parent = item->parent;
	QGridLayout* l = 0;
	if (parent)
		l = parent->layout;
	else
		l = m_mainLayout;

	if (expanded) {
		insertRow(l, row + 1);
		l->addWidget(item->container, row + 1, 0, 1, 2);
		item->container->show();
	}
	else {
		l->removeWidget(item->container);
		item->container->hide();
		removeRow(l, row + 1);
	}

	item->button->setChecked(expanded);
	item->button->setArrowType(expanded ? Qt::UpArrow : Qt::DownArrow);
}

void ButtonPropertyBrowserPrivate::slotToggled(bool checked)
{
	Q_Q(ButtonPropertyBrowser);
	WidgetItem* item = m_buttonToItem.value(q->sender());
	if (!item)
		return;

	setExpanded(item, checked);

	if (checked)
		emit q->expanded(m_itemToIndex.value(item));
	else
		emit q->collapsed(m_itemToIndex.value(item));
}

void ButtonPropertyBrowserPrivate::updateLater()
{
	Q_Q(ButtonPropertyBrowser);
	QTimer::singleShot(0, q, SLOT(slotUpdate()));
}

void ButtonPropertyBrowserPrivate::propertyInserted(BrowserItem* index, BrowserItem* afterIndex)
{
	Q_Q(ButtonPropertyBrowser);
	WidgetItem* afterItem = m_indexToItem.value(afterIndex);
	WidgetItem* parentItem = m_indexToItem.value(index->parent());

	WidgetItem* newItem = new WidgetItem();
	newItem->parent = parentItem;

	QGridLayout* layout = 0;
	QWidget* parentWidget = 0;
	int row = -1;
	if (!afterItem) {
		row = 0;
		if (parentItem)
			parentItem->children.insert(0, newItem);
		else
			m_children.insert(0, newItem);
	}
	else {
		row = gridRow(afterItem) + gridSpan(afterItem);
		if (parentItem)
			parentItem->children.insert(parentItem->children.indexOf(afterItem) + 1, newItem);
		else
			m_children.insert(m_children.indexOf(afterItem) + 1, newItem);
	}

	if (!parentItem) {
		layout = m_mainLayout;
		parentWidget = q;
	}
	else {
		if (!parentItem->container) {
			m_recreateQueue.removeAll(parentItem);
			WidgetItem* grandParent = parentItem->parent;
			QGridLayout* l = 0;
			const int oldRow = gridRow(parentItem);
			if (grandParent) {
				l = grandParent->layout;
			}
			else {
				l = m_mainLayout;
			}
			QFrame* container = new QFrame();
			container->setFrameShape(QFrame::Panel);
			container->setFrameShadow(QFrame::Raised);
			parentItem->container = container;
			parentItem->button = createButton();
			m_buttonToItem[parentItem->button] = parentItem;
			q->connect(parentItem->button, SIGNAL(toggled(bool)), q_ptr, SLOT(slotToggled(bool)));
			parentItem->layout = new QGridLayout();
			container->setLayout(parentItem->layout);
			if (parentItem->label) {
				l->removeWidget(parentItem->label);
				delete parentItem->label;
				parentItem->label = 0;
			}
			int span = 1;
			if (!parentItem->widget && !parentItem->widgetLabel)
				span = 2;
			l->addWidget(parentItem->button, oldRow, 0, 1, span);
			updateItem(parentItem);
		}
		layout = parentItem->layout;
		parentWidget = parentItem->container;
	}

	newItem->label = new QLabel(parentWidget);
	newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	newItem->widget = createEditor(index->property(), parentWidget);
	if (newItem->widget) {
		QObject::connect(newItem->widget, SIGNAL(destroyed()), q, SLOT(slotEditorDestroyed()));
		m_widgetToItem[newItem->widget] = newItem;
	}
	else if (index->property()->hasValue()) {
		newItem->widgetLabel = new QLabel(parentWidget);
		newItem->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
	}

	insertRow(layout, row);
	int span = 1;
	if (newItem->widget)
		layout->addWidget(newItem->widget, row, 1);
	else if (newItem->widgetLabel)
		layout->addWidget(newItem->widgetLabel, row, 1);
	else
		span = 2;
	layout->addWidget(newItem->label, row, 0, span, 1);

	m_itemToIndex[newItem] = index;
	m_indexToItem[index] = newItem;

	updateItem(newItem);
}

void ButtonPropertyBrowserPrivate::propertyRemoved(BrowserItem* index)
{
	WidgetItem* item = m_indexToItem.value(index);

	m_indexToItem.remove(index);
	m_itemToIndex.remove(item);

	WidgetItem* parentItem = item->parent;

	const int row = gridRow(item);

	if (parentItem)
		parentItem->children.removeAt(parentItem->children.indexOf(item));
	else
		m_children.removeAt(m_children.indexOf(item));

	const int colSpan = gridSpan(item);

	m_buttonToItem.remove(item->button);

	if (item->widget)
		delete item->widget;
	if (item->label)
		delete item->label;
	if (item->widgetLabel)
		delete item->widgetLabel;
	if (item->button)
		delete item->button;
	if (item->container)
		delete item->container;

	if (!parentItem) {
		removeRow(m_mainLayout, row);
		if (colSpan > 1)
			removeRow(m_mainLayout, row);
	}
	else if (parentItem->children.count() != 0) {
		removeRow(parentItem->layout, row);
		if (colSpan > 1)
			removeRow(parentItem->layout, row);
	}
	else {
		const WidgetItem* grandParent = parentItem->parent;
		QGridLayout* l = 0;
		if (grandParent) {
			l = grandParent->layout;
		}
		else {
			l = m_mainLayout;
		}

		const int parentRow = gridRow(parentItem);
		const int parentSpan = gridSpan(parentItem);

		l->removeWidget(parentItem->button);
		l->removeWidget(parentItem->container);
		delete parentItem->button;
		delete parentItem->container;
		parentItem->button = 0;
		parentItem->container = 0;
		parentItem->layout = 0;
		if (!m_recreateQueue.contains(parentItem))
			m_recreateQueue.append(parentItem);
		if (parentSpan > 1)
			removeRow(l, parentRow + 1);

		updateLater();
	}
	m_recreateQueue.removeAll(item);

	delete item;
}

void ButtonPropertyBrowserPrivate::insertRow(QGridLayout* layout, int row) const
{
	QMap<QLayoutItem*, QRect> itemToPos;
	int idx = 0;
	while (idx < layout->count()) {
		int r, c, rs, cs;
		layout->getItemPosition(idx, &r, &c, &rs, &cs);
		if (r >= row) {
			itemToPos[layout->takeAt(idx)] = QRect(r + 1, c, rs, cs);
		}
		else {
			idx++;
		}
	}

	for (auto it = itemToPos.constBegin(), icend = itemToPos.constEnd(); it != icend; ++it) {
		const QRect r = it.value();
		layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
	}
}

void ButtonPropertyBrowserPrivate::removeRow(QGridLayout* layout, int row) const
{
	QMap<QLayoutItem*, QRect> itemToPos;
	int idx = 0;
	while (idx < layout->count()) {
		int r, c, rs, cs;
		layout->getItemPosition(idx, &r, &c, &rs, &cs);
		if (r > row) {
			itemToPos[layout->takeAt(idx)] = QRect(r - 1, c, rs, cs);
		}
		else {
			idx++;
		}
	}

	for (auto it = itemToPos.constBegin(), icend = itemToPos.constEnd(); it != icend; ++it) {
		const QRect r = it.value();
		layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
	}
}

void ButtonPropertyBrowserPrivate::propertyChanged(BrowserItem* index)
{
	WidgetItem* item = m_indexToItem.value(index);

	updateItem(item);
}

void ButtonPropertyBrowserPrivate::updateItem(WidgetItem* item)
{
	PropertySheet* property = m_itemToIndex[item]->property();
	if (item->button) {
		QFont font = item->button->font();
		font.setUnderline(property->isModified());
		item->button->setFont(font);
		item->button->setText(property->propertyName());
		item->button->setToolTip(property->descriptionToolTip());
		item->button->setStatusTip(property->statusTip());
		item->button->setWhatsThis(property->whatsThis());
		item->button->setEnabled(property->isEnabled());
	}
	if (item->label) {
		QFont font = item->label->font();
		font.setUnderline(property->isModified());
		item->label->setFont(font);
		item->label->setText(property->propertyName());
		item->label->setToolTip(property->descriptionToolTip());
		item->label->setStatusTip(property->statusTip());
		item->label->setWhatsThis(property->whatsThis());
		item->label->setEnabled(property->isEnabled());
	}
	if (item->widgetLabel) {
		QFont font = item->widgetLabel->font();
		font.setUnderline(false);
		item->widgetLabel->setFont(font);
		item->widgetLabel->setText(*property->valueText().toQString());
		item->widgetLabel->setToolTip(*property->valueText().toQString());
		item->widgetLabel->setEnabled(property->isEnabled());
	}
	if (item->widget) {
		QFont font = item->widget->font();
		font.setUnderline(false);
		item->widget->setFont(font);
		item->widget->setEnabled(property->isEnabled());
		const QString valueToolTip = property->valueToolTip();
		item->widget->setToolTip(valueToolTip.isEmpty() ? *property->valueText().toQString() : valueToolTip);
	}
}

/*!
	\class ButtonPropertyBrowser
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The ButtonPropertyBrowser class provides a drop down QToolButton
	based property browser.

	A property browser is a widget that enables the user to edit a
	given set of properties. Each property is represented by a label
	specifying the property's name, and an editing widget (e.g. a line
	edit or a combobox) holding its value. A property can have zero or
	more subproperties.

	ButtonPropertyBrowser provides drop down button for all nested
	properties, i.e. subproperties are enclosed by a container associated with
	the drop down button. The parent property's name is displayed as button text. For example:

	\image qtbuttonpropertybrowser.png

	Use the QtAbstractPropertyBrowser API to add, insert and remove
	properties from an instance of the ButtonPropertyBrowser
	class. The properties themselves are created and managed by
	implementations of the QtAbstractPropertyManager class.

	\sa QtTreePropertyBrowser, QtAbstractPropertyBrowser
*/

/*!
	\fn void ButtonPropertyBrowser::collapsed(BrowserItem *item)

	This signal is emitted when the \a item is collapsed.

	\sa expanded(), setExpanded()
*/

/*!
	\fn void ButtonPropertyBrowser::expanded(BrowserItem *item)

	This signal is emitted when the \a item is expanded.

	\sa collapsed(), setExpanded()
*/

/*!
	Creates a property browser with the given \a parent.
*/
ButtonPropertyBrowser::ButtonPropertyBrowser(QWidget* parent)
	: ButtonPropertyBrowser(*new ButtonPropertyBrowserPrivate, parent)
{
	

}

/*!
	Destroys this property browser.

	Note that the properties that were inserted into this browser are
	\e not destroyed since they may still be used in other
	browsers. The properties are owned by the manager that created
	them.

	\sa PropertySheet, QtAbstractPropertyManager
*/
ButtonPropertyBrowser::~ButtonPropertyBrowser()
{
	Q_D(ButtonPropertyBrowser);
	const QMap<ButtonPropertyBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator icend = d->m_itemToIndex.constEnd();
	for (QMap<ButtonPropertyBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator it = d->m_itemToIndex.constBegin(); it != icend; ++it)
		delete it.key();
}

/*!
	\reimp
*/
void ButtonPropertyBrowser::itemInserted(BrowserItem* item, BrowserItem* afterItem)
{
	Q_D(ButtonPropertyBrowser);
	d->propertyInserted(item, afterItem);
}

/*!
	\reimp
*/
void ButtonPropertyBrowser::itemRemoved(BrowserItem* item)
{
	Q_D(ButtonPropertyBrowser);
	d->propertyRemoved(item);
}

/*!
	\reimp
*/
void ButtonPropertyBrowser::itemChanged(BrowserItem* item)
{
	Q_D(ButtonPropertyBrowser);
	d->propertyChanged(item);
}

/*!
	Sets the \a item to either collapse or expanded, depending on the value of \a expanded.

	\sa isExpanded(), expanded(), collapsed()
*/

void ButtonPropertyBrowser::setExpanded(BrowserItem* item, bool expanded)
{
	Q_D(ButtonPropertyBrowser);
	ButtonPropertyBrowserPrivate::WidgetItem* itm = d->m_indexToItem.value(item);
	if (itm)
		d->setExpanded(itm, expanded);
}

/*!
	Returns true if the \a item is expanded; otherwise returns false.

	\sa setExpanded()
*/

bool ButtonPropertyBrowser::isExpanded(BrowserItem* item) const
{
	Q_D(const ButtonPropertyBrowser);
	ButtonPropertyBrowserPrivate::WidgetItem* itm = d->m_indexToItem.value(item);
	if (itm)
		return itm->expanded;
	return false;
}
