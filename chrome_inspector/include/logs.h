#pragma once
#include "framework.h"
#include <boost/serialization/singleton.hpp>
#include "qloggingcategory.h"
#include "qglobalstatic.h"
namespace shelllet {
	namespace logs {
		Q_DECLARE_LOGGING_CATEGORY(shelllet_engine)
			class Logger {
			public:
				void initialize(boost::log::trivial::severity_level level);

				static boost::log::trivial::severity_level LevelFromString(const QString& level);
		};

		Q_GLOBAL_STATIC(Logger, logger)
	}
}