#pragma once
#include "qobject.h"
#include "boost/noncopyable.hpp"

namespace shelllet {
	namespace common {
		class Object;
		class ObjectData : private boost::noncopyable
		{
		public:
			virtual ~ObjectData() = 0;
		public:
			Object* q_ptr;
			Object* parent;
			std::list<Object*> children;
		};
		class ObjectPrivate : public ObjectData {
		public:
			virtual ~ObjectPrivate();
		};
		class Object {
			Q_DECLARE_PRIVATE(Object)
		public:

		protected:
			Object(ObjectPrivate& dd, Object* parent = nullptr);
		protected:
			std::unique_ptr<ObjectData> d_ptr;
		};
	}

	using namespace common;
}