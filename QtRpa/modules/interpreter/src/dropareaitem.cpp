#include "interpreter/composite_property.h"
#include "interpreter/dropareaitem.h"
#include "common/private/object_p.h"
#include "interpreter/private/component_p.h"
#include "interpreter/arrowitem.h"
#include "qgraphicslinearlayout.h"
#include "qgraphicssceneevent.h"
#include "qmimedata.h"
#include "events.hpp"
#include "qcoreapplication.h"
#include "qgraphicsscene.h"
#include "qpainter.h"
#include "interpreter/containeritem.h"
#include "interpreter/placeholderitem.h"

#include "qpropertyanimation.h"
#include "qgraphicssceneevent.h"

namespace shelllet {
	namespace interpreter {
		class DropAreaPrivate : public ComponentPrivate {
			Q_DECLARE_PUBLIC(DropArea)
		public:
			ArrowItem* arrow = nullptr;
			ArrowItem* arrowNext = nullptr;
			PlaceholderItem* placeholder = nullptr;
			void setupUi(DropArea* self) {
				layout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, self);
				layout->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
				layout->setContentsMargins(11, 11, 11, 11);
				arrow = new ArrowItem(self);
				self->addItem(arrow);
			}
		};
	}
}


shelllet::interpreter::DropArea::DropArea(QGraphicsItem* parent /*= nullptr*/)
	: Component(*new DropAreaPrivate, parent, Qt::Window | Qt::FramelessWindowHint)
{
	Q_D(DropArea);
	d->setupUi(this);
	setAcceptDrops(true);
	//setMinimumSize(240, 36);
	setMinimumWidth(240);


	//showExtraItem();
}

void shelllet::interpreter::DropArea::setGeometry(const QRectF& rect)
{

	__super::setGeometry(rect);
}

void shelllet::interpreter::DropArea::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	__super::paint(painter, option, widget);

	//painter->fillRect(rect(), Qt::red);

	painter->drawPoint(rect().center());
}



void shelllet::interpreter::DropArea::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	Q_D(DropArea);
	auto geo = geometry();
	showExtraItem();
	auto s = event->source();
	event->acceptProposedAction();
	/*d->layout->invalidate();
	d->layout->activate();
	emit geometryChanged();*/
	//adjustSize();
	event->accept();
	//update();

}

void shelllet::interpreter::DropArea::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
	Q_D(DropArea);
	hideExtraItem();
	//dynamic_cast<DiagramScene*>(scene())->rootWidget()->layout()->updateGeometry();
	//dynamic_cast<DiagramScene*>(scene())->rootWidget()->adjustSize();
	QCoreApplication::postEvent(scene(), new AdjustSizeEvent, Qt::LowEventPriority);
	//event->accept();
}

void shelllet::interpreter::DropArea::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	auto* parent = dynamic_cast<Container*>(parentWidget());

	hideExtraItem();
	parent->dropItem(event->mimeData(), this);
	QCoreApplication::postEvent(scene(), new AdjustSizeEvent, Qt::LowEventPriority);
	//event->accept();
}

QSizeF shelllet::interpreter::DropArea::sizeHint(Qt::SizeHint which, const QSizeF& constraint /*= QSizeF()*/) const
{
	if (which == Qt::MinimumSize) {
		return QSizeF(-1, 48);
	}
	//return constraint;

	auto size = __super::sizeHint(which, constraint);
	//size.setHeight(80);
	LOG_DEBUG("rap") << "# sizehint: " << size << std::endl;
	return	size;
}

void shelllet::interpreter::DropArea::removeItem(QGraphicsLayoutItem* item)
{
	Q_D(DropArea);
	d->layout->removeItem(item);
	scene()->removeItem(dynamic_cast<QGraphicsItem*>(item));
	delete item;
}

void shelllet::interpreter::DropArea::addItem(QGraphicsLayoutItem* item)
{
	Q_D(DropArea);
	d->layout->addItem(item);
	d->layout->setAlignment(item, Qt::AlignHCenter | Qt::AlignVCenter);
}



void shelllet::interpreter::DropArea::hideExtraItem()
{
	Q_D(DropArea);
	removeItem(d->arrowNext);
	removeItem(d->placeholder);
	d->arrowNext = nullptr;
	d->placeholder = nullptr;
	d->layout->invalidate();
}

void shelllet::interpreter::DropArea::showExtraItem()
{
	Q_D(DropArea);
	d->placeholder = new PlaceholderItem(this);
	d->arrowNext = new ArrowItem(this);
	addItem(d->placeholder);
	addItem(d->arrowNext);
}

