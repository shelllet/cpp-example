#pragma once
#include "qgraphicswidget.h"
#include "common.hpp"
#include "qgraphicslinearlayout.h"
namespace shelllet {
	namespace interpreter {
		class ComponentPrivate;
		
		class Component : public QGraphicsWidget, public Object {
			Q_DECLARE_PRIVATE_D(Object::d_ptr, Component)
			
		protected:
			Component(ComponentPrivate&, QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

		public:
			virtual Component* nextItem() const;
			Component* previousItem() const;

			void setNextItem(const Component* item);
			void setPreviousItem(const Component* item);

		virtual	void removeItem(QGraphicsLayoutItem* item);


		void setGeometry(const QRectF& rect) override;

		//QGraphicsLinearLayout* linearLayout() const;
		private:

		};
	}
}

