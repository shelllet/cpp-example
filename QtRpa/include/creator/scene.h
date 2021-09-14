#pragma once
#include <QGraphicsScene>
#include "common.hpp"
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

namespace shelllet {
	namespace creator {
	
		class DiagramScenePrivate;
		class DiagramScene : public QGraphicsScene, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, DiagramScene)
		public:
			enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

			explicit DiagramScene(QMenu* itemMenu, QObject* parent = 0);

			QGraphicsItem* rootItem() const;

			QGraphicsItem* startItem() const;
			std::unique_ptr<XmlDocument> toXml();
	
			void loadFromXml(const XmlDocument& doc);

			QGraphicsWidget* rootWidget() const;
		public slots:
			void setMode(Mode mode);
			void addItem(QGraphicsLayoutItem* item);

			static void RegisterAllViews();

		signals:
	

		protected:
			void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;

			void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;

			void dropEvent(QGraphicsSceneDragDropEvent* event) override;


			void customEvent(QEvent* event) override;

		private:
			bool isItemChange(int type);
			void walkChildNode(XmlNode node, Element* item);

			static 	void walkChildItem(XmlNode node, const QList<QGraphicsItem*>& items);
		};
	}
}
