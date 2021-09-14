#pragma once
#include "common/private/object_p.h"
namespace pybind11 {
	class scoped_interpreter;
}
namespace shelllet {
	namespace interpreter {
		class ScriptParserPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(ScriptParser)
		public:
			String code;

			//std::unique_ptr<pybind11::scoped_interpreter> guard;
		};
	}
}
