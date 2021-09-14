#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyLexerPythonPrivate;
        class PyLexerPython : public Object {
            Q_DECLARE_PRIVATE(PyLexerPython)
        public:
            PyLexerPython(Object*parent = nullptr);
			static void importAttr();
			static void embeddedModule(py::module_& m);
        protected:
            PyLexerPython(PyLexerPythonPrivate& d, Object*parent = nullptr);
        };
    }
}
    