//#include "pybind11/pybind11.h"
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <qmimedata.h>
#include "boost/serialization/shared_ptr.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include "boost/serialization/export.hpp"
//#include "graphics/code.h"
#include "common.hpp"
#include "events.hpp"
//#include "properties/print.h"
#include "qbuffer.h"
#include "common/private/object_p.h"
#include "qgraphicslinearlayout.h"
#include "qtextedit.h"
#include "qgraphicsproxywidget.h"
#include "interpreter.hpp"
#include "creator/scene.h"

namespace shelllet {
	namespace creator {
	//	namespace  py = pybind11;
		class GraphicsWidget : public QGraphicsWidget {
		public:

		protected:
			QVariant itemChange(GraphicsItemChange change, const QVariant& value) override
			{
				if (change == QGraphicsItem::ItemChildRemovedChange) {
					LOG_DEBUG("#pra") << "# child removed." << std::endl;
				}
				return __super::itemChange(change, value);
			}

		};

		class DiagramScenePrivate : public ObjectPrivate {
		public:
			QMenu* myItemMenu;
			bool leftButtonDown;
			QPointF startPoint;


			QGraphicsItem* item = nullptr;
			QGraphicsWidget* form;
			QGraphicsLinearLayout* layout;

			void setupUi(QGraphicsScene* scene) {
				form = new GraphicsWidget;
				layout = new QGraphicsLinearLayout(Qt::Vertical, form);
				layout->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
				layout->setContentsMargins(0, 0, 0, 0);

				form->setPos(100, 100);

				scene->addItem(form);
			}
		};



	}
}
shelllet::creator::DiagramScene::DiagramScene(QMenu* itemMenu, QObject* parent)
	: QGraphicsScene(parent)
	, Object(*new DiagramScenePrivate, nullptr)
{
	Q_D(DiagramScene);
	d->setupUi(this);

	d->form->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
}




QGraphicsItem* shelllet::creator::DiagramScene::rootItem() const
{
	Q_D(const DiagramScene);
	return d->form->childItems().first();
}

QGraphicsItem* shelllet::creator::DiagramScene::startItem() const
{

	return nullptr;
}

std::unique_ptr<XmlDocument> shelllet::creator::DiagramScene::toXml()
{
	Q_D(DiagramScene);
	std::unique_ptr<XmlDocument> doc = std::make_unique<XmlDocument>();
	doc->addDeclaration();
	Element* root = qgraphicsitem_cast<Element*>(rootItem());
	doc->appendCopy(root->prop()->getNode()->documentElement());
	walkChildItem(doc->documentElement(), root->childItems());
	return doc;
}

void shelllet::creator::DiagramScene::loadFromXml(const XmlDocument& doc)
{
	Q_D(DiagramScene);

	auto* sequence = new PropParser(doc.documentElement());
	addItem(sequence->element());
	walkChildNode(doc.documentElement(), sequence->element());
}

QGraphicsWidget* shelllet::creator::DiagramScene::rootWidget() const
{
	Q_D(const DiagramScene);
	return d->form;
}

void shelllet::creator::DiagramScene::walkChildNode(XmlNode node, Element* item)
{
	for (auto& c : node.children())
	{
		if (c.type() == XmlNodeType::Element) {
			//auto element = Element::CreateElement(CompositeProperty::CreateNode(c), item);
			auto* sequence = new PropParser(c, item);
			if (sequence) {
				item->addItem(sequence->element());
				walkChildNode(c, sequence->element());
			}
		}
	}
}

void shelllet::creator::DiagramScene::walkChildItem(XmlNode node, const QList<QGraphicsItem*>& items)
{
	for (auto* i : items) {
		if (auto* item = dynamic_cast<Element*>(i)) {
			auto doc = item->prop()->getNode();
			walkChildItem(node.appendCopy(doc->documentElement()), i->childItems());
		}
	}
}

//! [4]

void shelllet::creator::DiagramScene::setMode(Mode mode)
{
	Q_D(DiagramScene);
}

void shelllet::creator::DiagramScene::addItem(QGraphicsLayoutItem* item)
{
	Q_D(DiagramScene);
	d->layout->addItem(item);
	d->layout->setAlignment(item, Qt::AlignHCenter);
}



void shelllet::creator::DiagramScene::RegisterAllViews()
{
	//qRegisterMetaType<Sequence*>();
//	qRegisterMetaType<FileDelete*>();
	//qRegisterMetaType<ProcessStart*>();
	//qRegisterMetaType<Code*>();
}


//! [14]
bool shelllet::creator::DiagramScene::isItemChange(int type)
{
	Q_D(DiagramScene);
	foreach(QGraphicsItem * item, selectedItems()) {
		if (item->type() == type)
			return true;
	}
	return false;
}






void shelllet::creator::DiagramScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	__super::dragEnterEvent(event);
}

void shelllet::creator::DiagramScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	__super::dragMoveEvent(event);
}

void shelllet::creator::DiagramScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	__super::dropEvent(event);
}

void shelllet::creator::DiagramScene::customEvent(QEvent* event)
{
	//Q_D(DiagramScene);
	if (auto* e = dynamic_cast<AdjustSizeEvent*>(event)) {
		rootWidget()->layout()->updateGeometry();
		rootWidget()->adjustSize();
		LOG_DEBUG("ppp") << "update size" << std::endl;
	}
}
