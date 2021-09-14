#pragma once
#include "qobject.h"
#include "boost/noncopyable.hpp"

namespace shelllet {
	namespace common {

		enum class XmlNodeType
		{
			Null,			// Empty (null) node handle
			Document,		// A document tree's absolute root
			Element,		// Element tag, i.e. '<node/>'
			PCData,		// Plain character data, i.e. 'text'
			CData,			// Character data, i.e. '<![CDATA[text]]>'
			Comment,		// Comment tag, i.e. '<!-- text -->'
			PI,			// Processing instruction, i.e. '<?name?>'
			Declaration,	// Document declaration, i.e. '<?xml version="1.0"?>'
			DocType		// Document type declaration, i.e. '<!DOCTYPE doc>'
		};


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
			Object() = default;
			void invokeMethod(Object* obj);
		protected:
			Object(ObjectPrivate& dd, Object* parent = nullptr);
		protected:
			std::unique_ptr<ObjectData> d_ptr;
		};
	}
}