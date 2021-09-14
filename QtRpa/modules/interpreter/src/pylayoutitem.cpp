#include "interpreter/framework.h"
#include "interpreter/pylayoutitem.h"
#include "interpreter/private/pylayoutitem_p.h"
#include "qgraphicslayoutitem.h"

namespace shelllet {
	namespace interpreter {



	}
}
using namespace shelllet::interpreter;
PyLayoutItem::PyLayoutItem(Object* parent /*= nullptr*/)
	:PyLayoutItem(*new PyLayoutItemPrivate, parent)
{

}
PyLayoutItem::PyLayoutItem(PyLayoutItemPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
void PyLayoutItem::embeddedModule(py::module_& m)
{
	py::class_<QGraphicsLayoutItem>(m, "LayoutItem");
		;
}