#pragma once
#include "common.hpp"
#include "qgraphicsitem.h"
#include "qgraphicslayout.h"


namespace shelllet {
	namespace interpreter {
		class PlaceholderItemPrivate;
		class PlaceholderItem : public QGraphicsRectItem, public QGraphicsLayoutItem, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, PlaceholderItem)
		public:

			PlaceholderItem(QGraphicsItem* parent = 0);

		protected:
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

			QRectF boundingRect() const override;

			void setGeometry(const QRectF& rect);

			QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

		};
	}
}