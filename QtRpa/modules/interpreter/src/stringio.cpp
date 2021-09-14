#include "interpreter/framework.h"
#include "interpreter/stringio.h"


namespace shelllet {
	
}
void shelllet::interpreter::StringIO::write(const std::string& message)
{
	LOG_INFO(PROJECT_NAME) << message;
}

void shelllet::interpreter::StringIO::embedded(py::module_& m)
{
	py::class_<shelllet::interpreter::StringIO>(m, "StringIO")
		.def(py::init<>())
		.def_static("write", &shelllet::interpreter::StringIO::write)
		;
}



