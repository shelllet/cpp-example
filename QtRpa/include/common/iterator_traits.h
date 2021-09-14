#pragma once
#include <iterator>

namespace shelllet {
	namespace common {
		template <class Iterator>
		struct iterator_value
		{
			typedef typename std::iterator_traits<Iterator>::value_type type;
		};

		template <class Iterator>
		struct iterator_reference
		{
			typedef typename std::iterator_traits<Iterator>::reference type;
		};


		template <class Iterator>
		struct iterator_pointer
		{
			typedef typename std::iterator_traits<Iterator>::pointer type;
		};

		template <class Iterator>
		struct iterator_difference
		{
			typedef typename std::iterator_traits<Iterator>::difference_type type;
		};

		template <class Iterator>
		struct iterator_category
		{
			typedef typename std::iterator_traits<Iterator>::iterator_category type;
		};

	}

}

