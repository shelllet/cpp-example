#pragma once
#include "object_p.h"
namespace shelllet {
	namespace common {

		class PathPrivate : public ObjectPrivate {

		public:
			std::filesystem::path path;
		};
	}
}