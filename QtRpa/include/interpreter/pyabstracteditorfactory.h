#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyAbstractEditorFactoryPrivate;

        //template <typename T, typename TBase>
        class PyAbstractEditorFactory : public Object {
            Q_DECLARE_PRIVATE(PyAbstractEditorFactory)
        public:
            PyAbstractEditorFactory(Object*parent = nullptr);


            static void  embedded(py::module_& m);

        protected:
            PyAbstractEditorFactory(PyAbstractEditorFactoryPrivate& d, Object*parent = nullptr);
        };
    }
}
    