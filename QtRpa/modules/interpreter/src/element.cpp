//#include "properties/helper.h"
#include "interpreter/composite_property.h"
#include "interpreter/containeritem.h"
#include "interpreter/element.h"
#include "common/private/object_p.h"
#include "qgraphicslinearlayout.h"
#include "qpainter.h"
#include "qstyleoption.h"
#include "qapplication.h"
#include "qgraphicsscene.h"
#include "qaction.h"
#include "qmenu.h"
#include "events.hpp"
#include "qgraphicssceneevent.h"
#include "interpreter/private/element_p.h"
#include "interpreter/elementmimedata.h"
#include "qdrag.h"
#include "qmimedata.h"
#include "qpixmap.h"
#include "qbitmap.h"
#include "model.hpp"
namespace shelllet {
	namespace interpreter {
	}

}

shelllet::interpreter::Element::Element(ElementPrivate& d, QGraphicsItem* parent /*= nullptr*/, Object* p /*= nullptr*/)
	: Component(d, parent, Qt::Window /*| Qt::WindowTitleHint*/)
{
	//setWindowTitle(*property->displayName().toQString());

	QAction* action = new QAction("delete", this);
	QAction* refresh = new QAction("refresh", this);
	connect(action, &QAction::triggered, this, [this]() {
		auto* parent = dynamic_cast<Container*>(parentWidget());
		if (parent) {
			auto* sc = scene();
			//parent->removeItem(parent->indexWidget(this)+1);
			parent->removeItem(this);
			QCoreApplication::postEvent(sc, new AdjustSizeEvent, Qt::LowEventPriority);
		}
	});

	connect(refresh, &QAction::triggered, this, [this]() {
		QCoreApplication::postEvent(scene(), new AdjustSizeEvent, Qt::LowEventPriority);
	});

	//connect(prop(), &CompositeProperty::displayNameChanged, [this]() {
	//	setWindowTitle(*prop()->displayName().toQString());
	//	update();
	//});
	addAction(action);
	addAction(refresh);

	setFlag(QGraphicsItem::ItemIsSelectable);

}

shelllet::interpreter::Element::Element(QGraphicsItem* parent /*= nullptr*/, Object* p /*= nullptr*/)
	: Element(*new ElementPrivate, parent, p)
{

}

void shelllet::interpreter::Element::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	QMenu menu;
	menu.addActions(actions());
	menu.exec(event->screenPos());
}



Qt::WindowFrameSection shelllet::interpreter::Element::windowFrameSectionAt(const QPointF& pos) const
{
	//throw std::logic_error("The method or operation is not implemented.");
	auto section = __super::windowFrameSectionAt(pos);
	//switch (section)
	//{
	if (section != Qt::TitleBarArea) {
		//return Qt::NoSection;
	}
	//	return Qt::NoSection;
	//default:
	//	break;
	//}
	return section;
}

bool shelllet::interpreter::Element::windowFrameEvent(QEvent* e)
{
	Q_D(Element);
	//return __super::windowFrameEvent(e);
	//throw std::logic_error("The method or operation is not implemented.");
	if (e->type() == QEvent::GraphicsSceneMouseMove) {
		if (windowFrameSectionAt(dynamic_cast<QGraphicsSceneMouseEvent*>(e)->pos()) == Qt::TitleBarArea) {

			QDrag* drag = new QDrag(this);

			drag->setMimeData(mimeData());

			QPixmap pixmap(34, 34);
			pixmap.fill(Qt::white);

			QPainter painter(&pixmap);
			painter.translate(15, 15);
			painter.setRenderHint(QPainter::Antialiasing);
			paint(&painter, nullptr, nullptr);
			painter.end();

			pixmap.setMask(pixmap.createHeuristicMask());

			drag->setPixmap(pixmap);
			drag->setHotSpot(QPoint(15, 20));

			drag->exec();
			//	setCursor(Qt::OpenHandCursor);

			e->accept();

			return e->isAccepted();
		}
	}
	return __super::windowFrameEvent(e);
}

QMimeData* shelllet::interpreter::Element::mimeData()
{
	Q_D(const Element);
	//XmlMimeData* mime = new ElementMimeData;
//	mime->setElementItem(this);
	//XmlByteArrayWriter writer;
	//d->prop->getNode()->print(writer);

	//mime->setData(Environment::getInstance()->getOptions()->mime_data_type, writer.result);

	auto* mime_data = new XmlMimeData(prop()->getNode()->documentElement());

	mime_data->setSourceItem(this);

	return mime_data;
}


void shelllet::interpreter::Element::addItem(Element* item)
{
	throw std::logic_error("The method or operation is not implemented.");
}




//
//void shelllet::graphics::Element::removeItem(QGraphicsLayoutItem* item)
//{
//	
//}

