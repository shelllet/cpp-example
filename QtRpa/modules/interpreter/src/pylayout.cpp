#include "interpreter/framework.h"
#include "interpreter/pylayout.h"
#include "interpreter/private/pylayout_p.h"
#include "qgraphicslayout.h"

namespace shelllet {
	namespace interpreter {



	}
}
using namespace shelllet::interpreter;
PyLayout::PyLayout(Object* parent /*= nullptr*/)
	:PyLayout(*new PyLayoutPrivate, parent)
{

}
PyLayout::PyLayout(PyLayoutPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
void PyLayout::embeddedModule(py::module_& m)
{
	py::class_<QGraphicsLayout, QGraphicsLayoutItem>(m, "Layout")
		;
}