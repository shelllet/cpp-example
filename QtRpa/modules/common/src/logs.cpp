#include "common/logs.h"
#include "common/private/object_p.h"
#include <g3log/logworker.hpp>
#include "common/custom_output_backend.h"

//#include "boost/log/support/date_time.hpp"
//#include "boost/log/utility/setup/common_attributes.hpp"
//#include "boost/log/expressions/predicates/is_debugger_present.hpp"
//#include "boost/log/utility/setup/console.hpp"
//#include "boost/log/utility/setup/file.hpp"
//
//namespace shelllet {
//	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::debug_output_backend> sink_debug_t;
//
//	namespace logging {
//		static inline auto LOG_FORMAT_STREAM = (boost::log::expressions::format(L"[%1%]<%2%> : <%3%> %4%")
//			% boost::log::expressions::format_date_time<boost::posix_time::ptime>(L"TimeStamp", "%Y-%m-%d %H:%M:%S")
//			% boost::log::expressions::attr< std::wstring >(L"Channel")
//			% severity
//			% boost::log::expressions::message);
//
//		
//		BOOST_LOG_ATTRIBUTE_KEYWORD(keyword_channel, L"Channel", std::string);
//	}
//}
//void shelllet::logging::add_custom_sink(const boost::shared_ptr<sink_custom_t>& sink)
//{
//	//boost::shared_ptr<sink_broadcast_t> sink(new sink_broadcast_t());
//
//	sink->set_formatter(boost::log::expressions::stream << boost::log::expressions::if_(boost::log::expressions::has_attr(simple_log_message) && boost::log::expressions::attr<bool>("Simple"))
//		[
//			boost::log::expressions::stream << boost::log::expressions::message
//		]
//	.else_
//		[
//			LOG_FORMAT_STREAM
//		]);
//
//	boost::log::core::get()->add_sink(sink);
//	// LOG_INFO("") << boost::log::add_value(simple_log_message, true) << "simple message." << std::endl;
//}
//
//
//void shelllet::logging::add_file_sink(const std::filesystem::path& filename)
//{
//	boost::log::add_file_log(boost::log::keywords::file_name = filename.c_str(),
//		boost::log::keywords::rotation_size = 1 * 1024 * 1024,
//		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
//		boost::log::keywords::format = LOG_FORMAT_STREAM
//		//boost::log::keywords::channel = keyword_channel == channel
//	);
//}
//
//void shelllet::logging::initialize(boost::log::trivial::severity_level level)
//{
//	boost::log::add_common_attributes();
//
//	{
//		boost::shared_ptr<sink_debug_t> sink = boost::make_shared<sink_debug_t>();
//		sink->set_formatter(LOG_FORMAT_STREAM);
//		boost::log::core::get()->add_sink(sink);
//	}
//
//
//	boost::log::add_console_log(std::clog, boost::log::keywords::format = LOG_FORMAT_STREAM);
//	boost::log::core::get()->set_filter(boost::log::trivial::severity >= level);
//}
//
//boost::log::trivial::severity_level shelllet::logging::level_from_string(const std::string& level)
//{
//	static std::map<std::string, boost::log::trivial::severity_level> map = {
//	{"trace", boost::log::trivial::trace} ,
//	{"debug", boost::log::trivial::debug} ,
//	{"info", boost::log::trivial::info} ,
//	{"warning", boost::log::trivial::warning} ,
//	{"error", boost::log::trivial::error} ,
//	{"fatal", boost::log::trivial::fatal}
//	};
//
//	if (auto itor = map.find(level); itor != map.cend()) {
//		return itor->second;
//	}
//	return boost::log::trivial::fatal;
//}
#include "qglobalstatic.h"
#include "qcoreapplication.h"
namespace shelllet {

	namespace common {

		class LoggerPrivate : public ObjectPrivate {
		public:
			std::unique_ptr<g3::LogWorker> worker = g3::LogWorker::createLogWorker();
		};

		Q_GLOBAL_STATIC(Logger, __logger__)
	}
}
shelllet::common::Logger::Logger()
	: Object(*new LoggerPrivate, nullptr)
{


	//std::future<std::string> log_file_name = handle->call(&g3::FileSink::fileName);

	//auto changeFormatting = handle->call(&g3::FileSink::overrideLogDetails, g3::LogMessage::FullLogDetailsToString);
	//const std::string newHeader = "\t\tLOG format: [YYYY/MM/DD hh:mm:ss uuu* LEVEL THREAD_ID FILE->FUNCTION:LINE] message\n\t\t(uuu*: microseconds fractions of the seconds value)\n\n";
	//// example of ovrriding the default formatting of header
	//auto changeHeader = handle->call(&g3::FileSink::overrideLogHeader, newHeader);

	//changeFormatting.wait();
	//changeHeader.wait();
}

shelllet::common::Logger* shelllet::common::Logger::getInstance()
{
	return __logger__;
}

void shelllet::common::Logger::addFileSink(severity_level level, const std::filesystem::path& folder)
{
	Q_D(Logger);
	auto handle = d->worker->addDefaultLogger(QCoreApplication::applicationName().toStdString(), folder.string());

}

severity_level shelllet::common::Logger::levelFromString(const std::string& level)
{
	static std::map<std::string, severity_level> map = {

{"debug", debug} ,
{"info", info} ,
{"warning", warning} ,
{"error", error}
	};

	if (auto itor = map.find(level); itor != map.cend()) {
		return itor->second;
	}
	return debug;
}

void shelllet::common::Logger::initialize()
{
	Q_D(Logger);
	addCustomSink(debug, std::make_unique<custom_output_backend>());
	addCustomSink(debug, std::make_unique<StdOutBackend>());
	g3::initializeLogging(d->worker.get());
}

void shelllet::common::Logger::addCustomSink(severity_level level,  std::unique_ptr<CustomSink> sink)
{
	Q_D(Logger);
	d->worker->addSink(std::move(sink), &CustomSink::ReceiveLogMessage);
}
