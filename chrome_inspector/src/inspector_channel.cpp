#include "inspector_channel.h"
#include "inspector_client.h"
void shelllet::inspect::InspectorChannel::sendResponse(int call_id, std::unique_ptr<v8_inspector::StringBuffer> message)
{
	boost::ignore_unused(call_id);
	client_->sendMessageToFrontend(message->string());
}

void shelllet::inspect::InspectorChannel::sendNotification(std::unique_ptr<v8_inspector::StringBuffer> message)
{
	client_->sendMessageToFrontend(message->string());
}

void shelllet::inspect::InspectorChannel::pauseOnNextJavascriptStatement(const std::string& reason)
{
	auto buffer = v8_inspector::StringBuffer::create({ reinterpret_cast<const std::uint8_t*>(reason.c_str()), reason.length() });
	session_->schedulePauseOnNextStatement(buffer->string(), buffer->string());
}

void shelllet::inspect::InspectorChannel::dispatchProtocolMessage(const std::string& message)
{
	session_->dispatchProtocolMessage({ reinterpret_cast<const uint8_t*>(message.c_str()), message.length() });
}

shelllet::inspect::InspectorChannel::InspectorChannel(v8_inspector::V8Inspector* inspector, InspectorClient* c) :client_(c)
{
	std::string debugger = "{}";
	session_ = inspector->connect(1, this, v8_inspector::StringView(reinterpret_cast<const std::uint8_t*>(debugger.c_str()), debugger.length()));
}