#include "interpreter/framework.h"
#include "interpreter/pypushbutton.h"
#include "interpreter/private/pypushbutton_p.h"
#include "qpushbutton.h"

namespace shelllet{
    namespace interpreter{
        
		

	}
}
using namespace shelllet::interpreter;
PyPushButton::PyPushButton(Object* parent /*= nullptr*/)
    :PyPushButton(*new PyPushButtonPrivate, parent)
{

}
PyPushButton::PyPushButton(PyPushButtonPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
void PyPushButton::importAttr()
{

}

void PyPushButton::embeddedModule(py::module_& m)
{
	py::class_<QPushButton>(m, "QPushButton")
		.def(py::init<QString, QPushButton*>())
		.def("set_text", &QPushButton::setText)
		;
}