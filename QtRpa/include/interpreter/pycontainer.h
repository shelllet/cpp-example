#pragma once
#include "common.hpp"
#include "pyelement.h"
#include "private/containeritem_p.h"
#include "containeritem.h"
namespace shelllet {
	namespace interpreter {
		//class PyContainerPrivate;
		// template <typen
		template<typename ContainerBase = Container>
		class PyContainer : public PyElement<ContainerBase> {
			//Q_DECLARE_PRIVATE_D(Object::d_ptr, PyContainer)
		public:
		/*	PyContainer(ElementItem* parentItem, Object* parent = nullptr)
				:PyElementItem<>(*new ContainerPrivate, parentItem, parent)
			{

			}*/
			using PyElement<ContainerBase>::PyElement;

			//static void embedded(py::module_& m);

			
		protected:
			/*PyContainer(PyContainerPrivate& d, ElementItem* parentItem = nullptr, Object* parent = nullptr)
				: ContainerBase(d, parentItem, parent){

			}*/

			//shelllet::interpreter::PyContainer::PyContainer(ElementItem* parentItem, Object* parent /*= nullptr*/)
			//    :PyContainer(*new PyContainerPrivate, parentItem, parent)
			//{
			//
			//}
		public:
			static void embedded(py::module_& m)
			{
				py::class_<Container, Element, PyContainer<>>(m, "Container")
					.def(py::init<Element*>())
					
					//	.def(QUOTED(getInput), &CompositeProperty::getInput)
						//.def(QUOTED(getOutput), &CompositeProperty::getOutput)
						//.def(QUOTED(getNode), &CompositeProperty::getNode)
					;
			}

		};
	}
}
