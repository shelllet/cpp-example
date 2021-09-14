#pragma once
#include "interpreter/element.h"
#include "common.hpp"

#include "qgraphicswidget.h"
namespace shelllet {
	namespace interpreter {
		class ContainerPrivate;
		class Container : public Element {
			Q_DECLARE_PRIVATE_D(Object::d_ptr, Container)

		public:
			Container( Element* parent = nullptr, Object* p = nullptr);
			int insertItem(int index, QGraphicsLayoutItem* item);

			void removeItem(int index);


			void setGeometry(const QRectF& rect) override;
			int indexWidget(const QGraphicsLayoutItem* item) const;


			bool isEmpty() const;


			void removeItem(QGraphicsLayoutItem* item) override;
			void dropItem(const QMimeData* mimeData, Component* current);



			Component* itemAt(int index) const;


		protected:
			void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;


			void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;


			void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

			QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) override;
			Container(ContainerPrivate&, Element* parent = nullptr, Object * p=nullptr);




			void hideExtraItem();
			void showExtraItem();
			void updateExtraItem();

			void customEvent(QEvent* event) override;




			void addItem(Element* item) override;

		private:

	
			void addItem(QGraphicsLayoutItem* item);

		};
	}
}
Q_DECLARE_METATYPE(shelllet::interpreter::Container*)