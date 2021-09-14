#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyLayoutItemPrivate;

       
        class PyLayoutItem : public Object {
            Q_DECLARE_PRIVATE(PyLayoutItem)
        public:
            PyLayoutItem(Object*parent = nullptr);
            static void embeddedModule(py::module_& m);
        protected:
            PyLayoutItem(PyLayoutItemPrivate& d, Object*parent = nullptr);
        };
    }
}
    