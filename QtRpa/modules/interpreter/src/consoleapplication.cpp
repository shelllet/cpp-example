#include "interpreter/framework.h"
#include "common.hpp"
#include "events.hpp"
#include "interpreter/composite_property.h"
#include "interpreter/consoleapplication.h"
#include "common/private/object_p.h"
#include "interpreter/private/consoleapplication_p.h"
#include "interpreter/mybase.h"
#include "qcoreapplication.h"
#include "libzippp/libzippp.h"
#include <boost/range/adaptor/transformed.hpp>
#include "interpreter/pystderroutstreamredirect.h"
#include "interpreter/pymodule.h"
#include "qglobalstatic.h"
#include "interpreter/propparser.h"
//extern "C" PyObject * PyInit_example();

namespace py = pybind11;

namespace shelllet {
	using namespace pugi;
	using namespace libzippp;
	using boost::adaptors::transformed;

	/*static void WalkImportCall(Set<String>& v, const XmlNodeRange<XmlNodeIterator>& items) {
		for (const auto& i : items) {
			if (i.type() == XmlNodeType::Element) {
				auto prop = CompositeProperty::CreateNode(i);
				if (prop) {
					v.insert(prop->getImport());
				}

				WalkImportCall(v, i.children());
			}
		}
	}
	static void WalkCodeCall(std::ostringstream& ss, const xml_object_range<xml_node_iterator>& items) {
		for (const auto& i : items) {
			if (i.type() == pugi::node_element) {
				auto prop = CompositeProperty::CreateNode(i);
				if (prop) {
					prop->getCode(ss);
				}
				ss << std::endl;
				WalkCodeCall(ss, i.children());
			}
		}
	}*/
	static void WalkCodeCall2(const XmlNodeRange<XmlNodeIterator>& items) {
		for (const auto& i : items) {
			if (i.type() == XmlNodeType::Element) {
				auto prop = new interpreter::PropParser(i);
				if (prop) {
					prop->prop()->exec();
				}

				WalkCodeCall2(i.children());
			}
		}
	}

	namespace interpreter {


		Q_GLOBAL_STATIC(ConsoleApplication, __ConsoleApplication__)
	}

}





shelllet::interpreter::ConsoleApplication::ConsoleApplication()
	:ConsoleApplication(*new ConsoleApplicationPrivate)
{

}
shelllet::interpreter::ConsoleApplication::ConsoleApplication(ConsoleApplicationPrivate& d)
	: Object(d, nullptr)
{
	//	Helper::register_meta_type();
}

shelllet::interpreter::ConsoleApplication::~ConsoleApplication()
{

}

String shelllet::interpreter::ConsoleApplication::translate(const String& xml)
{
	std::ostringstream ss;
	xml_document doc;
	doc.load_string(xml.toStdString().c_str());
	Set<String> v;
	//WalkImportCall(v, doc.document_element().children());
//	ss << common::join(v | transformed([](const String& d) { return std::move(d.toStdString()); }), endline()) << std::endl;
	//WalkCodeCall(ss, doc.document_element().children());


	LOG_DEBUG("Velkhana") << "# generate code: " << std::endl
		<< ss.str();
	return ss.str();
}

void shelllet::interpreter::ConsoleApplication::run(QEvent* event)
{
	ConsoleEvent* e = dynamic_cast<ConsoleEvent*>(event);
	BOOST_SCOPE_EXIT(void)	{
		PyStdErrOutStreamRedirect::getInstance()->release();
		qApp->quit();
	}BOOST_SCOPE_EXIT_END

		if (!e->filename().isExist()) {
			LOG_WARNING("engine") << "# the file not exist: " << e->filename();
			return;
		}
	//std::streambuf* coutbuf = std::cerr.rdbuf();
//
	//std::stringstream out;

	//std::cerr.rdbuf(out.rdbuf());
	//String code;
	Path src = e->filename();
	if (src.isDir()) {
		src /= Environment::getInstance()->indexXmlPath();
	}



	bool is_zip = false;
	//if (file.extension() == Environment::getInstance()->getOptions()->pkg_extension) {
		//ZipArchive zf(src.toString().toStdString());
		//zf.open(ZipArchive::ReadOnly);

		//	ZipEntry entry2 = zf.getEntry(common::Environment::getInstance()->indexJsPath().string());
			//code = entry2.readAsText();
	is_zip = true;
	//}
//	else {
//		//code = translate(File::readAllAsText(src));
//	}


	try {
		//Py_SetPythonHome(L"C://Python39");
	//	Py_SetPath(Environment::getInstance()->getOptions()->module_search_path.wstring().c_str());
		//Py_SetProgramName(QCoreApplication::applicationName().toStdWString().c_str());

		py::object scope = py::module_::import("__main__").attr("__dict__");

		//	py::exec("import example; example.StringIO.write('sss')", scope);
		//	main_namespace["precreated_object"] = Mybase();
		//py::exec(code.toStdString(), scope);
		XmlDocument doc;
		doc.loadFile(src);
		WalkCodeCall2(doc.documentElement().children());
	}
	catch (py::error_already_set& eas) {
		// Discard the Python error using Python APIs, using the C++ magic
		// variable __func__. Python already knows the type and value and of the
		// exception object.
		QByteArray data = QString::fromUtf8(eas.what()).toUtf8();
		auto s = data.constData();
		LOG_WARNING("rap") << eas.what() << std::endl;
		//eas.discard_as_unraisable(__func__);
	}


	
	//std::cerr.rdbuf(coutbuf);
}

void shelllet::interpreter::ConsoleApplication::initialize()
{
	Q_D(ConsoleApplication);
	PyModule::getInstance()->initLibPath();
	d->guard = std::make_unique<pybind11::scoped_interpreter>();


	PyModule::getInstance()->importModules();
	PyStdErrOutStreamRedirect::getInstance()->initialize();

	{
#ifdef _DEBUG

		py::exec("import sys; print(sys.path);");

#endif // _DEBUG
	}

	{
#ifdef _DEBUG
		py::exec("import interpreter; import pprint; print(pprint.pformat(interpreter.__dict__))");
#endif // _DEBUG
	}
}

shelllet::interpreter::ConsoleApplication* shelllet::interpreter::ConsoleApplication::getInstance()
{
	return __ConsoleApplication__;
}
