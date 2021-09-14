#pragma once
#include "object_p.h"
class QImage;
namespace shelllet {
	namespace common {
		class ImagePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(Image)
		public:
			UniquePointer<QImage> image;
		};
	}
}
