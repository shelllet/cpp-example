#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyWidgetPrivate;
        class PyWidget : public Object {
            Q_DECLARE_PRIVATE(PyWidget)
        public:
            PyWidget(Object*parent = nullptr);
            static void embeddedModule(py::module_& m);
        protected:
            PyWidget(PyWidgetPrivate& d, Object*parent = nullptr);
        };
    }
}
    