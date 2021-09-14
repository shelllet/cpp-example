#include "interpreter/framework.h"
#include "interpreter/pyxmlnode.h"
void shelllet::interpreter::PyXmlNode::embedded(py::module_& m)
{
	 py::class_<XmlNode> node(m, "XmlNode");

		node.def("append_child", [](XmlNode& node, const std::string& name) { return node.appendChild(name); })
		.def("append_attribute", [](XmlNode& node, const std::string& name) { return node.appendAttribute(name); })
		.def("append_child", static_cast<XmlNode(XmlNode::*)(XmlNodeType)>(&XmlNode::appendChild))
		.def("set_value", [](XmlNode& node, const std::string& value) { node.setValue(value); })
		.def("attribute", [](XmlNode& node, const std::string& name) { return node.attribute(name); })
		;

	py::enum_<XmlNodeType>(node, "Type")
		.value("Null", XmlNodeType::Null)
		.value("Document", XmlNodeType::Document)
		.value("Element", XmlNodeType::Element)
		.value("PCData", XmlNodeType::PCData)
		.value("CData", XmlNodeType::CData)
		.value("Comment", XmlNodeType::Comment)
		.value("PI", XmlNodeType::PI)
		.value("Declaration", XmlNodeType::Declaration)
		.value("DocType", XmlNodeType::DocType)
		.export_values();
}
