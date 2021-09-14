#include "property/framework.h"
#include "qgridlayout.h"
#include "qwidget.h"
#include "qlabel.h"
#include "qtimer.h"
#include "qgroupbox.h"
#include "property/browseritem.h"
#include "property/propertysheet.h"
#include "property/abstractpropertybrowser.h"
#include "property/groupboxpropertybrowser.h"
#include "private/qwidget_p.h"
#include "property/private/abstractpropertybrowser_p.h"
#include "property/private/groupboxpropertybrowser_p.h"

namespace shelllet {
	namespace property {

	}
}
using namespace shelllet::property;
GroupBoxPropertyBrowser::GroupBoxPropertyBrowser(Object* parent /*= nullptr*/)
	:GroupBoxPropertyBrowser(*new GroupBoxPropertyBrowserPrivate, nullptr, parent)
{

}
GroupBoxPropertyBrowser::GroupBoxPropertyBrowser(GroupBoxPropertyBrowserPrivate& d, QWidget* widget, Object* parent /*= nullptr*/)
	: AbstractPropertyBrowser(d, widget)
{
	d.init(this);

}


void GroupBoxPropertyBrowserPrivate::init(QWidget* parent)
{
	m_mainLayout = new QGridLayout();
	parent->setLayout(m_mainLayout);
	QLayoutItem* item = new QSpacerItem(0, 0,
		QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_mainLayout->addItem(item, 0, 0);
}

void GroupBoxPropertyBrowserPrivate::slotEditorDestroyed()
{
	Q_Q(GroupBoxPropertyBrowser);
	QWidget* editor = qobject_cast<QWidget*>(q->sender());
	if (!editor)
		return;
	if (!m_widgetToItem.contains(editor))
		return;
	m_widgetToItem[editor]->widget = 0;
	m_widgetToItem.remove(editor);
}

void GroupBoxPropertyBrowserPrivate::slotUpdate()
{
	Q_Q(GroupBoxPropertyBrowser);
	for (WidgetItem* item : qAsConst(m_recreateQueue)) {
		WidgetItem* par = item->parent;
		QWidget* w = 0;
		QGridLayout* l = 0;
		int oldRow = -1;
		if (!par) {
			w = q;
			l = m_mainLayout;
			oldRow = m_children.indexOf(item);
		}
		else {
			w = par->groupBox;
			l = par->layout;
			oldRow = par->children.indexOf(item);
			if (hasHeader(par))
				oldRow += 2;
		}

		if (item->widget) {
			item->widget->setParent(w);
		}
		else if (item->widgetLabel) {
			item->widgetLabel->setParent(w);
		}
		else {
			item->widgetLabel = new QLabel(w);
		}
		int span = 1;
		if (item->widget)
			l->addWidget(item->widget, oldRow, 1, 1, 1);
		else if (item->widgetLabel)
			l->addWidget(item->widgetLabel, oldRow, 1, 1, 1);
		else
			span = 2;
		item->label = new QLabel(w);
		item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
		l->addWidget(item->label, oldRow, 0, 1, span);

		updateItem(item);
	}
	m_recreateQueue.clear();
}

void GroupBoxPropertyBrowserPrivate::updateLater()
{
	Q_Q(GroupBoxPropertyBrowser);
	QTimer::singleShot(0, q, SLOT(slotUpdate()));
}

void GroupBoxPropertyBrowserPrivate::propertyInserted(BrowserItem* index, BrowserItem* afterIndex)
{
	Q_Q(GroupBoxPropertyBrowser);
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
		if (parentItem) {
			row = parentItem->children.indexOf(afterItem) + 1;
			parentItem->children.insert(row, newItem);
		}
		else {
			row = m_children.indexOf(afterItem) + 1;
			m_children.insert(row, newItem);
		}
	}
	if (parentItem && hasHeader(parentItem))
		row += 2;

	if (!parentItem) {
		layout = m_mainLayout;
		parentWidget = q;;
	}
	else {
		if (!parentItem->groupBox) {
			m_recreateQueue.removeAll(parentItem);
			WidgetItem* par = parentItem->parent;
			QWidget* w = 0;
			QGridLayout* l = 0;
			int oldRow = -1;
			if (!par) {
				w = q;
				l = m_mainLayout;
				oldRow = m_children.indexOf(parentItem);
			}
			else {
				w = par->groupBox;
				l = par->layout;
				oldRow = par->children.indexOf(parentItem);
				if (hasHeader(par))
					oldRow += 2;
			}
			parentItem->groupBox = new QGroupBox(w);
			parentItem->layout = new QGridLayout();
			parentItem->groupBox->setLayout(parentItem->layout);
			if (parentItem->label) {
				l->removeWidget(parentItem->label);
				delete parentItem->label;
				parentItem->label = 0;
			}
			if (parentItem->widget) {
				l->removeWidget(parentItem->widget);
				parentItem->widget->setParent(parentItem->groupBox);
				parentItem->layout->addWidget(parentItem->widget, 0, 0, 1, 2);
				parentItem->line = new QFrame(parentItem->groupBox);
			}
			else if (parentItem->widgetLabel) {
				l->removeWidget(parentItem->widgetLabel);
				delete parentItem->widgetLabel;
				parentItem->widgetLabel = 0;
			}
			if (parentItem->line) {
				parentItem->line->setFrameShape(QFrame::HLine);
				parentItem->line->setFrameShadow(QFrame::Sunken);
				parentItem->layout->addWidget(parentItem->line, 1, 0, 1, 2);
			}
			l->addWidget(parentItem->groupBox, oldRow, 0, 1, 2);
			updateItem(parentItem);
		}
		layout = parentItem->layout;
		parentWidget = parentItem->groupBox;
	}

	newItem->label = new QLabel(parentWidget);
	newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	newItem->widget = createEditor(index->property(), parentWidget);
	if (!newItem->widget) {
		newItem->widgetLabel = new QLabel(parentWidget);
	}
	else {
		QObject::connect(newItem->widget, SIGNAL(destroyed()), q, SLOT(slotEditorDestroyed()));
		m_widgetToItem[newItem->widget] = newItem;
	}

	insertRow(layout, row);
	int span = 1;
	if (newItem->widget)
		layout->addWidget(newItem->widget, row, 1);
	else if (newItem->widgetLabel)
		layout->addWidget(newItem->widgetLabel, row, 1);
	else
		span = 2;
	layout->addWidget(newItem->label, row, 0, 1, span);

	m_itemToIndex[newItem] = index;
	m_indexToItem[index] = newItem;

	updateItem(newItem);
}

