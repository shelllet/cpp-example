#pragma once
#include "framework.h"
#include <qsharedpointer.h>

namespace shelllet {
	namespace core {
		template<typename T, bool C>
		class QObjectPrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename... Args>
			QObjectPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}

			virtual	~QObjectPrivate() {
				if (!weak_objectnamechanged.isNull()) {
					weak_objectnamechanged.toStrongRef().reset();
				}
				std::for_each(connections.begin(), connections.end(), std::bind([](auto& itor) { itor.second.second.Reset(); }, std::placeholders::_1));
			}
			void pushConnection(const std::string& name, QMetaObject::Connection c, CopyablePersistent<v8::Function> p) {
				connections[name] = std::make_pair(c, p);
			}
			bool removeConnection(const std::string& name) {
				if (connections.contains(name)) {
					QObject::disconnect(connections[name].first);
					return connections.erase(name) == 1;
				}
				return false;
			}

			QWeakPointer<v8::Global<v8::Function>> weak_objectnamechanged;

			std::map<std::string, std::pair<QMetaObject::Connection, CopyablePersistent<v8::Function>>> connections;
		protected:

			//
		};
	}
}