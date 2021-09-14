#pragma once
#include "common.hpp"
#include "composite_property_p.h"
namespace shelllet {
	namespace interpreter {
		class CodePrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositeProperty>(*this);

				ar& import;
				ar& code;
			}
		public:
			String import;
			String code;
		};
	}
}
BOOST_CLASS_VERSION(shelllet::interpreter::CodePrivate, 1)