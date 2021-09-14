#include "interpreter/textitem.h"
namespace shelllet {
	namespace interpreter {
		class TextItemPrivate : public ObjectPrivate {
		public:



		};


	}
}
shelllet::interpreter::TextItem::TextItem(QGraphicsItem* parent/* = nullptr*/)
	: QGraphicsTextItem(parent)
	, Object(*new TextItemPrivate, nullptr)
{
	Q_D(TextItem);

}


void shelllet::interpreter::TextItem::setColor(const QColor& color)
{
	Q_D(TextItem);
}



QSizeF shelllet::interpreter::TextItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint /*= QSizeF()*/) const
{
	return boundingRect().size();
}
