//#include "properties/helper.h"
#include "interpreter/component.h"
#include "common/private/object_p.h"
#include "qgraphicslinearlayout.h"
#include "qpainter.h"
#include "qstyleoption.h"
#include "qapplication.h"
#include "interpreter/private/component_p.h"
#include "qpropertyanimation.h"
#include "qgraphicssceneevent.h"
#include "private//qgraphicslayoutitem_p.h"
namespace shelllet {
}

shelllet::interpreter::Component::Component(ComponentPrivate& d, QGraphicsItem* parent /*= nullptr*/, Qt::WindowFlags wFlags /*= Qt::WindowFlags()*/)
	: QGraphicsWidget(parent, wFlags)
	, Object(d, nullptr)
{

}

void shelllet::interpreter::Component::removeItem(QGraphicsLayoutItem* item)
{
	throw std::logic_error("The method or operation is not implemented.");

}


shelllet::interpreter::Component* shelllet::interpreter::Component::nextItem() const
{
	Q_D(const Component);
	return d->next;

}

shelllet::interpreter::Component* shelllet::interpreter::Component::previousItem() const
{
	Q_D(const Component);
	return d->previous;
}

void shelllet::interpreter::Component::setNextItem(const Component* item)
{
	Q_D(Component);
	d->next = const_cast<Component*>(item);
}

void shelllet::interpreter::Component::setPreviousItem(const Component* item)
{
	Q_D(Component);
	d->previous = const_cast<Component*>(item);
}

void shelllet::interpreter::Component::setGeometry(const QRectF& rect)
{
	/*auto ge2 = geometry();
	QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(30000);
	animation->setStartValue(geometry());
	animation->setEndValue(ge2);

	animation->start();*/
	__super::setGeometry(rect);
//	QGraphicsWidgetPrivate* wd = QGraphicsWidget::d_func();
//	QGraphicsLayoutItemPrivate* d = QGraphicsLayoutItem::d_ptr.data();
//	QRectF newGeom;
//	QPointF oldPos = d->geom.topLeft();
//	if (!wd->inSetPos) {
//		setAttribute(Qt::WA_Resized);
//		newGeom = rect;
//		newGeom.setSize(rect.size().expandedTo(effectiveSizeHint(Qt::MinimumSize))
//			.boundedTo(effectiveSizeHint(Qt::MaximumSize)));
//
//		if (newGeom == d->geom) {
//			goto relayoutChildrenAndReturn;
//		}
//
//		// setPos triggers ItemPositionChange, which can adjust position
//		wd->inSetGeometry = 1;
//		setPos(newGeom.topLeft());
//		wd->inSetGeometry = 0;
//		newGeom.moveTopLeft(pos());
//
//		if (newGeom == d->geom) {
//			goto relayoutChildrenAndReturn;
//		}
//
//		// Update and prepare to change the geometry (remove from index) if the size has changed.
//		if (wd->scene) {
//			if (rect.topLeft() == d->geom.topLeft()) {
//				prepareGeometryChange();
//			}
//		}
//	}
//
//	// Update the layout item geometry
//	{
//		bool moved = oldPos != pos();
//		if (moved) {
//			// Send move event.
//			QGraphicsSceneMoveEvent event;
//			event.setOldPos(oldPos);
//			event.setNewPos(pos());
//			QCoreApplication::sendEvent(this, &event);
//			if (wd->inSetPos) {
//				//set the new pos
//				d->geom.moveTopLeft(pos());
//				emit geometryChanged();
//				goto relayoutChildrenAndReturn;
//			}
//		}
//		QSizeF oldSize = size();
//		QGraphicsLayoutItem::setGeometry(newGeom);
//		// Send resize event
//		bool resized = newGeom.size() != oldSize;
//		if (resized) {
//			QGraphicsSceneResizeEvent re;
//			re.setOldSize(oldSize);
//			re.setNewSize(newGeom.size());
//			if (oldSize.width() != newGeom.size().width())
//				emit widthChanged();
//			if (oldSize.height() != newGeom.size().height())
//				emit heightChanged();
//			QGraphicsLayout* lay = wd->layout;
//			if (QGraphicsLayout::instantInvalidatePropagation()) {
//				if (!lay || lay->isActivated()) {
//					QCoreApplication::sendEvent(this, &re);
//				}
//			}
//			else {
//				QCoreApplication::sendEvent(this, &re);
//			}
//		}
//	}
//
//	emit geometryChanged();
//relayoutChildrenAndReturn:
//	if (QGraphicsLayout::instantInvalidatePropagation()) {
//		if (QGraphicsLayout* lay = wd->layout) {
//			if (!lay->isActivated()) {
//				QEvent layoutRequest(QEvent::LayoutRequest);
//				QCoreApplication::sendEvent(this, &layoutRequest);
//			}
//		}
//	}
}

//
//QGraphicsLinearLayout* shelllet::graphics::GraphicsItem::linearLayout() const
//{
//	Q_D(const GraphicsItem);
//	return d->layout;
//}

