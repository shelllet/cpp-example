#include "interpreter/placeholderitem.h"
#include "qpainter.h"
#include "qsvgrenderer.h"
#include "common/private/object_p.h"
namespace shelllet {
	namespace interpreter {
		class PlaceholderItemPrivate : public ObjectPrivate {
		public:

		};

	}
}

shelllet::interpreter::PlaceholderItem::PlaceholderItem(QGraphicsItem* parent)
	: QGraphicsRectItem(parent)
	, Object(*new PlaceholderItemPrivate, nullptr)
{
	Q_D(PlaceholderItem);
	setGraphicsItem(this);
}



QRectF shelllet::interpreter::PlaceholderItem::boundingRect() const
{
	return { QPointF(0, 0), geometry().size() };
}

void shelllet::interpreter::PlaceholderItem::setGeometry(const QRectF& rect)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	setPos(rect.topLeft());
}

QSizeF shelllet::interpreter::PlaceholderItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint /*= QSizeF()*/) const
{
	if (which == Qt::MinimumSize) {
		return QSizeF(-1, 24);
	}
	return constraint;
}

void shelllet::interpreter::PlaceholderItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	Q_UNUSED(widget);

	painter->fillRect(boundingRect(), Qt::Dense3Pattern);
}
