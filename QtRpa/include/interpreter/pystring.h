#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyStringPrivate;
        class PyString : public Object {
            Q_DECLARE_PRIVATE(PyString)
        public:
            PyString(Object*parent = nullptr);

            static void embedded(py::module_& m);
        protected:
            PyString(PyStringPrivate& d, Object*parent = nullptr);
        };
    }
}
    