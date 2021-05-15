#pragma once
#include "filesystem"
#include "boost/log/sinks.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/sources/global_logger_storage.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sources/severity_channel_logger.hpp"
#include "custom_output_backend.h"

namespace sinks = boost::log::sinks;
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(__logger, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>);

namespace shelllet {
#define LOG_TRACE(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c, boost::log::trivial::trace)
#define LOG_DEBUG(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c, boost::log::trivial::debug)
#define LOG_INFO(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c,boost::log::trivial::info)
#define LOG_WARN(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c, boost::log::trivial::warning)
#define LOG_ERROR(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c,boost::log::trivial::error)
#define LOG_FATAL(c) BOOST_LOG_CHANNEL_SEV(__logger::get(), c,boost::log::trivial::fatal)

#define THROW_SYSTEM_ERROR(n) throw boost::system::system_error(n, boost::system::detail::system_error_category(), (boost::format("%1% %2%") % __FUNCTION__ % __LINE__).str())

	typedef boost::log::sinks::synchronous_sink<logging::custom_output_backend > sink_custom_t;

	namespace logging {
		BOOST_LOG_ATTRIBUTE_KEYWORD(simple_log_message, "Simple", bool)

			void initialize(boost::log::trivial::severity_level level);

		boost::log::trivial::severity_level level_from_string(const std::string& level);

		void add_custom_sink(const boost::shared_ptr<sink_custom_t>& sink);

		void add_file_sink(const std::filesystem::path& filename);
	}
}