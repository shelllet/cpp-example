#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
        class PyScintillaPrivate;
        class PyScintilla : public Object {
            Q_DECLARE_PRIVATE(PyScintilla)
        public:
            PyScintilla(QGraphicsItem*parent = nullptr, Object*parent2 = nullptr);
			static void importAttr();
			static void embeddedModule(py::module_& m);
        protected:
            PyScintilla(PyScintillaPrivate& d, QGraphicsItem* parent = nullptr, Object*parent2 = nullptr);
        };
    }
}
    