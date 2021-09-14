#include "interpreter/framework.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexerpython.h"
#include "qgraphicsproxywidget.h"
#include "qgraphicsitem.h"
#include "interpreter/pyscintilla.h"
#include "interpreter/private/pyscintilla_p.h"

namespace shelllet {
	namespace interpreter {



	}
}
using namespace shelllet::interpreter;
PyScintilla::PyScintilla(QGraphicsItem* parent, Object* /*parent*/ /*= nullptr*/)
	:PyScintilla(*new PyScintillaPrivate, parent)
{

}
PyScintilla::PyScintilla(PyScintillaPrivate& d, QGraphicsItem* parent, Object* /*parent*/ /*= nullptr*/)
	: Object(d, nullptr)
{
	d.scintilla = std::make_unique<QsciScintilla>();
	d.proxyWidget = std::make_unique<QGraphicsProxyWidget>(parent);
	d.proxyWidget->setWidget(d.scintilla.get());
}

void PyScintilla::importAttr()
{

}

void PyScintilla::embeddedModule(py::module_& m)
{
	py::class_<PyScintilla>(m, "Scintilla")
		.def(py::init<QGraphicsItem*>())
		.def("set_lexer", [](PyScintilla& sci, QsciLexer* lexer) {sci.d_func()->scintilla->setLexer(lexer); })
		.def("set_utf8", [](PyScintilla& sci, bool cp) {sci.d_func()->scintilla->setUtf8(cp); })
		.def("set_text", [](PyScintilla& sci, const String& text) {sci.d_func()->scintilla->setText(*text.toQString()); })
		.def("widget", [](PyScintilla& sci) { return sci.d_func()->proxyWidget.get(); })
		//.def_static("create", [](QGraphicsItem* parent) { return new PyScintilla(parent); })
		;
}