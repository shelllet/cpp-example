#include "common.hpp"
#include "v8.hpp"
#include <boost/beast/websocket/stream.hpp>
#include <boost/asio/buffer.hpp>
#include <qurl.h>
#include <qcoreapplication.h>
#include "interpreter/inspector_client.h"

namespace shelllet {
	const int kContextGroupId = 1;
	class DispatchMessagesTask : public v8::Task {
	public:
		explicit DispatchMessagesTask(inspect::InspectorClient* agent, const std::string& message)
			: agent_(agent)
			, message_(message) {
		}

		void Run() override {
			if (agent_ != nullptr) {
				agent_->dispatchProtocolMessage(message_);
			}
		}

	private:
		inspect::InspectorClient* agent_;
		std::string message_;
	};

	extern v8::Global<v8::Context> global_context;
}
shelllet::inspect::InspectorClient::InspectorClient(QObject* receiver, const v8::Local<v8::Context>& context, v8::Platform* platform)
	: isolate_(context->GetIsolate())
	, platform_(platform)
	, receiver_(receiver)
{
	std::string name = "{}";
	inspector_ = v8_inspector::V8Inspector::create(isolate_, this);
	inspector_->contextCreated(v8_inspector::V8ContextInfo(
		context, kContextGroupId, v8_inspector::StringView(reinterpret_cast<const std::uint8_t*>(name.c_str()), name.length())));

	channel_.reset(new InspectorChannel(inspector_.get(), this));
}

void shelllet::inspect::InspectorClient::sendMessageToFrontend(const v8_inspector::StringView& string)
{
	int length = static_cast<int>(string.length());

	v8::Local<v8::String> message = (string.is8Bit()
		? v8::String::NewFromOneByte(
			isolate_,
			reinterpret_cast<const uint8_t*>(string.characters8())/*,
			v8::NewStringType::kNormal, length*/)
		: v8::String::NewFromTwoByte(
			isolate_,
			reinterpret_cast<const uint16_t*>(string.characters16())/*,
			v8::NewStringType::kNormal, length*/))
		.ToLocalChecked();
	std::string resp = ToString({ isolate_, message });
	QCoreApplication::postEvent(receiver_, new MessageOutEvent(resp));
}

void shelllet::inspect::InspectorClient::runMessageLoopOnPause(int contextGroupId)
{
	is_paused_ = true;
	while (is_paused_ && waitForFrontendMessageWhilePaused()) {
		pumpMessageLoop();
	}
	is_paused_ = false;
}

void shelllet::inspect::InspectorClient::quitMessageLoopOnPause()
{
	is_paused_ = false;
}

void shelllet::inspect::InspectorClient::pauseOnNextJavascriptStatement(const std::string& reason)
{
	if (channel_)
		channel_->pauseOnNextJavascriptStatement(reason);
}

double shelllet::inspect::InspectorClient::currentTimeMS()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void shelllet::inspect::InspectorClient::runIfWaitingForDebugger(int contextGroupId)
{
	pauseOnNextJavascriptStatement("Break at bootstrap");
	QCoreApplication::postEvent(receiver_, new ContinueRunEvent);
}
//
//std::unique_ptr<v8_inspector::StringBuffer> shelllet::inspect::InspectorClient::resourceNameToUrl(const v8_inspector::StringView& resourceName)
//{
//	v8::Locker locker(isolate_);
//	v8::HandleScope handle_scope(isolate_);
//	int length = static_cast<int>(resourceName.length());
//	//DCHECK_LT(length, v8::String::kMaxLength);
//	v8::Local<v8::String> message =
//		(resourceName.is8Bit()
//			? v8::String::NewFromOneByte(
//				isolate_,
//				reinterpret_cast<const uint8_t*>(resourceName.characters8()),
//				v8::NewStringType::kNormal, length)
//			: v8::String::NewFromTwoByte(
//				isolate_,
//				reinterpret_cast<const uint16_t*>(resourceName.characters16()),
//				v8::NewStringType::kNormal, length))
//		.ToLocalChecked();
//	std::filesystem::path file = shelllet::ToString({ isolate_, message });
//	//file = "E:\\vision\\debug.js";
//	if (!std::filesystem::is_regular_file(file))
//		return nullptr;
//
//	std::string url = QUrl::fromLocalFile(QString::fromUtf8(file.string().c_str())).url().toStdString();
//	return v8_inspector::StringBuffer::create({ reinterpret_cast<const uint8_t*> (url.c_str()), url.size() });
//}

void shelllet::inspect::InspectorClient::postInspectorMessage(const std::string& message)
{
	//v8::Locker locker(isolate_);
	//v8::Isolate::Scope isolate_scope(isolate_);
	//v8::HandleScope handle_scope(isolate_);
	platform_->GetForegroundTaskRunner(isolate_)->PostTask(std::make_unique<DispatchMessagesTask>(this, message));
	if (is_paused_)
		is_ready_ = true;
	else {
		QCoreApplication::postEvent(receiver_, new PumpMessageLoopEvent);
	}
}

void shelllet::inspect::InspectorClient::consoleAPIMessage(int contextGroupId, v8::Isolate::MessageErrorLevel level, const v8_inspector::StringView& message, const v8_inspector::StringView& url, unsigned lineNumber, unsigned columnNumber, v8_inspector::V8StackTrace*)
{
	throw std::logic_error("The method or operation is not implemented.");
}

v8::Local<v8::Context> shelllet::inspect::InspectorClient::ensureDefaultContextInGroup(int groupId)
{
	return global_context.Get(isolate_);
}

void shelllet::inspect::InspectorClient::dispatchProtocolMessage(const std::string& message)
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	channel_->dispatchProtocolMessage(message);
}

bool shelllet::inspect::InspectorClient::waitForFrontendMessageWhilePaused()
{
	while (!is_ready_) {
		QCoreApplication::processEvents();
	}
	is_ready_ = !is_ready_;
	return true;
}

void shelllet::inspect::InspectorClient::disconnectFrontend()
{
	is_ready_ = true;
	quitMessageLoopOnPause();
}

void shelllet::inspect::InspectorClient::pumpMessageLoop()
{
	v8::Locker locker(isolate_);
	v8::Isolate::Scope isolate_scope(isolate_);
	v8::HandleScope handle_scope(isolate_);
	while (v8::platform::PumpMessageLoop(platform_, isolate_)) {
		QCoreApplication::processEvents();
	}
}