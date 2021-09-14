#pragma once
#include <QEvent>

namespace shelllet {
	namespace events {
		class MessageOutputEvent : public QEvent {
		public:

			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			MessageOutputEvent(const std::string& msg);

			std::string message() const;
		private:
			std::string message_;
		};
	}
}
