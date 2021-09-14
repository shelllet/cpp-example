#pragma once
#include "composite_property_p.h"

namespace shelllet {
	namespace interpreter {
		class ProcessStartPrivate : public CompositePropertyPrivate {
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& boost::serialization::base_object<CompositePropertyPrivate>(*this);

				ar& m_fileName;
			}
		public:
			String m_fileName;
			QStringList m_parameters;
			QString m_workingDirectory;
		};
}
}