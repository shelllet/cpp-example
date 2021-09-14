#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyPropertyBrowserPrivate;
        class PyPropertyBrowser : public Object {
            Q_DECLARE_PRIVATE(PyPropertyBrowser)
        public:
            PyPropertyBrowser(Object*parent = nullptr);
            static void embedded(py::module_& m);
        protected:
            PyPropertyBrowser(PyPropertyBrowserPrivate& d, Object*parent = nullptr);
        };
    }
}
    