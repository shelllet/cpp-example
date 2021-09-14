#pragma once
#include "object_p.h"
namespace shelllet {
	namespace common {
		template <typename T>
		class RectPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(Rect)
		public:
			std::variant<QRect, QRectF> rect;


		};
	}
}
