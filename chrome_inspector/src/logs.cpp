#include "framework.h"
//#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions/predicates/is_debugger_present.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "native/global_implement.h"
#include "logs.h"

namespace shelllet {
	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::debug_output_backend> sink_debug_t;
	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::simple_event_log_backend> event_sink_t;

	BOOST_LOG_ATTRIBUTE_KEYWORD(keyword_channel, "Channel", std::string);

	static auto gl_format = (boost::log::expressions::format("[%1%]<%2%> : <%3%> %4%")
		% boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
		% boost::log::expressions::attr< std::string >("Channel")
		% boost::log::trivial::severity
		% boost::log::expressions::message);
	using namespace global;
}
void shelllet::logs::Logger::initialize(boost::log::trivial::severity_level level)
{
	boost::log::add_common_attributes();

	boost::log::core::get()->set_filter(boost::log::trivial::severity >= level);

	boost::shared_ptr<sink_debug_t> sink(new sink_debug_t());
	sink->set_formatter(gl_format);
	sink->set_filter(boost::log::expressions::is_debugger_present());
	//boost::log::core::get()->set_filter(boost::log::expressions::is_debugger_present());
	boost::log::core::get()->add_sink(sink);

	boost::log::add_console_log(std::clog, boost::log::keywords::format = gl_format);

	std::filesystem::path dir = MyGlobal::GetHomePath() / "shelllet.com/logs";
	std::filesystem::create_directories(dir);
	auto location = dir / (boost::erase_all_copy(MyGlobal::Now(), ":") + ".log");

	boost::log::add_file_log(boost::log::keywords::file_name = location.c_str(),
		boost::log::keywords::rotation_size = 1 * 1024 * 1024,
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		boost::log::keywords::format = gl_format
		//boost::log::keywords::channel = keyword_channel == channel
	);
}

boost::log::trivial::severity_level shelllet::logs::Logger::LevelFromString(const QString& level)
{
	static QMap<QString, boost::log::trivial::severity_level> map = {
		{"trace", boost::log::trivial::trace} ,
		{"debug", boost::log::trivial::debug} ,
		{"info", boost::log::trivial::info} ,
		{"warning", boost::log::trivial::warning} ,
		{"error", boost::log::trivial::error} ,
		{"fatal", boost::log::trivial::fatal}
	};

	if (auto itor = map.constFind(level); itor != map.cend()) {
		return itor.value();
	}
	return boost::log::trivial::fatal;
}