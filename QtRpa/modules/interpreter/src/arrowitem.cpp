#include "interpreter/arrowitem.h"
#include "qpainter.h"
#include "qsvgrenderer.h"
#include "qgraphicslinearlayout.h"
#include "interpreter/private/svgitem_p.h"
#include "interpreter/svgitem.h"
namespace shelllet {
	namespace interpreter {

		class ArrowItemPrivate : public SvgItemPrivate {
		public:
			/*SvgItem* item;
			void setupUi(ArrowItem* self) {
				layout = new QGraphicsLinearLayout(Qt::Orientation::Horizontal, self);
				layout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
				layout->setContentsMargins(9, 9, 9, 9);
				item = new SvgItem(Environment::getInstance()->getIconFileName("arrow"), self);
				layout->addItem(item);
				layout->setAlignment(item, Qt::AlignHCenter | Qt::AlignVCenter);
			}*/
		};
	}
}


shelllet::interpreter::ArrowItem::ArrowItem(QGraphicsItem* parent /*= nullptr*/)
	: SvgItem(*new ArrowItemPrivate, Environment::getInstance()->getIconFileName("arrow"), parent)
{
	//setRotation(180);
	//setSize({ 24, 24 });
	Q_D(ArrowItem);
	//d->setupUi(this);
	setScale(-0.1);

	//setFocusPolicy(Qt::NoFocus);
	setFlag(QGraphicsItem::ItemIsFocusable, false);
//
	//renderer()->setViewBox(QRectF(QPoint(0, 0), renderer()->defaultSize() * 0.2));

}
//
//void shelllet::graphics::ArrowItem::setGeometry(const QRectF& rect)
//{
//	/*prepareGeometryChange();
//	QGraphicsLayoutItem::setGeometry({ rect.topLeft(), renderer()->defaultSize() * 0.2 });
//	setPos(rect.center() + (QRectF{ QPointF(0, 0), geometry().size() }).center());*/
//	__super::setGeometry(rect);
//}

