#pragma once
#include <qglobalstatic.h>
#include "inspector.h"
#include "inspector_agent.h"
#include "tcp_server.h"

QT_FORWARD_DECLARE_CLASS(QEvent)
namespace shelllet {
	namespace engine {
		class Worker : public inspect::Receiver
		{
		public:
			Worker();
			~Worker();
			void run(const std::string& filename, bool inspect_brk);
		protected:
			virtual void customEvent(QEvent* event) override;
		protected:
			inspect::InspectorVersion requestInspectorVersion() override;
			inspect::InspectorList requestInspectorList() override;
			void finished();
		private:
			std::unique_ptr<InspectorAgent> agent_;
			std::unique_ptr<v8::Platform> platform_;
			inspect::TcpServer* worker_thread_ = nullptr;
		};
	} // namespace engine
}
