#include "interpreter/framework.h"
#include "interpreter/pyxmldocument.h"

void shelllet::interpreter::PyXmlDocument::embedded(py::module_& m)
{
	py::class_<XmlDocument, std::shared_ptr<XmlDocument>>(m, "XmlDocument")
		.def(py::init<>())
		.def("document_element", &XmlDocument::documentElement)
		;
}
