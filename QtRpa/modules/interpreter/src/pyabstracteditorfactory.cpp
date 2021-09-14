#include "interpreter/framework.h"
#include "property.hpp"
#include "interpreter/pyabstracteditorfactory.h"
#include "interpreter/private/pyabstracteditorfactory_p.h"

namespace shelllet{
    namespace interpreter{
        
	

	}
}
using namespace shelllet::interpreter;
PyAbstractEditorFactory::PyAbstractEditorFactory(Object* parent /*= nullptr*/)
    :PyAbstractEditorFactory(*new PyAbstractEditorFactoryPrivate, parent)
{

}
PyAbstractEditorFactory::PyAbstractEditorFactory(PyAbstractEditorFactoryPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}


void PyAbstractEditorFactory::embedded(py::module_& m)
{
	py::class_<AbstractEditorFactory<StringPropertyManager>>(m, "AbstractEditorFactory")
		;
}