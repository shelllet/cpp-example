#include "interpreter/svgitem.h"
#include "common.hpp"
#include "qpainter.h"
#include "qsvgrenderer.h"
#include "interpreter/private/svgitem_p.h"
namespace shelllet {
	namespace interpreter {
	
	}
}

shelllet::interpreter::SvgItem::SvgItem(const String& fileName, QGraphicsItem* parent)
	: //QGraphicsSvgItem(fileName, parent)
	SvgItem(*new SvgItemPrivate, fileName, parent)
	//, Object(*new SvgItemPrivate, nullptr)
{
	Q_D(SvgItem);

	
}



void shelllet::interpreter::SvgItem::setSize(const QSize& size)
{
	Q_D(SvgItem);
	//d->size = size;
}

shelllet::interpreter::SvgItem::SvgItem(SvgItemPrivate& d, const String& fileName, QGraphicsItem* parent /*= 0*/)
	: QGraphicsSvgItem(*fileName.toQString(), parent)
	, Object(d, nullptr)
{
	setGraphicsItem(this);
}

//QRectF shelllet::graphics::SvgItem::boundingRect() const
//{
//	if (!renderer()->isValid()) {
//		return { 0, 0, 0, 0 };
//	}
//	return { QPointF(0, 0),renderer()->defaultSize() * std::abs(scale()) };
//}

void shelllet::interpreter::SvgItem::setGeometry(const QRectF& rect)
{
	/*prepareGeometryChange();
	setPos(rect.topLeft());*/
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	//	QGraphicsLayoutItem::setGeometry({ rect.topLeft(), boundingRect().size() });
	//setPos(rect.topLeft());
	QSize c = renderer()->defaultSize() * scale() / 2;

	setPos(rect.center() - QPoint{ c.width(), c.height() });
}

//void shelllet::graphics::SvgItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
//{
//	//if (!renderer()->isValid())
//	//	return;
//
//	//QRectF adjust = { QPointF(0, 0), geometry().size() };
//	//setTransformOriginPoint(adjust.center() - boundingRect().center());
//	LOG_TRACE("rpa") << transformOriginPoint() << std::endl;
//	LOG_TRACE("rpa") << boundingRect() << std::endl;
//	LOG_TRACE("rpa") << geometry() << std::endl;
//	LOG_TRACE("rpa") << renderer()->viewBox() << std::endl;
//	if (elementId().isEmpty())
//		renderer()->render(painter, boundingRect());
//	else
//		renderer()->render(painter, elementId(), boundingRect());
//
//	//__super::paint(painter, option, widget);
//}

QSizeF shelllet::interpreter::SvgItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint /*= QSizeF()*/) const
{
	//Q_D(const SvgItem);
	//if (which == Qt::MinimumSize) {
		//return d->size;
	//}
	return { -1, -1 };
}
