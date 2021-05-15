#include <boost/asio/dispatch.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <qcoreapplication.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qthreadpool.h>
#include <qjsonarray.h>
#include <quuid.h>
#include "framework.h"
#include "http_session.h"
#include "websocket_session.h"

namespace shelllet {
	// https://github.com/boostorg/beast/blob/develop/example/advanced/server/advanced_server.cpp
	static std::string id = QUuid::createUuid().toString(QUuid::WithoutBraces).toStdString();

	std::string FrontendUrl(const std::string& address, uint16_t port) {
		std::ostringstream frontendUrl;
		frontendUrl << "devtools://devtools/bundled/js_app.html?experiments=true&v8only=true&ws=";
		frontendUrl << address << ":" << port << "/" << id;
		return frontendUrl.str();
	}
	std::string HandleReqVersion(inspect::Receiver* receiver)
	{
		// https://chromedevtools.github.io/devtools-protocol/
		auto version = receiver->requestInspectorVersion();

		QJsonObject json = { {"Browser", QString::fromStdString(version.browser)}, {"Protocol-Version", QString::fromStdString(version.version)} };
		QJsonDocument document(json);
		return document.toJson(QJsonDocument::Indented).constData();
	}

	std::string HandleReqList(inspect::Receiver* receiver)
	{
		// https://chromedevtools.github.io/devtools-protocol/

		auto info = receiver->requestInspectorList();

		std::ostringstream ws;
		ws << "ws://" << info.address << ":" << info.port << "/" << id;

		std::string  frontend_url = FrontendUrl(info.address, info.port);

		QJsonObject obj = { {"id", QString::fromStdString(id) }, {"description",  QString::fromStdString(info.description)},
		{"type",  QString::fromStdString(info.type)},
		{"title", QString::fromStdString(info.title)},
		{"url", QString::fromStdString(info.url)},
		{"webSocketDebuggerUrl", QString::fromStdString(ws.str())},
		{"devtoolsFrontendUrl", QString::fromStdString(frontend_url)},
		};
		QJsonArray array = { obj };
		QJsonDocument document(array);

		return document.toJson(QJsonDocument::Indented).constData();
	}

	template<class Body, class Allocator, class Send>
	void HandleRequest(inspect::Receiver* receiver, boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& req, Send&& send) {
		static std::map<boost::beast::string_view, std::function<std::string(inspect::Receiver*)>> handlers = {
							{"/json/version", HandleReqVersion },
							{"/json", HandleReqList },
							{"/json/list", HandleReqList }
		};

		auto const bad_request = [&req](boost::beast::string_view why)
		{
			boost::beast::http::response<boost::beast::http::string_body> res{ boost::beast::http::status::bad_request, req.version() };
			res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
			res.set(boost::beast::http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = std::string(why);
			res.prepare_payload();
			return res;
		};

		if (!handlers.contains(req.target())) {
			LOG_WARN("inspect") << "# target: `" << req.target() << "` not supported." << std::endl;
			return send(bad_request("Illegal request-target"));
		}
		boost::beast::http::dynamic_body::value_type body;
		boost::beast::ostream(body) << handlers[req.target()](receiver).c_str();
		auto const size = body.size();

		boost::beast::http::response<boost::beast::http::dynamic_body> res{
		std::piecewise_construct,
		std::make_tuple(std::move(body)),
		std::make_tuple(boost::beast::http::status::ok, req.version()) };
		res.set(boost::beast::http::field::content_type, "application/json; charset=UTF-8");
		res.set(boost::beast::http::field::cache_control, "no-cache");
		res.content_length(size);
		res.keep_alive(req.keep_alive());
		return send(std::move(res));
	}
}
shelllet::inspect::HttpSession::HttpSession(shelllet::inspect::Receiver* receiver, boost::asio::ip::tcp::socket&& socket)
	: receiver_(receiver)
	, stream_(std::move(socket))
	, queue_(*this)
{
}

void shelllet::inspect::HttpSession::run()
{
	boost::asio::dispatch(stream_.get_executor(), boost::beast::bind_front_handler(&HttpSession::doRead, this->shared_from_this()));
}

void shelllet::inspect::HttpSession::doRead()
{
	parser_.emplace();

	boost::beast::http::async_read(stream_, buffer_, *parser_, boost::beast::bind_front_handler(&HttpSession::onRead, shared_from_this()));
}

void shelllet::inspect::HttpSession::onRead(boost::beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec == boost::beast::http::error::end_of_stream)
		return doClose();

	if (ec) {
		LOG_ERROR("inspect") << "# read error " << ec.message() << std::endl;
		return;
	}
	if (boost::beast::websocket::is_upgrade(parser_->get()))
	{
		LOG_TRACE("inspect") << "# websocket created." << std::endl;
		std::make_shared<WebsocketSession>(receiver_, stream_.release_socket())->doAccept(parser_->release());
		return;
	}

	HandleRequest(receiver_, parser_->release(), queue_);

	if (!queue_.isFull())
		doRead();
}

void shelllet::inspect::HttpSession::onWrite(bool close, boost::beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec) {
		LOG_ERROR("inspect") << "# read error " << ec.message() << std::endl;
		return;
	}

	if (close)
	{
		return doClose();
	}
	if (queue_.onWrite())
	{
		doRead();
	}
}

void shelllet::inspect::HttpSession::doClose()
{
	boost::system::error_code ec;
	stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
}