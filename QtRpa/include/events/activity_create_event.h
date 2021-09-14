#pragma once
#include <qobject.h>
#include <qglobalstatic.h>
#include <qtreewidget.h>
#include <qevent.h>
namespace shelllet {
	namespace events {
		class ActivityCreateEvent : public QEvent {
		public:

			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			ActivityCreateEvent(const String& meta);

			String meta() const;
		private:
			String meta_;
		};
	}
}
