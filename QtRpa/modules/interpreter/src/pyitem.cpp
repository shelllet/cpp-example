#include "interpreter/framework.h"
#include "interpreter/pyitem.h"
#include "interpreter/private/pyitem_p.h"
#include "qgraphicsitem.h"

namespace shelllet{
    namespace interpreter{
        
		

	}
}
using namespace shelllet::interpreter;
PyItem::PyItem(Object* parent /*= nullptr*/)
    :PyItem(*new PyItemPrivate, parent)
{

}
PyItem::PyItem(PyItemPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}

void PyItem::embeddedModule(py::module_& m)
{
	py::class_<QGraphicsItem>(m, "Item");
	;
}
