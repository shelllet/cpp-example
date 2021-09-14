#include "common/image.h"
#include "common/private/image_p.h"
#include "qimage.h"
#include "qpixmap.h"
shelllet::common::Image::Image()
	: Image(*new ImagePrivate)
{

}

shelllet::common::Image::Image(const QPixmap* pixmap)
	: Image(*new ImagePrivate)
{
	Q_D(Image);
	*d->image = { pixmap->toImage() };
}

shelllet::common::Image::Image(const uint8_t* data, int32_t width, int32_t height, UInt32 bytesPerLine, QImage::Format format)
	: Image(*new ImagePrivate)
{
	Q_D(Image);
	d->image.reset(new QImage(data, width, height, bytesPerLine, format));
}

shelllet::common::Image::Image(const QImage* image)
	: Image(*new ImagePrivate)
{
	Q_D(Image);

	*d->image = { *image };
}

shelllet::common::Image::Image(ImagePrivate& d)
	: Object(d, nullptr)
{
	d.image = std::make_unique<QImage>();
}
