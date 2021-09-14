#include "interpreter/framework.h"
#include "interpreter/pymodule.h"
//#include "interpreter/process.h"
#include "interpreter/composite_property.h"
#include "interpreter/containeritem.h"
#include "interpreter/stringio.h"
#include "interpreter/pyactivityproperty.h"
#include "interpreter/pyxmldocument.h"
#include "interpreter/pyxmlnode.h"
#include "interpreter/pyxmlattribute.h"
#include "interpreter/pystring.h"
#include "interpreter/pycontainer.h"
#include "interpreter/pyelement.h"
#include "interpreter/pylineeditfactory.h"
#include "interpreter/pystringpropertymanager.h"
#include "interpreter/pypropertybrowser.h"
#include "interpreter/pypropertysheet.h"
#include "interpreter/pyabstracteditorfactory.h"
#include "interpreter/pylinearlayout.h"
#include "interpreter/pyscintilla.h"
#include "interpreter/pylexerpython.h"
#include "interpreter/pylayoutitem.h"
#include "interpreter/pylayout.h"
#include "interpreter/pyitem.h"
#include "interpreter/pywidget.h"
namespace shelllet {
	namespace py = pybind11;
	namespace interpreter
	{
		class PyModulePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(PyModule)
		public:
		};

		Q_GLOBAL_STATIC(PyModule, __pymodule__)

	}
}

using namespace shelllet::interpreter;
shelllet::interpreter::PyModule::PyModule()
	: Object(*new PyModulePrivate, nullptr)
{

}

void shelllet::interpreter::PyModule::importModules()
{
	try
	{


		py::module::import("interpreter").attr(QUOTED(StringIO));
		py::module::import("interpreter").attr(QUOTED(String));
		PyActivityProperty::importModule();
		py::module::import("interpreter").attr(QUOTED(XmlDocument));
		py::module::import("interpreter").attr(QUOTED(XmlNode));
		py::module::import("interpreter").attr(QUOTED(XmlAttribute));
		PyElement<>::importModule();
		py::module::import("interpreter").attr(QUOTED(Container));
		py::module::import("interpreter").attr(QUOTED(WrapperElement));
		py::module::import("interpreter").attr(QUOTED(LineEditFactory));
		py::module::import("interpreter").attr(QUOTED(PropertyBrowser));
		py::module::import("interpreter").attr(QUOTED(AbstractEditorFactory));
		PyStringPropertyManager::importModule();
	
		PyLinearLayout::importAttr();
		PyScintilla::importAttr();
		PyLexerPython::importAttr();
	}
	catch (const py::error_already_set& err)
	{
		LOG_ERROR(PROJECT_NAME) << err.what();
	}
}

void shelllet::interpreter::PyModule::initLibPath()
{
	std::vector<std::wstring> ss;
	ss.push_back( L"D:\\vcpkg\\installed\\x64-windows-mixed\\share\\python3\\Lib");
	ss.push_back( Environment::getInstance()->getViewPath().toString().toStdWString());
	Py_SetPath((boost::join(ss, ";")).c_str());
	Py_SetProgramName(L"creator.exe");
	Py_SetPythonHome(Path::applicationDirPath().toString().toStdWString().c_str());
	//py::module_::import("sys").attr("path").cast<py::list>().append("D:\\vcpkg\\installed\\x64-windows-mixed\\share\\python3\\Lib");
	//py::module_::import("sys").attr("path").cast<py::list>().append("C:\\Users\\admin\\Source\\Repos\\rpa\\library");
	//py::module_::import("sys").attr("path").cast<py::list>().append(Environment::getInstance()->getViewPath().toString().toStdString());
}

shelllet::interpreter::PyModule* shelllet::interpreter::PyModule::getInstance()
{
	return __pymodule__;
}



PYBIND11_EMBEDDED_MODULE(interpreter, m) {
	shelllet::interpreter::StringIO::embedded(m);
	shelllet::interpreter::PyActivityProperty::embedded(m);
	shelllet::interpreter::PyXmlDocument::embedded(m);
	shelllet::interpreter::PyXmlNode::embedded(m);
	shelllet::interpreter::PyXmlAttribute::embedded(m);
	shelllet::interpreter::PyString::embedded(m);

	shelllet::interpreter::PyStringPropertyManager::embedded(m);
	shelllet::interpreter::PyPropertyBrowser::embedded(m);
	shelllet::interpreter::PyPropertySheet::embedded(m);
	shelllet::interpreter::PyAbstractEditorFactory::embedded(m);
	shelllet::interpreter::PyLineEditFactory::embedded(m);
	PyLayoutItem::embeddedModule(m);
	PyItem::embeddedModule(m);
	PyWidget::embeddedModule(m);
	PyElement<>::embedded(m);
	PyContainer<>::embedded(m);
	PyLayout::embeddedModule(m);
	PyLinearLayout::embeddedModule(m);

	PyScintilla::embeddedModule(m);
	PyLexerPython::embeddedModule(m);

}

