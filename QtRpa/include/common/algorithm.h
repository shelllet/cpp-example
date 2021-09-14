#pragma once
#include "framework.h"
namespace shelllet {
	namespace common {

		template< typename SequenceSequenceT, typename Range1T>
		inline typename boost::range_value<SequenceSequenceT>::type
			join(
				const SequenceSequenceT& Input,
				const Range1T& Separator)
		{
			return boost::join(Input, Separator);
		}
	
	}
}



