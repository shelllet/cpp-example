#pragma once
#include "common.hpp"
#include "common/private/object_p.h"
namespace pybind11 {
	class object;
}
namespace shelllet {
	namespace interpreter {
	
		class PyStdErrOutStreamRedirectPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(PyStdErrOutStreamRedirect)
		public:
			UniquePointer<pybind11::object> stdout_raw;
			UniquePointer<pybind11::object> stderr_raw;
			UniquePointer<pybind11::object> stdout_buffer;
			UniquePointer<pybind11::object> stderr_buffer;
		};
	}
}
