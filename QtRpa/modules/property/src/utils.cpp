#include "property/framework.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qcoreapplication.h"
#include "property/utils.h"
#include "property/private/utils_p.h"

namespace shelllet{
    namespace property{
        
    }
}
using namespace shelllet::property;
Utils::Utils(Object* parent /*= nullptr*/)
    :Utils(*new UtilsPrivate, parent)
{

}
Utils::Utils(UtilsPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}



QPixmap Utils::brushValuePixmap(const QBrush& b)
{
	QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
	img.fill(0);

	QPainter painter(&img);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(0, 0, img.width(), img.height(), b);
	QColor color = b.color();
	if (color.alpha() != 255) { // indicate alpha by an inset
		QBrush  opaqueBrush = b;
		color.setAlpha(255);
		opaqueBrush.setColor(color);
		painter.fillRect(img.width() / 4, img.height() / 4,
			img.width() / 2, img.height() / 2, opaqueBrush);
	}
	painter.end();
	return QPixmap::fromImage(img);
}

QIcon Utils::brushValueIcon(const QBrush& b)
{
	return QIcon(brushValuePixmap(b));
}

QString Utils::colorValueText(const QColor& c)
{
	return QCoreApplication::translate("Utils", "[%1, %2, %3] (%4)")
		.arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}

QPixmap Utils::fontValuePixmap(const QFont& font)
{
	QFont f = font;
	QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
	img.fill(0);
	QPainter p(&img);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setRenderHint(QPainter::Antialiasing, true);
	f.setPointSize(13);
	p.setFont(f);
	QTextOption t;
	t.setAlignment(Qt::AlignCenter);
	p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
	return QPixmap::fromImage(img);
}

QIcon Utils::fontValueIcon(const QFont& f)
{
	return QIcon(fontValuePixmap(f));
}

QString Utils::fontValueText(const QFont& f)
{
	return QCoreApplication::translate("Utils", "[%1, %2]")
		.arg(f.family()).arg(f.pointSize());
}

QString Utils::dateFormat()
{
	QLocale loc;
	QString format = loc.dateFormat(QLocale::ShortFormat);
	// Change dd.MM.yy, MM/dd/yy to 4 digit years
	if (format.count(QLatin1Char('y')) == 2)
		format.insert(format.indexOf(QLatin1Char('y')), QLatin1String("yy"));
	return format;
}

QString Utils::timeFormat()
{
	QLocale loc;
	// ShortFormat is missing seconds on UNIX.
	return loc.timeFormat(QLocale::LongFormat);
}

QString Utils::dateTimeFormat()
{
	QString format = dateFormat();
	format += QLatin1Char(' ');
	format += timeFormat();
	return format;
}