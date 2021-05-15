#pragma once
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/empty_body.hpp>
#include "inspector.h"

namespace shelllet {
	namespace inspect {
		class WebSocketListener : public std::enable_shared_from_this<WebSocketListener>
		{
		public:
			WebSocketListener(Receiver* receiver, boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint endpoint);

		public:
			void run();
		private:
			void doAccept();

			void onAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);

		private:
			boost::asio::io_context& ioc_;
			boost::asio::ip::tcp::acceptor acceptor_;

			Receiver* receiver_;
		};
	}
}