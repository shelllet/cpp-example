#include "interpreter/framework.h"
#include "interpreter/composite_property.h"
#include "qglobalstatic.h"
#include "interpreter/element.h"
#include "interpreter/propparser.h"
#include "private/qobject_p.h"
#include "interpreter/private/propparser_p.h"
#include "interpreter/pyelement.h"
#include "interpreter/containeritem.h"
//#include "qgraphicsitem.h"
namespace shelllet {
	namespace interpreter {
		//	namespace py = pybind11;
			//Q_GLOBAL_STATIC(PropParser, __propparser__)
	}
}
//py::object shelllet::interpreter::PropParser::loadPy(const XmlNode& node)
//{
//	Q_D(PropParser);
//	
//	return py::cast(nullptr);
//}

//shelllet::interpreter::PropParser* shelllet::interpreter::PropParser::getInstance()
//{
//	return __propparser__;
//}

//shelllet::interpreter::PropParser::PropParser(QObject* parent /*= nullptr*/)
//	: Object(*new PropParserPrivate, parent)
//{
//
//}

shelllet::interpreter::Element* shelllet::interpreter::PropParser::element()
{
	Q_D(PropParser);

	try
	{

		//auto* c = py::cast<Container*>(d->ooo);

		//auto* cc = dynamic_cast<ElementItem*>(c);
		return	py::cast<Element*>(d->ooo);


	}
	catch (const py::cast_error& err)
	{
		LOG_ERROR(PROJECT_NAME) << err.what();
	}

}

shelllet::interpreter::CompositeProperty* shelllet::interpreter::PropParser::prop()
{
	return element()->prop();
}

shelllet::interpreter::PropParser::PropParser(const XmlNode& node, Element* parentItem /*= nullptr*/, Object* parent /*= nullptr*/)
	: Object(*new PropParserPrivate, parent)
{
	Q_D(PropParser);
	try
	{
		using namespace py::literals;
		//	py::dict locals = py::dict("data"_a = py::cast(node));


		//py::eval_file(p.toString().toStdString(), py::globals(), locals);

		LOG_DEBUG(PROJECT_NAME) << "category: " << node.attribute("category").value();
		LOG_DEBUG(PROJECT_NAME) << "class: " << node.attribute("meta").value();

		py::object Decimal = py::module_::import((node.attribute("category").value() + "." + node.name()).toUtf8())
			.attr(node.attribute("meta").value().toUtf8());


		d->ooo = Decimal(py::cast(node), py::cast(parentItem));

		//auto result = locals["result"].cast<CompositeProperty*>();
		//return pi;

		element()->setWindowTitle(*prop()->displayName().toQString());

		QObject::connect(prop(), &CompositeProperty::displayNameChanged, [this]() { element()->setWindowTitle(*prop()->displayName().toQString()); });
		//return UniquePointer<CompositeProperty>(py::cast<CompositeProperty*>(pi));

	}
	catch (py::error_already_set& eas)
	{
		LOG_WARNING("rap") << eas.what();
	}

}
