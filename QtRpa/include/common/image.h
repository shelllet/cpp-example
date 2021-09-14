#pragma once
#include "framework.h"
#include "alias.h"
#include "object.h"
#include "qimage.h"
namespace shelllet {
	namespace common {
		class ImagePrivate;
		class Image : public Object {
			Q_DECLARE_PRIVATE(Image)
		public:
			Image();
			Image(const QImage* image);
			Image(const QPixmap* pixmap);
			Image(const uint8_t* data, int32_t width, int32_t height, UInt32 bytesPerLine, QImage::Format format);
		protected:
			Image(ImagePrivate& d);
		};
	}
}
