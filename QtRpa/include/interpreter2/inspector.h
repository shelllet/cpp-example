#pragma once
#include <qevent.h>

namespace shelllet {
	namespace inspect {
		struct InspectorVersion {
			std::string version;
			std::string browser;
		};
		struct InspectorList {
			std::string description;
			std::string type;
			std::string title;
			std::string url;
			std::string address;
			uint16_t port;
		};

		class Receiver : public QObject {
		public:
			void dispatchInspectorMessage(const std::string& message) { if (callback) { callback(message); } }
			virtual InspectorVersion requestInspectorVersion() = 0;
			virtual InspectorList requestInspectorList() = 0;
			std::function<void(const std::string&)> callback;
		};

		class MessageInEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			MessageInEvent(const std::string& message) : QEvent(Type), message(message) {}
			std::string message;
		};
		class MessageOutEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			MessageOutEvent(const std::string& message) : QEvent(Type), message(message) {}
			std::string message;
		};
		class PumpMessageLoopEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			PumpMessageLoopEvent() : QEvent(Type) {}
		};
		class ContinueRunEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			ContinueRunEvent() : QEvent(Type) {}
		};

		class DisconnectEvent : public QEvent {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			DisconnectEvent() : QEvent(Type) {}
		};
	}
}