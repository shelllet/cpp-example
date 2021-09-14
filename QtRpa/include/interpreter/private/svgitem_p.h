#pragma once
#include "common/private/object_p.h"

namespace shelllet {
	namespace interpreter {
		class SvgItemPrivate : public ObjectPrivate {
		public:
			QSize size;
		};

	}
}