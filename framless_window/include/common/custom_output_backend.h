#pragma once

namespace shelllet {
	namespace logging {
		class custom_output_backend : public boost::log::sinks::basic_formatted_sink_backend<char, boost::log::sinks::synchronized_feeding>
		{
		public:
			virtual void consume(boost::log::record_view const& rec, string_type const& command_line);
		};
	}
}