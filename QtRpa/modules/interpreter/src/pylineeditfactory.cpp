#include "interpreter/framework.h"
#include "property.hpp"
#include "interpreter/pylineeditfactory.h"
#include "interpreter/private/pylineeditfactory_p.h"

shelllet::interpreter::PyLineEditFactory::PyLineEditFactory(Object* parent /*= nullptr*/)
	:PyLineEditFactory(*new PyLineEditFactoryPrivate, parent)
{

}

void shelllet::interpreter::PyLineEditFactory::embedded(py::module_& m)
{
	using StringEditorFactory = AbstractEditorFactory<StringPropertyManager>;
	py::class_<LineEditFactory, StringEditorFactory, UniquePointer<LineEditFactory, py::nodelete>>(m, "LineEditFactory")
		.def(py::init<>())
		.def_static("create", []() { return new LineEditFactory; })
		;
}

shelllet::interpreter::PyLineEditFactory::PyLineEditFactory(PyLineEditFactoryPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
