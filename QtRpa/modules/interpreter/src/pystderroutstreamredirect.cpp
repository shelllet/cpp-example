#include "pybind11/embed.h"
#include "interpreter/pystderroutstreamredirect.h"
#include "interpreter/private/pystderroutstreamredirect_p.h"
namespace shelllet {
	namespace interpreter {
		namespace py = pybind11;
		Q_GLOBAL_STATIC(PyStdErrOutStreamRedirect, __pystderroutstreamredirect__)
	}
}

shelllet::interpreter::PyStdErrOutStreamRedirect::PyStdErrOutStreamRedirect()
	: PyStdErrOutStreamRedirect(*new PyStdErrOutStreamRedirectPrivate)
{

}

shelllet::interpreter::PyStdErrOutStreamRedirect::~PyStdErrOutStreamRedirect()
{

}

shelllet::common::String shelllet::interpreter::PyStdErrOutStreamRedirect::stdoutString() const
{
	Q_D(const PyStdErrOutStreamRedirect);
	d->stdout_buffer->attr("seek")(0);
	return std::string(py::str(d->stdout_buffer->attr("read")()));
}

shelllet::common::String shelllet::interpreter::PyStdErrOutStreamRedirect::stderrString() const
{

	Q_D(const PyStdErrOutStreamRedirect);
	d->stderr_buffer->attr("seek")(0);
	return std::string(py::str(d->stderr_buffer->attr("read")()));
}

void shelllet::interpreter::PyStdErrOutStreamRedirect::initialize()
{
	Q_D(PyStdErrOutStreamRedirect);
	auto sysm = py::module::import("sys");

	d->stdout_raw = std::make_unique<py::object>(sysm.attr("stdout"));
	d->stderr_raw = std::make_unique<py::object>(sysm.attr("stderr"));

	auto stringio = py::module::import("interpreter").attr("StringIO");
	d->stdout_buffer = std::make_unique<py::object>(stringio);
	d->stderr_buffer = std::make_unique<py::object>(stringio);

	sysm.attr("stdout") = *d->stdout_buffer;
	sysm.attr("stderr") = *d->stderr_buffer;
}

void shelllet::interpreter::PyStdErrOutStreamRedirect::release()
{
	Q_D(PyStdErrOutStreamRedirect);
	auto sysm = py::module::import("sys");
	sysm.attr("stdout") = *d->stdout_raw;
	sysm.attr("stderr") = *d->stderr_raw;
}

shelllet::interpreter::PyStdErrOutStreamRedirect* shelllet::interpreter::PyStdErrOutStreamRedirect::getInstance()
{
	return __pystderroutstreamredirect__;
}

shelllet::interpreter::PyStdErrOutStreamRedirect::PyStdErrOutStreamRedirect(PyStdErrOutStreamRedirectPrivate& d)
	: Object(d, nullptr)
{
	
}
