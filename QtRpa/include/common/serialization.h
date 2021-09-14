#pragma once
#include "common.hpp"

namespace shelllet {
	namespace common {
		class Serialization
		{
		public:
			virtual ~Serialization() {}
			virtual void create() = 0;
			virtual void load(const Path& filename) = 0;
			virtual void save(const Path& filename) = 0;
		};

		class Property {
		public:
			virtual std::filesystem::path relative() = 0;
		};

		static inline const char* endline() {
			return "\n";
		}
	}
}
