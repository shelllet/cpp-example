#include "interpreter/framework.h"
#include "interpreter/pylinearlayout.h"
#include "interpreter/private/pylinearlayout_p.h"
#include "qgraphicslinearlayout.h"

namespace shelllet {
	namespace interpreter {



	}
}
using namespace shelllet::interpreter;
PyLinearLayout::PyLinearLayout(Object* parent /*= nullptr*/)
	:PyLinearLayout(*new PyLinearLayoutPrivate, parent)
{

}
PyLinearLayout::PyLinearLayout(PyLinearLayoutPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}


void PyLinearLayout::importAttr()
{

}

void PyLinearLayout::embeddedModule(py::module_& m)
{
	py::class_<QGraphicsLinearLayout, QGraphicsLayout> layout(m, "LinearLayout");
	layout.def(py::init<Qt::Orientation, QGraphicsLayoutItem*>())
		.def("set_contents_margins", &QGraphicsLinearLayout::setContentsMargins)
		.def("add_item", &QGraphicsLinearLayout::addItem)
		.def_static("create", [](Qt::Orientation orientation, QGraphicsLayoutItem* parent) { return new QGraphicsLinearLayout(orientation,parent); })
		;
	py::enum_<Qt::Orientation>(layout, "Orientation")
		.value("Vertical", Qt::Orientation::Vertical)
		.value("Horizontal", Qt::Orientation::Horizontal)
		.export_values();
}