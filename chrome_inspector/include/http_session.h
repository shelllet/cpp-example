#pragma once
#include <boost/beast/websocket.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include "inspector.h"
namespace shelllet {
	namespace inspect {
		class HttpSession : public std::enable_shared_from_this<HttpSession>
		{
			class Queue
			{
				enum
				{
					limit = 8
				};

				struct Work
				{
					virtual ~Work() = default;
					virtual void operator()() = 0;
				};

				HttpSession& self;
				std::vector<std::unique_ptr<Work>> items;

			public:
				explicit Queue(HttpSession& self)
					: self(self)
				{
					static_assert(limit > 0, "queue limit must be positive");
					items.reserve(limit);
				}

				bool isFull() const
				{
					return items.size() >= limit;
				}

				bool onWrite()
				{
					BOOST_ASSERT(!items.empty());
					auto const was_full = isFull();
					items.erase(items.begin());
					if (!items.empty())
						(*items.front())();
					return was_full;
				}

				template<bool isRequest, class Body, class Fields>
				void operator()(boost::beast::http::message<isRequest, Body, Fields>&& msg)
				{
					struct WorkImpl : Work
					{
						HttpSession& self_;
						boost::beast::http::message<isRequest, Body, Fields> msg_;

						WorkImpl(HttpSession& self, boost::beast::http::message<isRequest, Body, Fields>&& msg)
							: self_(self)
							, msg_(std::move(msg))
						{
						}

						void operator()()
						{
							boost::beast::http::async_write(self_.stream_, msg_, boost::beast::bind_front_handler(&HttpSession::onWrite, self_.shared_from_this(), msg_.need_eof()));
						}
					};

					items.push_back(boost::make_unique<WorkImpl>(self, std::move(msg)));

					if (items.size() == 1)
						(*items.front())();
				}
			};

		public:
			explicit HttpSession(Receiver* receiver, boost::asio::ip::tcp::socket&& socket);

		public:
			void run();
		protected:
			void doRead();

			void onRead(boost::beast::error_code ec, std::size_t bytes_transferred);

			void onWrite(bool close, boost::beast::error_code ec, std::size_t bytes_transferred);

			void doClose();

		private:
			boost::beast::tcp_stream stream_;

			boost::beast::flat_buffer buffer_;
			boost::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;
			Receiver* receiver_;
			Queue queue_;
		};
	}
}