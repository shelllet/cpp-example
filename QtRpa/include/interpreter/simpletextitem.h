#pragma once
#include "common.hpp"
#include "qgraphicsitem.h"
#include "qgraphicslayoutitem.h"

namespace shelllet {
	namespace interpreter {
		class SimpleTextItemPrivate;
		class SimpleTextItem : public QGraphicsSimpleTextItem, public QGraphicsLayoutItem, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, SimpleTextItem)
		public:
			SimpleTextItem(QGraphicsItem* parent = nullptr);
			SimpleTextItem(const QString& text, QGraphicsItem* parent = nullptr);
			~SimpleTextItem();
			void setColor(const QColor& color);

		protected:
			QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
			void setGeometry(const QRectF& rect) override;

		};

	}
}
Q_DECLARE_METATYPE(shelllet::interpreter::SimpleTextItem*)