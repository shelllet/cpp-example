#pragma once
#include "filesystem"
#include "object.h"

namespace std {
	template<typename T>
	using result_of = invoke_result<T>;
}
#include <g3log/g3log.hpp>

enum severity_level
{
	debug,
	info,
	warning,
	error
};

namespace shelllet {
	namespace common {

		const LEVELS ERROR_ALIAS{ WARNING.value + 1, {"ERROR"} };

		//#define LOG_TRACE(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c, boost::log::trivial::trace/*)
#define LOG_DEBUG(c) LOG(G3LOG_DEBUG) << "#" << c << ": "
#define LOG_INFO(c) LOG(INFO) << "#" << c << ": "
#define LOG_WARNING(c) LOG(WARNING) << "#" << c << ": "
#define LOG_ERROR(c) LOG(ERROR_ALIAS) << "#" << c << ": "
#define LOG_FATAL(c) LOG(FATAL) << "#" << c << ": "
		struct CustomSink {
			virtual void ReceiveLogMessage(g3::LogMessageMover logEntry) {	}
			int level;
		};

		class LoggerPrivate;
		class Logger final : public Object {
			Q_DECLARE_PRIVATE(Logger)
		public:
			Logger();

			static Logger* getInstance();

			void addFileSink(severity_level level, const std::filesystem::path& folder);

			void addCustomSink(severity_level level, std::unique_ptr< CustomSink> sink);

			static severity_level levelFromString(const std::string& level);

			void initialize();
		};
	}
}

