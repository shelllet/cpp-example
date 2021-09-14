#include "interpreter/simpletextitem.h"
#include "common/private/object_p.h"
namespace shelllet {
	namespace interpreter {
		class SimpleTextItemPrivate : public ObjectPrivate {
		public:



		};


	}
}
shelllet::interpreter::SimpleTextItem::SimpleTextItem(QGraphicsItem* parent/* = nullptr*/)
	: SimpleTextItem("", parent)
{

}


shelllet::interpreter::SimpleTextItem::~SimpleTextItem()
{

}

shelllet::interpreter::SimpleTextItem::SimpleTextItem(const QString& text, QGraphicsItem* parent /*= nullptr*/)
	: QGraphicsSimpleTextItem(text,parent)
	, Object(*new SimpleTextItemPrivate, nullptr)
{
	Q_D(SimpleTextItem);

}

void shelllet::interpreter::SimpleTextItem::setColor(const QColor& color)
{
	Q_D(SimpleTextItem);
}



void shelllet::interpreter::SimpleTextItem::setGeometry(const QRectF& rect)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	setPos(rect.topLeft());
}

QSizeF shelllet::interpreter::SimpleTextItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint /*= QSizeF()*/) const
{
	return boundingRect().size();
}
