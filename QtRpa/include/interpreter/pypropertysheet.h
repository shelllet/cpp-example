#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyPropertySheetPrivate;
        class PyPropertySheet : public Object {
            Q_DECLARE_PRIVATE(PyPropertySheet)
        public:
            PyPropertySheet(Object*parent = nullptr);
            static void embedded(py::module_& m);
        protected:
            PyPropertySheet(PyPropertySheetPrivate& d, Object*parent = nullptr);
        };
    }
}
    