#include "interpreter/framework.h"
#include "property.hpp"
#include "interpreter/pypropertybrowser.h"
#include "interpreter/private/pypropertybrowser_p.h"

shelllet::interpreter::PyPropertyBrowser::PyPropertyBrowser(Object* parent /*= nullptr*/)
    :PyPropertyBrowser(*new PyPropertyBrowserPrivate, parent)
{

}

void shelllet::interpreter::PyPropertyBrowser::embedded(py::module_& m)
{
	py::class_<PropertyBrowser>(m, "PropertyBrowser")
		.def(py::init<>())
		.def("set_factory_for_manager", &PropertyBrowser::setFactoryForManager<StringPropertyManager>)
		;
}

shelllet::interpreter::PyPropertyBrowser::PyPropertyBrowser(PyPropertyBrowserPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
