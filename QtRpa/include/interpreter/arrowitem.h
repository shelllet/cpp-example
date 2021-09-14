#pragma once
#include "svgitem.h"

namespace shelllet {
	namespace interpreter {
		class ArrowItemPrivate;
		class ArrowItem : public SvgItem
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, ArrowItem)
		public:
			ArrowItem(QGraphicsItem* parent = nullptr);
		protected:
			//void setGeometry(const QRectF& rect) override;
		};
	}
}