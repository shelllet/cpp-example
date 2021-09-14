#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <chrono>
#include <qeventloop.h>
#include <include/libplatform/libplatform.h>
#include "interpreter/inspector_channel.h"
#include "interpreter/inspector.h"

namespace shelllet {
	namespace inspect {
		class InspectorClient : public v8_inspector::V8InspectorClient {
		public:
			InspectorClient(QObject* receiver, const v8::Local<v8::Context>& context, v8::Platform* platform);

		protected:
			void runMessageLoopOnPause(int contextGroupId) override;

			void quitMessageLoopOnPause() override;

			void pauseOnNextJavascriptStatement(const std::string& reason);

			double currentTimeMS() override;

			void runIfWaitingForDebugger(int contextGroupId) override;

			//	std::unique_ptr<v8_inspector::StringBuffer> resourceNameToUrl(const v8_inspector::StringView& resourceName) override;

			void consoleAPIMessage(int contextGroupId, v8::Isolate::MessageErrorLevel level, const v8_inspector::StringView& message, const v8_inspector::StringView& url, unsigned lineNumber, unsigned columnNumber, v8_inspector::V8StackTrace*) override;

		private:

			v8::Local<v8::Context> ensureDefaultContextInGroup(int groupId) override;
		public:
			void postInspectorMessage(const std::string& message);
			void sendMessageToFrontend(const v8_inspector::StringView& string);
			void dispatchProtocolMessage(const std::string& message);
			bool waitForFrontendMessageWhilePaused();
			void disconnectFrontend();
			void pumpMessageLoop();

		private:
			std::unique_ptr<v8_inspector::V8Inspector> inspector_;
			std::unique_ptr<InspectorChannel> channel_;
			bool is_paused_ = false;
			bool is_ready_ = false;
			v8::Isolate* isolate_;
			v8::Platform* platform_;
			QObject* receiver_;
		};
	}
}