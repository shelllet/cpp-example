#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <qthread.h>
#include "framework.h"
#include "websocket_listener.h"
#include "http_session.h"

namespace shelllet {
}

shelllet::inspect::WebSocketListener::WebSocketListener(shelllet::inspect::Receiver* receiver, boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint endpoint)
	: receiver_(receiver)
	, ioc_(ioc)
	, acceptor_(ioc)
{
	boost::beast::error_code ec;
	acceptor_.open(endpoint.protocol(), ec);
	if (ec)
	{
		LOG_ERROR("inspect") << "# open error: " << ec.message() << std::endl;
		return;
	}

	acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
	if (ec)
	{
		LOG_ERROR("inspect") << "# set option error: " << ec.message() << std::endl;
		return;
	}
	acceptor_.bind(endpoint, ec);
	if (ec)
	{
		LOG_ERROR("inspect") << "# bind error: " << ec.message() << std::endl;
		return;
	}

	acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
	if (ec)
	{
		LOG_ERROR("inspect") << "# set option error: " << ec.message() << std::endl;
	}
}

void shelllet::inspect::WebSocketListener::run()
{
	boost::asio::dispatch(acceptor_.get_executor(), boost::beast::bind_front_handler(&WebSocketListener::doAccept, this->shared_from_this()));
}

void shelllet::inspect::WebSocketListener::doAccept()
{
	acceptor_.async_accept(boost::asio::make_strand(ioc_), boost::beast::bind_front_handler(&WebSocketListener::onAccept, shared_from_this()));
}

void shelllet::inspect::WebSocketListener::onAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket)
{
	if (ec)
	{
		LOG_ERROR("inspect") << "# accept error: " << ec.message() << std::endl;
	}
	else
	{
		std::make_shared<HttpSession>(receiver_, std::move(socket))->run();
	}
	if (QThread::currentThread()->isInterruptionRequested()) {
		ioc_.stop();
		return;
	}
	doAccept();
}