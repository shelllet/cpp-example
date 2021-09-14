#pragma once
#include "common.hpp"
namespace shelllet {
	class Resource {
	public:
		virtual ~Resource() {};
		virtual void cleanup() = 0;
		class Deleter {
		public:
			void operator()(Resource* res) {
				res->cleanup();
				delete res;
				LOG_DEBUG("resource") << "# free." << std::endl;
			}
		};
	};
}