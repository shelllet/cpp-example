#pragma once
#include "common.hpp"
#include "qgraphicssvgitem.h"
#include "qgraphicslayout.h"


namespace shelllet {
	namespace interpreter {
		class SvgItemPrivate;
		class SvgItem : public QGraphicsSvgItem, public QGraphicsLayoutItem, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, SvgItem)
		public:

			SvgItem(const String& fileName, QGraphicsItem* parent = 0);
			void setSize(const QSize& size);
		protected:

			SvgItem(SvgItemPrivate&d, const String& fileName, QGraphicsItem* parent = 0);

			//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

			//QRectF boundingRect() const override;

			void setGeometry(const QRectF& rect) override;

			QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

		};
	}
}