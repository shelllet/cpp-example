#pragma once
#include <qthread.h>
#include <qhostaddress.h>
#include <boost/asio.hpp>
#include "interpreter/inspector.h"
QT_FORWARD_DECLARE_CLASS(QTimerEvent)
namespace shelllet {
	namespace inspect {
		class TcpServer : public QThread
		{
		public:
			TcpServer(Receiver* receiver, const QHostAddress& address, uint16_t port);

		protected:
			void run() override;
		private:
			Receiver* receiver_;
			QHostAddress address_;
			uint16_t port_;
			boost::asio::io_context io_{ 1 };
		};
	}
}
