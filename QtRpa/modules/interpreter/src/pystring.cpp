#include "interpreter/framework.h"
#include "common.hpp"
#include "interpreter/pystring.h"
#include "interpreter/private/pystring_p.h"

shelllet::interpreter::PyString::PyString(Object* parent /*= nullptr*/)
    :PyString(*new PyStringPrivate, parent)
{

}
shelllet::interpreter::PyString::PyString(PyStringPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}

void shelllet::interpreter::PyString::embedded(py::module_& m)
{
	py::class_<String>(m, "String")
		.def(py::init<const std::string&>())
		.def(py::init<const char *>())
		.def("__repr__", [](const String& s) { return s.toStdString(); })
		;
}
