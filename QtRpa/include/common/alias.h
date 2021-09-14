#pragma once
#include "framework.h"


namespace std {
	//template<typename T>
//	using iterator = iterator_traits<T>;
}
namespace shelllet {
	namespace common {
		//using String = std::string;
		using WString = std::wstring;
		//using Path = std::filesystem::path;
		//template<class T>
	//	struct Alloc { };

		template<class T,
			class Allocator = std::allocator<T>>
			using Vector = std::vector<T, Allocator>;

		using Int32 = std::int32_t;

		using UInt32 = std::uint32_t;

		using Bool = bool;

		template <class T, class Deleter = std::default_delete<T>>
		using UniquePointer = std::unique_ptr<T, Deleter >;

		template <class T>
		using SharedPointer = std::shared_ptr<T >;

		template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
		using Set = std::set<Key, Compare, Allocator>;
		
		template <class... Types>
		using Variant = std::variant<Types...>;
	}
}