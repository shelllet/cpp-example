#pragma once
#include "pugixml.hpp"
#include "boost/serialization/list.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/version.hpp"
#include "private/qobject_p.h"
#include "qicon.h"
class QtProperty;
namespace shelllet {
	namespace interpreter {
		class PropertyPrivate : public QObjectPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& m_displayName;
				ar& icon;
			}

		public:
			String m_displayName;
			PropertySheet* m_misc;
			String tagName;
			QIcon icon;
		};
	}
}
BOOST_CLASS_VERSION(shelllet::interpreter::PropertyPrivate, 1)
