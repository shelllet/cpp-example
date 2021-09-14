#include "pybind11/pybind11.h"
#include "common.hpp"
#include "interpreter/mybase.h"
#include "common/private/object_p.h"
#include "interpreter/private/mybase_p.h"

shelllet::interpreter::Mybase::Mybase()
	//:Object(*new MybasePrivate, nullptr)
{
};

std::string shelllet::interpreter::Mybase::name()
{
	return "";
}



PYBIND11_MODULE(example, m) {

}