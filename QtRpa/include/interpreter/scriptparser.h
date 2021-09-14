#pragma once
#include "common.hpp"
namespace shelllet {
	namespace interpreter {
		class ScriptParserPrivate;
		class ScriptParser : public Object {
			Q_DECLARE_PRIVATE(ScriptParser)
		public:
			ScriptParser();
			void loadFile(const Path& path);
			String parseImports() const;

			String parseCode(std::int32_t hash);

			void exec(const Path& path, QObject* obj, const QMetaObject* meta);

			static ScriptParser* getInstance();
		};
	}
}