void shelllet::interpreter::Element::paintWindowFrame(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	Q_D(Element);
	//const bool fillBackground = !testAttribute(Qt::WA_OpaquePaintEvent)
	//	&& !testAttribute(Qt::WA_NoSystemBackground);
	//QGraphicsProxyWidget* proxy = qobject_cast<QGraphicsProxyWidget*>(this);
	//const bool embeddedWidgetFillsOwnBackground = proxy && proxy->widget();

	//if (rect().contains(option->exposedRect)) {
	//	if (fillBackground && !embeddedWidgetFillsOwnBackground)
			//painter->fillRect(option->exposedRect, palette().window());
	//	return;
	//}



	QRect windowFrameRect = QRect(QPoint(), windowFrameGeometry().size().toSize());

	QStyleOptionTitleBar bar;
	bar.initFrom(widget);
	bar.icon = prop()->icon();
	bar.text = windowTitle();
	bar.QStyleOption::operator=(*option);

	bar.subControls = QStyle::SC_TitleBarCloseButton | QStyle::SC_TitleBarLabel;

	//	d->initStyleOptionTitleBar(&bar);   // this clear flags in bar.state
		//d->ensureWindowData();
		//bar.state.setFlag(QStyle::State_MouseOver, d->windowData->buttonMouseOver);
		//bar.state.setFlag(QStyle::State_Sunken, d->windowData->buttonSunken);
	bar.rect = windowFrameRect;

	// translate painter to make the style happy
	const QPointF styleOrigin = this->windowFrameRect().topLeft();
	painter->translate(styleOrigin);


	// Fill background
	//QStyleHintReturnMask mask;
	//bool setMask = style()->styleHint(QStyle::SH_WindowFrame_Mask, &bar, widget, &mask) && !mask.region.isEmpty();
	//bool hasBorder = !style()->styleHint(QStyle::SH_TitleBar_NoBorder, &bar, widget);
	//int frameWidth = style()->pixelMetric(QStyle::PM_MdiSubWindowFrameWidth, &bar, widget);
	//if (setMask) {
	//	painter->save();
	//	painter->setClipRegion(mask.region, Qt::IntersectClip);
	//}
	//if (fillBackground) {
	//	if (embeddedWidgetFillsOwnBackground) {
	//		// Don't fill the background twice.
	//		QPainterPath windowFrameBackground;
	//		windowFrameBackground.addRect(windowFrameRect);
	//		// Adjust with 0.5 to avoid border artifacts between
	//		// widget background and frame background.
	//		windowFrameBackground.addRect(rect().translated(-styleOrigin).adjusted(0.5, 0.5, -0.5, -0.5));
	//		painter->fillPath(windowFrameBackground, palette().window());
	//	}
	//	else {
	//		painter->fillRect(windowFrameRect, palette().window());
	//	}
	//}

	//// Draw title
	int height = style()->pixelMetric(QStyle::PM_TitleBarHeight, &bar);
	bar.rect.setHeight(height);
	//if (hasBorder) // Frame is painted by PE_FrameWindow
	//bar.rect.adjust(d->frameWidth, d->frameWidth, -d->frameWidth, 0);

	//painter->save();
	//painter->setFont(QApplication::font("QMdiSubWindowTitleBar"));
	style()->drawComplexControl(QStyle::CC_TitleBar, &bar, painter, widget);
	//painter->restore();
	//if (setMask)
	//	painter->restore();
	//// Draw window frame
	QStyleOptionGroupBox frameOptions;
	frameOptions.QStyleOption::operator=(*option);
	//initStyleOption(&frameOptions);
	//if (!hasBorder)
	//	painter->setClipRect(windowFrameRect.adjusted(0, +height, 0, 0), Qt::IntersectClip);
	//frameOptions.state.setFlag(QStyle::State_HasFocus, hasFocus());
	bool isActive = isActiveWindow();
	//frameOptions.state.setFlag(QStyle::State_Active, isActive);

	frameOptions.palette.setCurrentColorGroup(isActive ? QPalette::Active : QPalette::Normal);
	frameOptions.rect = windowFrameRect;
	frameOptions.lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, nullptr, widget);
	frameOptions.midLineWidth = 1;
	style()->drawPrimitive(QStyle::PE_FrameGroupBox, &frameOptions, painter, widget);

	//QGraphicsWidget::paintWindowFrame(painter, option, widget);
}
shelllet::interpreter::CompositeProperty* shelllet::interpreter::Element::prop()
{
	Q_D(Element);
	//return nullptr;
	throw std::logic_error("");
	//return d->prop;
}

shelllet::interpreter::Component* shelllet::interpreter::Element::nextItem() const
{
	//throw std::logic_error("The method or operation is not implemented.");

	auto* parent = dynamic_cast<Container*>(parentWidget());
	if (parent) {

		//parent->removeItem();
		//parent->removeItem(this);

		return parent->itemAt(parent->indexWidget(this) + 1);

		//QCoreApplication::postEvent(sc, new AdjustSizeEvent, Qt::LowEventPriority);
	}

	return nullptr;
}
//
//shelllet::graphics::Element* shelllet::graphics::Element::CreateElement(const py::object& property, QGraphicsItem* parent /*= nullptr*/)
//{
//	Element* element = nullptr;
//	QString ns = GetNamespace<Container>(QUOTED(Container)) + property->metaName() + "*";
//	if (int id = QMetaType::type(ns.toUtf8()); id != QMetaType::UnknownType) {
//		const auto* meta = QMetaType::metaObjectForType(id);
//		element = dynamic_cast<Element*>(meta->newInstance(Q_ARG(SharedPointer<CompositeProperty>, property), Q_ARG(QGraphicsItem*, parent)));
//	}
//	else {
//		LOG_WARNING("rpa") << "# meta type is unknown: " << property->metaName() << "-" << std::endl;
//	}
//	Q_ASSERT_X(element != nullptr, "Create Graphics Widget", "element is null");
//	return element;
//}