void GroupBoxPropertyBrowserPrivate::propertyRemoved(BrowserItem* index)
{
	WidgetItem* item = m_indexToItem.value(index);

	m_indexToItem.remove(index);
	m_itemToIndex.remove(item);

	WidgetItem* parentItem = item->parent;

	int row = -1;

	if (parentItem) {
		row = parentItem->children.indexOf(item);
		parentItem->children.removeAt(row);
		if (hasHeader(parentItem))
			row += 2;
	}
	else {
		row = m_children.indexOf(item);
		m_children.removeAt(row);
	}

	if (item->widget)
		delete item->widget;
	if (item->label)
		delete item->label;
	if (item->widgetLabel)
		delete item->widgetLabel;
	if (item->groupBox)
		delete item->groupBox;

	if (!parentItem) {
		removeRow(m_mainLayout, row);
	}
	else if (parentItem->children.count() != 0) {
		removeRow(parentItem->layout, row);
	}
	else {
		WidgetItem* par = parentItem->parent;
		QGridLayout* l = 0;
		int oldRow = -1;
		if (!par) {
			l = m_mainLayout;
			oldRow = m_children.indexOf(parentItem);
		}
		else {
			l = par->layout;
			oldRow = par->children.indexOf(parentItem);
			if (hasHeader(par))
				oldRow += 2;
		}

		if (parentItem->widget) {
			parentItem->widget->hide();
			parentItem->widget->setParent(0);
		}
		else if (parentItem->widgetLabel) {
			parentItem->widgetLabel->hide();
			parentItem->widgetLabel->setParent(0);
		}
		else {
			//parentItem->widgetLabel = new QLabel(w);
		}
		l->removeWidget(parentItem->groupBox);
		delete parentItem->groupBox;
		parentItem->groupBox = 0;
		parentItem->line = 0;
		parentItem->layout = 0;
		if (!m_recreateQueue.contains(parentItem))
			m_recreateQueue.append(parentItem);
		updateLater();
	}
	m_recreateQueue.removeAll(item);

	delete item;
}

