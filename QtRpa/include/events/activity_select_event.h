#pragma once
#include <qobject.h>
#include <qglobalstatic.h>
#include <qgraphicsitem.h>
#include <qevent.h>
namespace shelllet {
	namespace interpreter {
		class CompositeProperty;
	}
	namespace events {
		class ActivitySelectEvent : public QEvent {
		public:

			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			ActivitySelectEvent(interpreter::CompositeProperty* prop);
			interpreter::CompositeProperty* getProp() const;
		private:
			interpreter::CompositeProperty* prop_;
		};
	}
}
