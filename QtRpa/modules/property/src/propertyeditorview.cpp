#include "property/framework.h"
#include "qtreewidget.h"
#include "qpainter.h"
#include "qheaderview.h"
#include "property/propertysheet.h"
#include "property/qtpropertybrowser.h"

#include "property/abstractpropertybrowser.h"
#include "property/propertybrowser.h"
#include "property/propertyeditorview.h"
#include "private/qwidget_p.h"
#include "property/private/abstractpropertybrowser_p.h"
#include "property/private/propertybrowser_p.h"
#include "property/private/propertyeditorview_p.h"
#include "common/wobjectimpl.h"
namespace shelllet {
	namespace property {

	}
}
using namespace shelllet::property;

W_OBJECT_IMPL(PropertyEditorView)
PropertyEditorView::PropertyEditorView(Object* parent /*= nullptr*/)
	:PropertyEditorView(*new PropertyEditorViewPrivate,nullptr, parent)
{

}
PropertyEditorView::PropertyEditorView(PropertyEditorViewPrivate& d, QWidget* parent1/* = 0*/, Object* parent /*= nullptr*/)
	: QTreeWidget(parent1)
	,
	m_editorPrivate(0)
	//, Object(d, parent)
{

}


PropertyEditorView::PropertyEditorView(QWidget* parent) :
	PropertyEditorView(*new PropertyEditorViewPrivate, parent)
{
	connect(header(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(resizeColumnToContents(int)));
}

void PropertyEditorView::drawRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem opt = option;
	bool hasValue = true;
	if (m_editorPrivate) {
		PropertySheet* property = m_editorPrivate->indexToProperty(index);
		if (property)
			hasValue = property->hasValue();
	}
	if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
		const QColor c = option.palette.color(QPalette::Dark);
		painter->fillRect(option.rect, c);
		opt.palette.setColor(QPalette::AlternateBase, c);
	}
	else {
		const QColor c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
		if (c.isValid()) {
			painter->fillRect(option.rect, c);
			opt.palette.setColor(QPalette::AlternateBase, c.lighter(112));
		}
	}
	QTreeWidget::drawRow(painter, opt, index);
	QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
	painter->save();
	painter->setPen(QPen(color));
	painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
	painter->restore();
}

void PropertyEditorView::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
	case Qt::Key_Return:
	case Qt::Key_Enter:
	case Qt::Key_Space: // Trigger Edit
		if (!m_editorPrivate->editedItem())
			if (const QTreeWidgetItem* item = currentItem())
				if (item->columnCount() >= 2 && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
					event->accept();
					// If the current position is at column 0, move to 1.
					QModelIndex index = currentIndex();
					if (index.column() == 0) {
						index = index.sibling(index.row(), 1);
						setCurrentIndex(index);
					}
					edit(index);
					return;
				}
		break;
	default:
		break;
	}
	QTreeWidget::keyPressEvent(event);
}

void PropertyEditorView::mousePressEvent(QMouseEvent* event)
{
	QTreeWidget::mousePressEvent(event);
	QTreeWidgetItem* item = itemAt(event->pos());

	if (item) {
		if ((item != m_editorPrivate->editedItem()) && (event->button() == Qt::LeftButton)
			&& (header()->logicalIndexAt(event->pos().x()) == 1)
			&& ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
			editItem(item, 1);
		}
		else if (!m_editorPrivate->hasValue(item) && m_editorPrivate->markPropertiesWithoutValue() && !rootIsDecorated()) {
			if (event->pos().x() + header()->offset() < 20)
				item->setExpanded(!item->isExpanded());
		}
	}
}