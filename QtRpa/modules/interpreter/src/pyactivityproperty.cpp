#include "interpreter/framework.h"
#include "property.hpp"
#include "interpreter/composite_property.h"
#include "interpreter/pyactivityproperty.h"
#include "interpreter/private/pyactivityproperty_p.h"

std::shared_ptr<XmlDocument> shelllet::interpreter::PyActivityProperty::getNode()
{
	try
	{

		PYBIND11_OVERRIDE_NAME(std::shared_ptr<XmlDocument>, CompositeProperty, "get_doc", getNode);
	}
	catch (const py::error_already_set& err)
	{
		LOG_ERROR(PROJECT_NAME) << err.what();
	}
	//return CompositeProperty::getNode().release();
}

void shelllet::interpreter::PyActivityProperty::exec()
{
	try
	{
		PYBIND11_OVERRIDE(void, CompositeProperty, exec);
	}
	catch (const py::error_already_set& err)
	{
		LOG_ERROR(PROJECT_NAME) << err.what();
	}
}

void shelllet::interpreter::PyActivityProperty::embedded(py::module_& m)
{
	py::class_<CompositeProperty, PyActivityProperty >(m, "Property")
		.def(py::init<const XmlNode&>())
		.def("get_input", &CompositeProperty::getInput)
		.def("get_output", &CompositeProperty::getOutput)
		.def("get_doc", &CompositeProperty::getNode)
		;

}

void shelllet::interpreter::PyActivityProperty::importModule()
{
	py::module::import("interpreter").attr(QUOTED(Property));
}

shelllet::interpreter::PyActivityProperty::PyActivityProperty(const XmlNode& node)
	: PyActivityProperty(*new PyActivityPropertyPrivate, node)
{

}

shelllet::interpreter::PyActivityProperty::PyActivityProperty(PyActivityPropertyPrivate& d, const XmlNode& node)
	: CompositeProperty(d, node, nullptr)
{

}

PropertySheet* shelllet::interpreter::PyActivityProperty::getInput(PropertyBrowser* browser)
{
	try
	{
		PYBIND11_OVERRIDE_NAME(PropertySheet*, CompositeProperty, "get_input", getInput, browser);

	}
	catch (const py::error_already_set& err)
	{
		LOG_ERROR(PROJECT_NAME) << err.what();
	}
	return nullptr;
}

PropertySheet* shelllet::interpreter::PyActivityProperty::getOutput(PropertyBrowser* browser)
{
	PYBIND11_OVERRIDE(PropertySheet*, CompositeProperty, getOutput, browser);
}
