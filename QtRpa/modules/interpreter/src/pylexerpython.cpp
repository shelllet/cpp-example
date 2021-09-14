#include "interpreter/framework.h"
#include "interpreter/pylexerpython.h"
#include "interpreter/private/pylexerpython_p.h"
#include "Qsci/qscilexerpython.h"
namespace shelllet{
    namespace interpreter{
        
		

	}
}
using namespace shelllet::interpreter;
PyLexerPython::PyLexerPython(Object* parent /*= nullptr*/)
    :PyLexerPython(*new PyLexerPythonPrivate, parent)
{

}
PyLexerPython::PyLexerPython(PyLexerPythonPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
void PyLexerPython::importAttr()
{

}

void PyLexerPython::embeddedModule(py::module_& m)
{
	py::class_<QsciLexerPython>(m, "LexerPython")
		.def(py::init<QObject*>())
		;
}