void GroupBoxPropertyBrowserPrivate::insertRow(QGridLayout* layout, int row) const
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

	const QMap<QLayoutItem*, QRect>::ConstIterator icend = itemToPos.constEnd();
	for (QMap<QLayoutItem*, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
		const QRect r = it.value();
		layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
	}
}

void GroupBoxPropertyBrowserPrivate::removeRow(QGridLayout* layout, int row) const
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

	const QMap<QLayoutItem*, QRect>::ConstIterator icend = itemToPos.constEnd();
	for (QMap<QLayoutItem*, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
		const QRect r = it.value();
		layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
	}
}

bool GroupBoxPropertyBrowserPrivate::hasHeader(WidgetItem* item) const
{
	if (item->widget)
		return true;
	return false;
}

void GroupBoxPropertyBrowserPrivate::propertyChanged(BrowserItem* index)
{
	WidgetItem* item = m_indexToItem.value(index);

	updateItem(item);
}

void GroupBoxPropertyBrowserPrivate::updateItem(WidgetItem* item)
{
	PropertySheet* property = m_itemToIndex[item]->property();
	if (item->groupBox) {
		QFont font = item->groupBox->font();
		font.setUnderline(property->isModified());
		item->groupBox->setFont(font);
		item->groupBox->setTitle(property->propertyName());
		item->groupBox->setToolTip(property->descriptionToolTip());
		item->groupBox->setStatusTip(property->statusTip());
		item->groupBox->setWhatsThis(property->whatsThis());
		item->groupBox->setEnabled(property->isEnabled());
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
	//item->setIcon(1, property->valueIcon());
}

/*!
	\class GroupBoxPropertyBrowser
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The GroupBoxPropertyBrowser class provides a QGroupBox
	based property browser.

	A property browser is a widget that enables the user to edit a
	given set of properties. Each property is represented by a label
	specifying the property's name, and an editing widget (e.g. a line
	edit or a combobox) holding its value. A property can have zero or
	more subproperties.

	GroupBoxPropertyBrowser provides group boxes for all nested
	properties, i.e. subproperties are enclosed by a group box with
	the parent property's name as its title. For example:

	\image qtgroupboxpropertybrowser.png

	Use the QtAbstractPropertyBrowser API to add, insert and remove
	properties from an instance of the GroupBoxPropertyBrowser
	class. The properties themselves are created and managed by
	implementations of the QtAbstractPropertyManager class.

	\sa QtTreePropertyBrowser, QtAbstractPropertyBrowser
*/

/*!
	Creates a property browser with the given \a parent.
*/


/*!
	Destroys this property browser.

	Note that the properties that were inserted into this browser are
	\e not destroyed since they may still be used in other
	browsers. The properties are owned by the manager that created
	them.

	\sa QtProperty, QtAbstractPropertyManager
*/
GroupBoxPropertyBrowser::~GroupBoxPropertyBrowser()
{
	Q_D(GroupBoxPropertyBrowser);
	const QMap<GroupBoxPropertyBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator icend = d->m_itemToIndex.constEnd();
	for (QMap<GroupBoxPropertyBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator it = d->m_itemToIndex.constBegin(); it != icend; ++it)
		delete it.key();
}

/*!
	\reimp
*/
void GroupBoxPropertyBrowser::itemInserted(BrowserItem* item, BrowserItem* afterItem)
{
	Q_D(GroupBoxPropertyBrowser);
	d->propertyInserted(item, afterItem);
}

/*!
	\reimp
*/
void GroupBoxPropertyBrowser::itemRemoved(BrowserItem* item)
{
	Q_D(GroupBoxPropertyBrowser);
	d->propertyRemoved(item);
}

/*!
	\reimp
*/
void GroupBoxPropertyBrowser::itemChanged(BrowserItem* item)
{
	Q_D(GroupBoxPropertyBrowser);
	d->propertyChanged(item);
}