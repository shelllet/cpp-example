#pragma once
namespace shelllet {
	namespace common {
		class custom_output_backend : public CustomSink
		{
		public:

			void ReceiveLogMessage(g3::LogMessageMover logEntry) override;

		};
		
		
		class StdOutBackend : public CustomSink
		{
		public:

			void ReceiveLogMessage(g3::LogMessageMover logEntry) override;

		};
	}
}