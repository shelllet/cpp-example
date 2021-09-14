#pragma once
#include "common/private/mimedata_p.h"

namespace shelllet {
	namespace interpreter {

		class ElementMimeDataPrivate : public MimeDataPrivate {
		public:
			Element* item = nullptr;
		};

	}
}