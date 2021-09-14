#include "creator.hpp"
#include <QCoreApplication>
#include "graphics_view.h"
#include "interpreter.hpp"
#include "events/activity_select_event.h"
#include "creator/scene.h"
#include "events/common_event.h"
//#include "properties/helper.h"
#include "private/qgraphicsview_p.h"

namespace shelllet {

		using namespace interpreter;
	namespace creator {
		class GraphicsViewPrivate : public QGraphicsViewPrivate {
		public:
			DiagramScene* scene;
			Element* lastSelectItem = nullptr;
		};
	}

	static void WalkCodeCall(std::ostringstream& ss, const QList<QGraphicsItem*>& items) {
		for (auto* i : items) {
			if (auto* element = dynamic_cast<Element*>(i)) {
				element->prop()->getCode(ss);
				ss << std::endl;

				WalkCodeCall(ss, i->childItems());
			}
		}
	}

	static	void WalkCodeImport(QStringList& imports, QStringList& declares, QGraphicsItem* start) {
		for (auto* item : start->childItems()) {
			if (item) {
				{

					std::ostringstream ss;

					if (auto* element = dynamic_cast<Element*>(item)) {
						element->prop()->getImport();

						imports.push_back(QString::fromStdString(ss.str()));
					}

				}
				{

					std::ostringstream ss;
					if (auto* element = dynamic_cast<Element*>(item)) {

						element->prop()->getDefines(ss);

						declares.push_back(QString::fromStdString(ss.str()));
					}
				}
			}


			WalkCodeImport(imports, declares, item);
		}
	}

}

shelllet::creator::GraphicsView::GraphicsView(QWidget* parent /*= nullptr*/)
	: QGraphicsView(*new GraphicsViewPrivate, parent)
{
	Q_D(GraphicsView);
	QMenu* menu = nullptr;
	d->scene = new DiagramScene(menu, this);
	d->scene->setSceneRect(QRectF(0, 0, 5000, 5000));;

	setScene(d->scene);
	DiagramScene::RegisterAllViews();
}

shelllet::creator::GraphicsView::~GraphicsView()
{
}

std::unique_ptr<XmlDocument> shelllet::creator::GraphicsView::getXml() const
{
	Q_D(const GraphicsView);
	return	d->scene->toXml();
}

void shelllet::creator::GraphicsView::setXml(const XmlDocument& doc)
{
	Q_D(GraphicsView);
	//QGraphicsItem* first_item = nullptr;

	//auto* item = scene_->addItem(std::move(properties::CompositeProperty::CreateNode(node)));

	//for (auto& c : node.children())
	//{
	//	/*	std::shared_ptr<ItemMimeData> data = std::make_shared<ItemMimeData>();
	//		data->display = node.attribute("display").value();
	//		data->meta = node.attribute("meta").value();
	//		data->height = node.attribute("h").value();
	//		data->width = node.attribute("w").value();
	//		data->x = node.attribute("x").value();
	//		data->y = node.attribute("y").value();
	//		data->type = node.attribute("type").value();*/
	//	LOG_DEBUG("rpa") << "# c: " << properties::Helper::toString(c) << std::endl;
	//	scene_->addItem(std::move(properties::CompositeProperty::CreateNode(c)));

	//}

	d->scene->loadFromXml(doc);
	ensureVisible(d->scene->rootItem());
}


QString shelllet::creator::GraphicsView::getCode() const
{
	Q_D(const GraphicsView);
	std::ostringstream ss;

	QStringList imports, declares;

	//ss << "import " << Environment::getInstance()->getOptions()->index_var_filename << std::endl;

	//WalkCodeImport(imports, declares, d->scene->rootItem());

	ss << imports.join("\n") << std::endl;

	ss << declares.join("\n") << std::endl;

	Component* item = dynamic_cast<Component*>(d->scene->rootItem());

	WalkCodeCall(ss, item->childItems());


	return QString::fromStdString(ss.str());

}

void shelllet::creator::GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
	//QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::ActivitiesShowEvent(nullptr));
}

void shelllet::creator::GraphicsView::mousePressEvent(QMouseEvent* event)
{
	Q_D(GraphicsView);
	if (event->button() == Qt::LeftButton)
	{
		QGraphicsItem* item = itemAt(event->pos());
		Element* current = dynamic_cast<Element*>(item);
		if (current && current != d->lastSelectItem) {
			d->lastSelectItem = current;
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::ActivitySelectEvent(current->prop()));
		}
	}
	__super::mousePressEvent(event);
}
