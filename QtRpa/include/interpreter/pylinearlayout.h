#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyLinearLayoutPrivate;
        class PyLinearLayout : public Object {
            Q_DECLARE_PRIVATE(PyLinearLayout)
        public:
            PyLinearLayout(Object*parent = nullptr);
            static void importAttr();
            static void embeddedModule(py::module_& m);
        protected:
            PyLinearLayout(PyLinearLayoutPrivate& d, Object*parent = nullptr);
        };
    }
}
    