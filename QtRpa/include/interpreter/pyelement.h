#pragma once
#include "common.hpp"
#include "element.h"
#include "private/element_p.h"
namespace shelllet {
	namespace interpreter {
		//class PyElementItemPrivate;

		template<typename TBase = Element>
		class PyElement : public TBase {
			//Q_DECLARE_PRIVATE_D(Object::d_ptr, PyElementItem)
		public:
			// PyElementItem(Object*parent = nullptr);
			PyElement(Element* element, Object* parent = nullptr)
				: TBase(element, parent) {}
			//   static void embedded(py::module_& m);
			using TBase::TBase;
		protected:
			/*PyElementItem(PyElementItemPrivate& d, ElementItem* item, Object* parent = nullptr)
				: TBase(d, item)
			{

			}*/

			//shelllet::interpreter::PyElementItem::PyElementItem( ElementItem* element, Object* parent /*= nullptr*/)
			//    :PyElementItem(*new PyElementItemPrivate, element, parent)
			//{
			//
			//}

			CompositeProperty* prop()override
			{
				PYBIND11_OVERRIDE_NAME(CompositeProperty*, TBase, "get_prop", prop);
			}
		public:
			static void importModule() {
				py::module::import("interpreter").attr(QUOTED(Element));

			}
			static void  embedded(py::module_& m)
			{
				py::class_<Element, QGraphicsWidget,  PyElement<>>(m, "Element")
					.def(py::init<Element*>())
					//.def("get_prop", &TBase::prop)
					;


				/*py::class_<WrapperElement >(m, "WrapperElement")

					;*/
			}

		};
	}
}
