#pragma once
#include "composite_property_p.h"

namespace shelllet {
	namespace interpreter {
		class PrintPrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositeProperty>(*this);

				ar& message_;
			}
		public:
			QString message_;
			
			QString id;

		};
	}
}
BOOST_CLASS_VERSION(shelllet::interpreter::PrintPrivate, 1)