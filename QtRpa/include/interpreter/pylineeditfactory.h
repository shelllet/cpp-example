#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyLineEditFactoryPrivate;
        class PyLineEditFactory : public Object {
            Q_DECLARE_PRIVATE(PyLineEditFactory)
        public:
            PyLineEditFactory(Object*parent = nullptr);

            static void embedded(py::module_& m);
        protected:
            PyLineEditFactory(PyLineEditFactoryPrivate& d, Object*parent = nullptr);
        };
    }
}
    