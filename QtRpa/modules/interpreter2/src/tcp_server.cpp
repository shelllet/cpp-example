#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include "interpreter/tcp_server.h"
#include "interpreter/websocket_listener.h"
void shelllet::inspect::TcpServer::run()
{
	std::make_shared<WebSocketListener>(receiver_, io_, boost::asio::ip::tcp::endpoint{ boost::asio::ip::make_address(address_.toString().toStdString()), port_ })->run();
	io_.run();
}

shelllet::inspect::TcpServer::TcpServer(Receiver* receiver, const QHostAddress& address, uint16_t port)
	: receiver_(receiver)
	, address_(address)
	, port_(port)
{
}