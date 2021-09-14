#pragma once
#include "element_p.h"

namespace shelllet {
	namespace interpreter {
		class DropArea;
		class SimpleTextItem;
		class Container;
		class ContainerPrivate : public ElementPrivate {
			Q_DECLARE_PUBLIC(Container)
		public:
			SimpleTextItem* description = nullptr;
		};
	}
}