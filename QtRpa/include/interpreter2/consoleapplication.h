#pragma once
#include <qglobalstatic.h>
#include "inspector.h"
#include "common.hpp"

QT_FORWARD_DECLARE_CLASS(QEvent)
namespace shelllet {
	namespace interpreter {
		class ConsoleApplicationPrivate;
		class ConsoleApplication : public inspect::Receiver, public Runnable
		{
			Q_DECLARE_PRIVATE_D(p_, ConsoleApplication)
		public:
			ConsoleApplication();
			~ConsoleApplication();
			void run(QEvent* event) override;
		protected:
			virtual void customEvent(QEvent* event) override;
		protected:
			inspect::InspectorVersion requestInspectorVersion() override;
			inspect::InspectorList requestInspectorList() override;
			void finished();
		private:
			ConsoleApplicationPrivate* p_ = nullptr;
		};
	} // namespace engine
}
