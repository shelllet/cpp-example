#include "interpreter/elementmimedata.h"
#include "interpreter/private/elementmimedata_p.h"

shelllet::interpreter::ElementMimeData::ElementMimeData()
	: MimeData(*new ElementMimeDataPrivate)
{

}

void shelllet::interpreter::ElementMimeData::setElementItem(Element* item)
{
	Q_D(ElementMimeData);
	d->item = item;
}

shelllet::interpreter::Element* shelllet::interpreter::ElementMimeData::elementItem() const
{
	Q_D(const ElementMimeData);
	return d->item;
}
