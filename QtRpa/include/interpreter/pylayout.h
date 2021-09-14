#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyLayoutPrivate;
        class PyLayout : public Object {
            Q_DECLARE_PRIVATE(PyLayout)
        public:
            PyLayout(Object*parent = nullptr);
            static void embeddedModule(py::module_& m);
        protected:
            PyLayout(PyLayoutPrivate& d, Object*parent = nullptr);
        };
    }
}
    