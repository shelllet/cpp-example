#pragma once
#include "composite_property_p.h"

namespace shelllet {
	namespace interpreter {

		class WorkflowAssignPrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositePropertyPrivate>(*this);

				ar& m_name;
				ar& m_value;
			}
		
		public:
			QString m_name;
			QVariant m_value;

		};
	}
}
BOOST_CLASS_VERSION(shelllet::interpreter::WorkflowAssignPrivate, 1)