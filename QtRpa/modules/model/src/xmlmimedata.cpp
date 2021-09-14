#include "model/xmlmimedata.h"
#include "model/private/xmlmimedata_p.h"
shelllet::model::XmlMimeData::XmlMimeData(const XmlNode& node)
	: MimeData(*new XmlMimeDataPrivate)
{
	Q_D(XmlMimeData);
	d->doc.appendCopy(node);
}

XmlNode shelllet::model::XmlMimeData::documentElement() const
{
	Q_D(const XmlMimeData);

	return d->doc.documentElement();
}

void shelllet::model::XmlMimeData::setSourceItem(QGraphicsItem* source)
{
	Q_D(XmlMimeData);
	d->source = source;
}

QGraphicsItem* shelllet::model::XmlMimeData::sourceItem() const
{
	Q_D(const XmlMimeData);
	return d->source;
}
