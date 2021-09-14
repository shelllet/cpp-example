#pragma once
#include "component.h"
namespace shelllet {
	namespace interpreter {
		class DropAreaPrivate;
		class DropArea : public Component
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, DropArea)
		public:

			DropArea(QGraphicsItem* parent = nullptr);






			void setGeometry(const QRectF& rect) override;

		protected:

			//QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
		
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

			void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;


			void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;


			void dropEvent(QGraphicsSceneDragDropEvent* event) override;


			QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;


			void	removeItem(QGraphicsLayoutItem* item) override;
		private:
			void addItem(QGraphicsLayoutItem* item);
	

			void hideExtraItem();
			void showExtraItem();


		};
	}
}