#pragma once
#include "common/private/object_p.h"
#include "qgraphicslinearlayout.h"
namespace shelllet {
	namespace interpreter {
		class Component;

		class ComponentPrivate : public ObjectPrivate {
		public:
			QGraphicsLinearLayout* layout = nullptr;

			Component* next;
			Component* previous;
		};
	}
}