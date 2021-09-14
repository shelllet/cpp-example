#pragma once
#include "object.h"
namespace shelllet {
	namespace common {
		class DirectoryIteratorPrivate;
		class DirectoryIterator : public Object {
			Q_DECLARE_PRIVATE(DirectoryIterator)
		public:
			DirectoryIterator(Object* parent = nullptr);
			DirectoryIterator(const Path& p, Object* parent = nullptr);
			DirectoryIterator(const std::filesystem::directory_iterator& iterator, Object* parent = nullptr);


			using value_type = DirectoryIterator;
			using difference_type = std::ptrdiff_t;
			using pointer = const DirectoryIterator*;
			using reference = const DirectoryIterator&;
			using iterator_category = std::input_iterator_tag;

			DirectoryIterator& operator++();

			bool operator==(const DirectoryIterator& rhs) const noexcept;

			bool operator!=(const DirectoryIterator& rhs) const noexcept;

			DirectoryIterator begin() const;
			DirectoryIterator end() const;

			const DirectoryEntry& operator*() const noexcept;

			const DirectoryEntry* operator->() const noexcept;

		protected:
			DirectoryIterator(DirectoryIteratorPrivate& d, Object* parent = nullptr);
		};
	}
}
