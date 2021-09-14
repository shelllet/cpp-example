#include "interpreter/framework.h"
#include "interpreter/pyxmlattribute.h"

void shelllet::interpreter::PyXmlAttribute::embedded(py::module_& m)
{
	py::class_<XmlAttribute>(m, "XmlAttribute")
		.def("value", [](XmlAttribute& attr) { return attr.value().toStdString(); })
		.def("set_value", [](XmlAttribute& attr, const std::string& value) { attr.setValue(value); })
		;
}
