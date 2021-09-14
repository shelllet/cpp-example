#pragma once
#include "filesystem"
#include <qobject.h>
#include <qglobalstatic.h>
#include <qevent.h>
#include <boost/serialization/singleton.hpp>
#include "common.hpp"

namespace shelllet {
	namespace	events {
		class Event : public QEvent {
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
		public:
			Event(Runnable* p) :QEvent(Type), p_(p) {}
			Runnable* ptr() { return p_; }
		private:
			Runnable* p_ = nullptr;
		};
		class ConsoleEvent : public Event {
		public:

			ConsoleEvent(const Path& file, bool inspect_brk)
				: Event(0)
				, file_(file)
				, inspect_brk_(inspect_brk) {}

			Path filename() const { return file_; }
			bool inspectBrk() const { return inspect_brk_; }
		private:
			Path file_;
			bool inspect_brk_;
		};

		class GuiEvent : public Event {
		public:
			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			GuiEvent()
				: Event(0)
			{}
		};

		class EmptyPtr {
		public:
			virtual ~EmptyPtr() {}

		private:
			EmptyPtr* d_ptr;
		};
		class DumpRequestEvent : public Event {
		public:
			DumpRequestEvent(Runnable* p)
				: Event(p)
			{}
		};
		class ActivitiesShowEvent : public QEvent {
		public:

			static inline QEvent::Type eType = static_cast<QEvent::Type>(registerEventType());
			ActivitiesShowEvent(/*QTreeWidgetItem* item*/);
			//QTreeWidgetItem* getItem() const;
		private:
			//QTreeWidgetItem* item;
		};

		class EventDispatcher : public QObject, public boost::serialization::singleton<EventDispatcher> {
		public:
			EventDispatcher();
			void push(QObject* receiver);

			static	EventDispatcher* Dispatcher() { return &EventDispatcher::get_mutable_instance(); }
			static	const EventDispatcher* ConstDispatcher() { return &EventDispatcher::get_const_instance(); }
		protected:
			void customEvent(QEvent* event) override;

		private:
			QObjectList concerns;
		};
		//Q_GLOBAL_STATIC(EventDispatcher, eDispatcher)
	}
}
