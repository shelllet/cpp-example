#include "property/framework.h"
#include "qitemdelegate.h"
#include "qtreewidget.h"
#include "qpainter.h"
#include "qapplication.h"
#include "property/propertysheet.h"
#include "property/qtpropertybrowser.h"
#include "property/abstractpropertybrowser.h"
#include "property/propertybrowser.h"
#include "property/browseritem.h"
#include "property/propertyeditorview.h"
#include "private/qwidget_p.h"
#include "property/private/abstractpropertybrowser_p.h"
#include "property/private/propertybrowser_p.h"
#include "property/propertyeditordelegate.h"
#include "property/private/propertyeditordelegate_p.h"
#include "common/wobjectimpl.h"
namespace shelllet {
	namespace property {



	}
}
using namespace shelllet::property;

W_OBJECT_IMPL(PropertyEditorDelegate)
PropertyEditorDelegate::PropertyEditorDelegate(Object* parent /*= nullptr*/)
	:PropertyEditorDelegate(*new PropertyEditorDelegatePrivate, nullptr, parent)
{

}

PropertyEditorDelegate::PropertyEditorDelegate(QObject* parent /*= 0*/)
	: PropertyEditorDelegate(*new PropertyEditorDelegatePrivate, parent)
{

}

PropertyEditorDelegate::PropertyEditorDelegate(PropertyEditorDelegatePrivate& d, QObject* parent1, Object* parent /*= nullptr*/)
	: QItemDelegate(parent1)
	, m_editorPrivate(0), m_editedItem(0), m_editedWidget(0)
{

}




int PropertyEditorDelegate::indentation(const QModelIndex& index) const
{
	if (!m_editorPrivate)
		return 0;

	QTreeWidgetItem* item = m_editorPrivate->indexToItem(index);
	int indent = 0;
	while (item->parent()) {
		item = item->parent();
		++indent;
	}
	if (m_editorPrivate->treeWidget()->rootIsDecorated())
		++indent;
	return indent * m_editorPrivate->treeWidget()->indentation();
}

void PropertyEditorDelegate::slotEditorDestroyed(QObject* object)
{
	if (QWidget* w = qobject_cast<QWidget*>(object)) {
		const EditorToPropertyMap::iterator it = m_editorToProperty.find(w);
		if (it != m_editorToProperty.end()) {
			m_propertyToEditor.remove(it.value());
			m_editorToProperty.erase(it);
		}
		if (m_editedWidget == w) {
			m_editedWidget = 0;
			m_editedItem = 0;
		}
	}
}

void PropertyEditorDelegate::closeEditor(PropertySheet* property)
{
	if (QWidget* w = m_propertyToEditor.value(property, 0))
		w->deleteLater();
}

QWidget* PropertyEditorDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem&, const QModelIndex& index) const
{
	if (index.column() == 1 && m_editorPrivate) {
		PropertySheet* property = m_editorPrivate->indexToProperty(index);
		QTreeWidgetItem* item = m_editorPrivate->indexToItem(index);
		if (property && item && (item->flags() & Qt::ItemIsEnabled)) {
			QWidget* editor = m_editorPrivate->createEditor(property, parent);
			if (editor) {
				editor->setAutoFillBackground(true);
				editor->installEventFilter(const_cast<PropertyEditorDelegate*>(this));
				connect(editor, &QWidget::destroyed, this, &PropertyEditorDelegate::slotEditorDestroyed);
				m_propertyToEditor[property] = editor;
				m_editorToProperty[editor] = property;
				m_editedItem = item;
				m_editedWidget = editor;
			}
			return editor;
		}
	}
	return 0;
}

void PropertyEditorDelegate::updateEditorGeometry(QWidget* editor,
	const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	Q_UNUSED(index);
	editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));
}

void PropertyEditorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	bool hasValue = true;
	if (m_editorPrivate) {
		PropertySheet* property = m_editorPrivate->indexToProperty(index);
		if (property)
			hasValue = property->hasValue();
	}
	QStyleOptionViewItem opt = option;
	if ((m_editorPrivate && index.column() == 0) || !hasValue) {
		PropertySheet* property = m_editorPrivate->indexToProperty(index);
		if (property && property->isModified()) {
			opt.font.setBold(true);
			opt.fontMetrics = QFontMetrics(opt.font);
		}
	}
	QColor c;
	if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
		c = opt.palette.color(QPalette::Dark);
		opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
	}
	else {
		c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
		if (c.isValid() && (opt.features & QStyleOptionViewItem::Alternate))
			c = c.lighter(112);
	}
	if (c.isValid())
		painter->fillRect(option.rect, c);
	opt.state &= ~QStyle::State_HasFocus;
	QItemDelegate::paint(painter, opt, index);

	opt.palette.setCurrentColorGroup(QPalette::Active);
	QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
	painter->save();
	painter->setPen(QPen(color));
	if (!m_editorPrivate || (!m_editorPrivate->lastColumn(index.column()) && hasValue)) {
		int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
		painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
	}
	painter->restore();
}

QSize PropertyEditorDelegate::sizeHint(const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	return QItemDelegate::sizeHint(option, index) + QSize(3, 4);
}

bool PropertyEditorDelegate::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::FocusOut) {
		QFocusEvent* fe = static_cast<QFocusEvent*>(event);
		if (fe->reason() == Qt::ActiveWindowFocusReason)
			return false;
	}
	return QItemDelegate::eventFilter(object, event);
}
