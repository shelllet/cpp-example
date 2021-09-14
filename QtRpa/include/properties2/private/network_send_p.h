#pragma once
#include "composite_property_p.h"

namespace shelllet {
	namespace interpreter {
		class NetworkSendPrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositeProperty>(*this);
			}
		public:

			QString m_data;
			QString m_owner;
		};
}
}