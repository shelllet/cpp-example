#pragma once
#include "composite_property_p.h"

namespace shelllet {
	namespace interpreter {
		class NetworkUDPServerPrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositeProperty>(*this);
			}

		public:

			int64_t m_port;
			QString m_ip;
			QString m_code;
			QString m_outputVariable;
		};
	}
}