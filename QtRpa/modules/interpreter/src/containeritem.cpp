//#include "properties/helper.h"
#include "interpreter/composite_property.h"
#include "interpreter/propparser.h"
#include "events.hpp"
#include "common/private/object_p.h"
#include "qpainter.h"
#include "qstyle.h"
#include "qcoreapplication.h"
#include "qstyleoption.h"
#include "interpreter/containeritem.h"
#include "qgraphicslinearlayout.h"
#include "interpreter/simpletextitem.h"
#include "interpreter/simpletextitem.h"
#include "interpreter/private/containeritem_p.h"
#include "interpreter/dropareaitem.h"
#include "interpreter/element.h"
#include "qpropertyanimation.h"
#include "qgraphicssceneevent.h"
#include "interpreter/elementmimedata.h"
#include "pugixml.hpp"
#include "model.hpp"
#include "interpreter.hpp"
#include "qgraphicsscene.h"
namespace shelllet {
	namespace interpreter {
		class UpdateEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			UpdateEvent() : QEvent(Type) {

			}
		};
	}
}

shelllet::interpreter::Container::Container(ContainerPrivate& d, Element* parent /*= nullptr*/, Object*p /*= nullptr*/)
	: Element(d, parent, p)
{
	d.layout = new QGraphicsLinearLayout(Qt::Orientation::Vertical, this);
	d.layout->setContentsMargins(11, 11, 11, 11);
	d.layout->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	addItem(new DropArea(this));

	//setFlag(QGraphicsItem::ItemIsMovable, true);
	//setFlag(QGraphicsItem::ItemIsSelectable, true);
	//setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

	//setAcceptHoverEvents(true);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}



void shelllet::interpreter::Container::removeItem(int index)
{
	Q_D(Container);
	//auto* item = d->layout->itemAt(index);

	//if (auto *temp = dynamic_cast<DropArea*>(item)) {
	//	removeItem(temp);
	//}
	throw std::runtime_error("");
}


void shelllet::interpreter::Container::hideExtraItem()
{
	Q_D(Container);
	if (d->description) {
		removeItem(d->description);
		d->description = nullptr;
	}
}

void shelllet::interpreter::Container::showExtraItem()
{
	Q_D(Container);
	if (d->description) {
		d->description = new SimpleTextItem(tr("put activities in here"), this);
		addItem(d->description);
	}
}

void shelllet::interpreter::Container::updateExtraItem()
{
	if (isEmpty()) {
		showExtraItem();
	}
	else {
		hideExtraItem();
		QCoreApplication::postEvent(scene(), new AdjustSizeEvent, Qt::LowEventPriority);
	}
}

void shelllet::interpreter::Container::customEvent(QEvent* event)
{
	if (dynamic_cast<UpdateEvent*>(event)) {
		updateExtraItem();
	}
}
void shelllet::interpreter::Container::dropItem(const QMimeData* mimeData, Component* current)
{
	Q_D(Container);
	//throw std::logic_error("The method or operation is not implemented.");
	//ElementItem* element = nullptr;
	//GraphicsItem* nextItem = nullptr;

	//if (auto* temp = dynamic_cast<ElementMimeData*>(const_cast<QMimeData*>(mimeData))) {
		/*element = temp->elementItem();
		nextItem = temp->elementItem()->nextItem();*/

		//	std::shared_ptr<CompositeProperty> property = std::move(CompositeProperty::CreateNode(temp->node()));
			//element = ElementItem::CreateElement(property, nullptr);
		//	nextItem = new DropArea(nullptr);
	//	}
	if (auto* temp = dynamic_cast<XmlMimeData*>(const_cast<QMimeData*>(mimeData))) {
		//	QByteArray bytes = mimeData->data(Environment::getInstance()->getOptions()->mime_data_type);

			//if (!bytes.isEmpty()) {
				//pugi::xml_document doc;
			//	doc.load_string(bytes.constData());

		LOG_DEBUG("rpa") << temp->documentElement();


		//auto element = ElementItem::CreateElement(CompositeProperty::CreateNode(temp->documentElement()), this);
		auto* sequence = new PropParser(temp->documentElement(), this);
		//}
		if (sequence) {

			insertItem(indexWidget(current) + 1, sequence->element());
		}
		//insertItem(indexWidget(element) + 1, nextItem);

		if (temp->sourceItem()) {
			auto* p = temp->sourceItem();
			if (auto* parent = dynamic_cast<Container*>(p->parentItem())) {
				parent->removeItem(dynamic_cast<QGraphicsLayoutItem*>(p));
			}
		}
	}


	//// update index
	//element->setPreviousItem(current);
	//element->setNextItem(nextItem);

	//nextItem->setPreviousItem(element);
	//nextItem->setNextItem(dynamic_cast<GraphicsItem*>(d->layout->itemAt(index + 1)));

	//d->layout->invalidate();
}



Component* shelllet::interpreter::Container::itemAt(int index) const
{
	Q_D(const Container);
	return dynamic_cast<Component*>(d->layout->itemAt(index));
}

void shelllet::interpreter::Container::addItem(QGraphicsLayoutItem* item)
{
	Q_D(Container);
	d->layout->addItem(item);
	d->layout->setAlignment(item, Qt::AlignHCenter);
}

void shelllet::interpreter::Container::addItem(Element* item)
{
	//throw std::logic_error("The method or operation is not implemented.");
	Q_D(Container);
	/*d->layout->addItem(item);
	d->layout->setAlignment(item, Qt::AlignHCenter);

	addItem(new DropArea(this));*/
	std::invoke(static_cast<void(Container::*)(QGraphicsLayoutItem*)>(&Container::addItem), this, item);
	//addItem(item);
	auto* extra = new DropArea(this);
	d->layout->addItem(extra);
	d->layout->setAlignment(extra, Qt::AlignHCenter);
}

int shelllet::interpreter::Container::insertItem(int index, QGraphicsLayoutItem* item)
{
	Q_D(Container);
	d->layout->insertItem(index, item);
	d->layout->setAlignment(item, Qt::AlignHCenter);
	if (auto* temp = dynamic_cast<QGraphicsWidget*>(item); temp->parentItem() != this) {
		temp->setParentItem(this);
	}
	auto* extra = new DropArea(this);

	d->layout->insertItem(index + 1, extra);
	d->layout->setAlignment(extra, Qt::AlignHCenter);
	///setParentLayoutItem();
	//addItem(new DropArea(this));

	int newIndex = indexWidget(item);

	//Q_ASSERT_X(newIndex == index, "insert item", "index not equal");
	return newIndex;
}

int shelllet::interpreter::Container::indexWidget(const QGraphicsLayoutItem* item) const
{
	//Q_D(Container);
	for (int i = 0; i < layout()->count(); i++) {
		if (item == dynamic_cast<QGraphicsLayoutItem*>(layout()->itemAt(i))) {
			return i;
		}
	}

	return -1;

}


bool shelllet::interpreter::Container::isEmpty() const
{
	for (int i = 0; i < layout()->count(); i++) {
		if (auto* item = itemAt(i)) {
			return false;
		}
	}
	return true;
}

void shelllet::interpreter::Container::setGeometry(const QRectF& rect)
{
	__super::setGeometry(rect);


}

void shelllet::interpreter::Container::removeItem(QGraphicsLayoutItem* item)
{
	Q_D(Container);

	auto* p = dynamic_cast<Component*>(item);

	if (p)
	{
		p->hide();
		if (auto* temp = dynamic_cast<DropArea*>(p->nextItem())) {
			d->layout->removeItem(temp);
			scene()->removeItem(temp);
			delete temp;
		}

		d->layout->removeItem(p);
		scene()->removeItem(p);
		delete p;
	}
	//for (int i = 0; i < layout()->count(); i++) {
	//	if (item == dynamic_cast<QGraphicsLayoutItem*>(layout()->itemAt(i))) {

	//		auto* area = dynamic_cast<DropArea*>(layout()->itemAt(i + 1));

	//		if (area) {
	//			removeItem(area);
	//			break;
	//		}

	//	}
	//}



}


void shelllet::interpreter::Container::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	//LOG_TRACE("rpa") << "# enter" << std::endl;
	Component::hoverEnterEvent(event);
}

void shelllet::interpreter::Container::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	//LOG_TRACE("rpa") << "# move" << std::endl;
	Component::hoverMoveEvent(event);
}

void shelllet::interpreter::Container::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	//throw std::logic_error("The method or operation is not implemented.");
	//LOG_TRACE("rpa") << "# leave" << std::endl;
	Component::hoverLeaveEvent(event);
}

QVariant shelllet::interpreter::Container::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
	Q_D(Container);
	if (change == QGraphicsItem::ItemChildAddedChange || change == QGraphicsItem::ItemChildRemovedChange) {
		if (auto* item = value.value<QGraphicsItem*>(); item->isWidget()) {
			//QTimer::singleShot(0.1s, this, Q_SLOT(updateExtraItem()));
			QCoreApplication::postEvent(this, new UpdateEvent, Qt::LowEventPriority);
		}
	}

	return __super::itemChange(change, value);
}

shelllet::interpreter::Container::Container(Element* parent /*= nullptr*/, Object* p /*= nullptr*/)
	: Container(*new ContainerPrivate, parent, p)
{

}
