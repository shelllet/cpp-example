#pragma once
#include <qobject.h>
#include <qglobalstatic.h>
#include <qevent.h>
namespace shelllet {
	namespace events {
		class ShowEvent : public QEvent {
		public:

			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			ShowEvent();

		private:
		};
	}
}
