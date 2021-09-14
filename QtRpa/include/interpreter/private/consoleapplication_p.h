#pragma once

namespace shelllet {
	namespace interpreter {
		class ConsoleApplicationPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(ConsoleApplication)
		public:

			std::unique_ptr<pybind11::scoped_interpreter> guard;
		};
	}
}
