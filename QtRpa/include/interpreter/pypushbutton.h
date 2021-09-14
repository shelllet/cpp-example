#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyPushButtonPrivate;
        class PyPushButton : public Object {
            Q_DECLARE_PRIVATE(PyPushButton)
        public:
            PyPushButton(Object*parent = nullptr);

			static void importAttr();
			static void embeddedModule(py::module_& m);
        protected:
            PyPushButton(PyPushButtonPrivate& d, Object*parent = nullptr);
        };
    }
}
    