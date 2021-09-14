#include <boost/asio/dispatch.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/asio/strand.hpp>
#include <qcoreapplication.h>
#include <qeventloop.h>
#include <qthreadpool.h>
#include "common.hpp"
#include "interpreter/websocket_session.h"
namespace shelllet {
	std::mutex mutex;
}
shelllet::inspect::WebsocketSession::WebsocketSession(shelllet::inspect::Receiver* receiver, boost::asio::ip::tcp::socket&& socket)
	: receiver_(receiver)
	, ws_(std::move(socket))
{
	receiver_->callback = [this](auto& message) {
		std::lock_guard<std::mutex> lock_guard(mutex);
		messages_.emplace_front(message);
	};
}

shelllet::inspect::WebsocketSession::~WebsocketSession()
{
	receiver_->callback = {};
	LOG_TRACE("inspect") << "# ~websocket_session." << std::endl;
}

//void shelllet::inspect::WebsocketSession::customEvent(QEvent* event)
//{
//	if (auto* e = dynamic_cast<ReadEvent*>(event)) {
//		doRead();
//	}
//	else if (auto* e = dynamic_cast<WriteEvent*>(event)) {
//		doWrite(messages_.back());
//		messages_.pop_back();
//	}
//}

void shelllet::inspect::WebsocketSession::onAccept(boost::beast::error_code ec)
{
	if (ec) {
		LOG_ERROR("inspect") << "# accept error: " << ec.message() << std::endl;
		return;
	}

	class Runnable : public QRunnable {
	public:
		Runnable(const std::shared_ptr<WebsocketSession>& session) :self_(session) {
		}
		void run() override {
			self_->thread_ = QThread::currentThread();
			while (true) {
				if (QThread::currentThread()->isInterruptionRequested()) {
					break;
				}
				if (self_->messages_.empty()) {
					self_->doRead();
				}
				else {
					std::lock_guard<std::mutex> lock_guard(mutex);
					self_->doWrite(self_->messages_.back());
					self_->messages_.pop_back();
				}
				QCoreApplication::processEvents();
				std::this_thread::sleep_for(10ms);
			}
			QCoreApplication::postEvent(self_->receiver_, new DisconnectEvent);

			LOG_INFO("inspect") << "# message runnable exit." << std::endl;
		}
	private:
		std::shared_ptr<WebsocketSession> self_;
	};
	QThreadPool::globalInstance()->start(new Runnable(shared_from_this()));
}

void shelllet::inspect::WebsocketSession::doRead()
{
	if (is_read_ok_) {
		is_read_ok_ = false;
		ws_.async_read(buffer_, boost::beast::bind_front_handler(&WebsocketSession::onRead, shared_from_this()));
	}
}

void shelllet::inspect::WebsocketSession::onRead(boost::beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec == boost::beast::websocket::error::closed) {
		if (thread_) {
			thread_->requestInterruption();
		}
		return;
	}

	if (ec) {
		LOG_ERROR("inspect") << "# read error: " << ec.message() << std::endl;
		if (thread_) {
			thread_->requestInterruption();
		}
		return;
	}

	std::string message = boost::beast::buffers_to_string(buffer_.cdata());
	QCoreApplication::postEvent(receiver_, new MessageInEvent(message));

	is_read_ok_ = true;
	buffer_.consume(buffer_.size());
	LOG_TRACE("inspct") << "# incoming: " << message << std::endl;
}
void shelllet::inspect::WebsocketSession::doWrite(const std::string& message)
{
	ws_.text(true);

	boost::beast::error_code ec;

	std::size_t size = ws_.write(boost::asio::buffer(message), ec);

	if (ec) {
		LOG_ERROR("inspect") << "# write error: " << ec.message() << std::endl;
		if (thread_) {
			thread_->requestInterruption();
		}
		return;
	}
	assert(size == message.length());

	LOG_TRACE("inspct") << "# outgoing: " << message << std::endl;
}