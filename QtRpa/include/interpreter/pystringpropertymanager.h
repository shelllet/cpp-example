#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyStringPropertyManagerPrivate;
        class PyStringPropertyManager : public Object {
            Q_DECLARE_PRIVATE(PyStringPropertyManager)
        public:
            PyStringPropertyManager(Object*parent = nullptr);

            static void embedded(py::module_& m);
            static void importModule();
        protected:
            PyStringPropertyManager(PyStringPropertyManagerPrivate& d, Object*parent = nullptr);
        };
    }
}
    