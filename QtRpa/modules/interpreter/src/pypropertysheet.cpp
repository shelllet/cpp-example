#include "interpreter/framework.h"
#include "qwidget.h"
#include "property.hpp"
#include "interpreter/pypropertysheet.h"
#include "interpreter/private/pypropertysheet_p.h"

shelllet::interpreter::PyPropertySheet::PyPropertySheet(Object* parent /*= nullptr*/)
	:PyPropertySheet(*new PyPropertySheetPrivate, parent)
{

}

void shelllet::interpreter::PyPropertySheet::embedded(py::module_& m)
{
	py::class_<PropertySheet, std::unique_ptr<PropertySheet, py::nodelete>>(m, "PropertySheet")
		//.def(py::init<AbstractPropertyManager*>())
		.def("add_sub_property", &PropertySheet::addSubProperty)
		;
}

shelllet::interpreter::PyPropertySheet::PyPropertySheet(PyPropertySheetPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
