#pragma once
#include <v8-inspector.h>
namespace shelllet {
	namespace inspect {
		class InspectorClient;
		class InspectorChannel final : public v8_inspector::V8Inspector::Channel {
		public:
			explicit InspectorChannel(v8_inspector::V8Inspector* inspector, InspectorClient* c);
			~InspectorChannel() = default;
		public:
			void pauseOnNextJavascriptStatement(const std::string& reason);
			void dispatchProtocolMessage(const std::string& message);
		private:
			void sendResponse(int call_id, std::unique_ptr<v8_inspector::StringBuffer> message) override;
			void sendNotification(std::unique_ptr<v8_inspector::StringBuffer> message) override;
			void flushProtocolNotifications() override {}
		private:
			InspectorClient* client_;
			std::unique_ptr<v8_inspector::V8InspectorSession> session_;
		};
	}
}