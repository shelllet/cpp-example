#pragma once
#include "property_p.h"
//#include "properties/helper.h"
namespace shelllet {
	namespace interpreter {
		class CompositePropertyPrivate : public PropertyPrivate{
			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<PropertyPrivate>(*this);
				ar& dtype_;
				ar& x_;
				ar& y_;
				ar& width_;
				ar& height_;
			}
		public:
			PropertySheet* m_input;
			PropertySheet* m_output;
			int32_t id_;
			int32_t pid_;

			float x_;
			float y_;

			float width_;
			float height_;
			DiagramType dtype_;
			String meta;
			String category;

		};
}
}