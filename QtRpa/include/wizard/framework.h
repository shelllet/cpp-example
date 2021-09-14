#pragma once

namespace shelllet {
	namespace wizard {
		class ResponseHandler {
		public:
			enum class Exit {
				Create,
				Open,
				FromGit,
			};

			virtual void finshed(Exit exit) = 0;
		};

	}
}
