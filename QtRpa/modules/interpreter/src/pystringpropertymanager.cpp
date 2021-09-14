#include "interpreter/framework.h"
#include "property.hpp"
#include "interpreter/pystringpropertymanager.h"
#include "interpreter/private/pystringpropertymanager_p.h"

namespace shelllet {

	namespace interpreter {
		class StringPropertyManager_valueChanged {
		public:
			StringPropertyManager_valueChanged(StringPropertyManager& self) : self(self) {}
			void connect(py::object func) {
				QObject::connect(&self, &StringPropertyManager::valueChanged, [func](auto...args) {
					auto second = std::get<1>(std::forward_as_tuple(args...));
					func(second.toStdString()); });
			}
			StringPropertyManager& self;
		};
	}
}
shelllet::interpreter::PyStringPropertyManager::PyStringPropertyManager(Object* parent /*= nullptr*/)
	:PyStringPropertyManager(*new PyStringPropertyManagerPrivate, parent)
{

}

void shelllet::interpreter::PyStringPropertyManager::embedded(py::module_& m)
{
	py::class_<StringPropertyManager_valueChanged>(m, QUOTED(StringPropertyManager_valueChanged))
		.def("connect", &StringPropertyManager_valueChanged::connect)
		;

	py::class_<StringPropertyManager, UniquePointer<StringPropertyManager, py::nodelete>>(m, "StringPropertyManager")
		.def(py::init<>())
		.def("add_property", [](StringPropertyManager& self, const std::string& name) {	return self.addProperty(name); })
		.def("set_value", [](StringPropertyManager& self, PropertySheet* property, const std::string& value) { self.setValue(property, value); })
		.def_property_readonly("value_changed", [](StringPropertyManager& self) {
		return StringPropertyManager_valueChanged(self); 
	})
		//.def("connect", [](StringPropertyManager& self, py::object func) {
		//QObject::connect(&self, &StringPropertyManager::valueChanged, [func](auto...args) {
		//	auto second = std::get<1>(std::forward_as_tuple(args...));
		//	func(second.toStdString()); }); })
		.def_static("create", []() { return new StringPropertyManager; })
		//.def("connect", &StringPropertyManager::connect)
		;
}

void shelllet::interpreter::PyStringPropertyManager::importModule()
{
	py::module::import("interpreter").attr(QUOTED(StringPropertyManager));
	py::module::import("interpreter").attr(QUOTED(StringPropertyManager_valueChanged));
}

shelllet::interpreter::PyStringPropertyManager::PyStringPropertyManager(PyStringPropertyManagerPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
