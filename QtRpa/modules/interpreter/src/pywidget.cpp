#include "interpreter/framework.h"
#include "interpreter/pywidget.h"
#include "interpreter/private/pywidget_p.h"
#include "qgraphicswidget.h"

namespace shelllet{
    namespace interpreter{
        
		}
}
using namespace shelllet::interpreter;
PyWidget::PyWidget(Object* parent /*= nullptr*/)
    :PyWidget(*new PyWidgetPrivate, parent)
{

}
PyWidget::PyWidget(PyWidgetPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}

void PyWidget::embeddedModule(py::module_& m)
{
	py::class_<QGraphicsWidget, QGraphicsItem, QGraphicsLayoutItem>(m, "Widget", py::multiple_inheritance());
	;
}


