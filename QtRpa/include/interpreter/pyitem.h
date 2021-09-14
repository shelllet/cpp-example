#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyItemPrivate;
        class PyItem : public Object {
            Q_DECLARE_PRIVATE(PyItem)
        public:
            PyItem(Object*parent = nullptr);
            static void embeddedModule(py::module_& m);
        protected:
            PyItem(PyItemPrivate& d, Object*parent = nullptr);
        };
    }
}
    