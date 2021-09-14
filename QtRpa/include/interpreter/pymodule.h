#pragma once

namespace shelllet {
	namespace interpreter {
		class PyModulePrivate;
		class PyModule : public Object {
			Q_DECLARE_PRIVATE(PyModule)
		public:
			PyModule();
			void importModules();
			void initLibPath();
			static PyModule* getInstance();
		};
	}
}
