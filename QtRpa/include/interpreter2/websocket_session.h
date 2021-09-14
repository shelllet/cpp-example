#pragma once
#include <qrunnable.h>
#include <qevent.h>
#include <boost/beast/websocket.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include "interpreter/inspector.h"

namespace shelllet {
	namespace inspect {
		class WebsocketSession : public std::enable_shared_from_this<WebsocketSession>
		{
		public:
			explicit WebsocketSession(shelllet::inspect::Receiver* receiver, boost::asio::ip::tcp::socket&& socket);

			~WebsocketSession();
		public:
			template<class Body, class Allocator>
			void doAccept(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> req)
			{
				ws_.async_accept(req, boost::beast::bind_front_handler(&WebsocketSession::onAccept, shared_from_this()));
			}

			void onAccept(boost::beast::error_code ec);

			void doRead();

			void onRead(boost::beast::error_code ec, std::size_t bytes_transferred);

			void doWrite(const std::string& message);
		private:
			friend class Runnable;
			boost::beast::websocket::stream<boost::beast::tcp_stream> ws_;
			boost::beast::flat_buffer buffer_;
			Receiver* receiver_;
			bool is_read_ok_ = true;
			std::list<std::string> messages_;
			QThread* thread_ = nullptr;
		};
	}
}