#pragma once
#include <qobject.h>
#include <qevent.h>
namespace shelllet {
	namespace events {
		class AdjustSizeEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			AdjustSizeEvent();
		};
	}
}
