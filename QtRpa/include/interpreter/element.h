#pragma once
#include "component.h"
#include "common.hpp"
namespace shelllet {
	namespace interpreter {
		class ElementPrivate;
		class Element;
		class WrapperElement {
		public:
			WrapperElement(Element* item) : item(item) {

			}
		public:
			Element* item;
		};

		class Element : public Component {
			Q_DECLARE_PRIVATE_D(Object::d_ptr, Element)
		public:

			Element( QGraphicsItem* parent = nullptr, Object* p = nullptr);
			void paintWindowFrame(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		//	std::shared_ptr<properties::CompositeProperty> prop();


			Component* nextItem() const override;

		public:
			//static ElementItem* CreateElement(const py::object& property, QGraphicsItem* parent = nullptr);
			virtual void addItem(Element* item);

			virtual CompositeProperty* prop();
		protected:
			Element(ElementPrivate&, QGraphicsItem* parent = nullptr, Object* p=nullptr);
			void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;



			Qt::WindowFrameSection windowFrameSectionAt(const QPointF& pos) const override;


			bool windowFrameEvent(QEvent* e) override;

			QMimeData* mimeData();
		
		private:

		};
	}
}

