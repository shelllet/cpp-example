#pragma once

namespace shelllet {
	namespace interpreter {
		class StringIO {
		public:
			StringIO() = default;
			static void write(const std::string& message);


			static void embedded(py::module_& m);

		};
	}
}
