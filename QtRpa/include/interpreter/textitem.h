#pragma once
#include "common.hpp"
#include "qgraphicsitem.h"
#include "qgraphicslayoutitem.h"

namespace shelllet {
	namespace interpreter {
		class TextItemPrivate;
		class TextItem : public QGraphicsTextItem, public QGraphicsLayoutItem, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, TextItem)
		public:
			TextItem(QGraphicsItem* parent = nullptr);

			void setColor(const QColor& color);

		protected:
			QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

		};
	}
}