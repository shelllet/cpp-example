#pragma once
#include "object_p.h"
namespace shelllet {
	namespace common {
		class DirectoryIteratorPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(DirectoryIterator)
		public:
			SharedPointer<std::filesystem::directory_iterator> iterator = std::make_shared<std::filesystem::directory_iterator>();
		};
	}
}
