#include "common/path.h"
#include "common/directoryentry.h"
#include "common/directoryiterator.h"
#include "common/private/directoryiterator_p.h"
shelllet::common::DirectoryIterator::DirectoryIterator(Object* parent /*= nullptr*/)
	:DirectoryIterator(*new DirectoryIteratorPrivate, parent)
{

}

shelllet::common::DirectoryIterator& shelllet::common::DirectoryIterator::operator++()
{
	Q_D(DirectoryIterator);
	d->iterator->operator++();
	return *this;
}

bool shelllet::common::DirectoryIterator::operator==(const DirectoryIterator& rhs) const noexcept
{
	Q_D(const DirectoryIterator);
	return *d->iterator == *rhs.d_func()->iterator;
}

bool shelllet::common::DirectoryIterator::operator!=(const DirectoryIterator& rhs) const noexcept
{
	Q_D(const DirectoryIterator);
	return *d->iterator != *rhs.d_func()->iterator;
}

shelllet::common::DirectoryIterator shelllet::common::DirectoryIterator::begin() const
{
	Q_D(const DirectoryIterator);
	return std::filesystem::begin(*d->iterator);
}

shelllet::common::DirectoryIterator shelllet::common::DirectoryIterator::end() const
{
	Q_D(const DirectoryIterator);
	return std::filesystem::end(*d->iterator);
}

const shelllet::common::DirectoryEntry& shelllet::common::DirectoryIterator::operator*() const noexcept
{
	Q_D(const DirectoryIterator);
	static DirectoryEntry entry;
	entry = d->iterator->operator*();
	return entry;
}

const shelllet::common::DirectoryEntry* shelllet::common::DirectoryIterator::operator->() const noexcept
{
	Q_D(const DirectoryIterator);
	static DirectoryEntry entry;
	entry = *d->iterator->operator->();
	return &entry;
}

shelllet::common::DirectoryIterator::DirectoryIterator(const std::filesystem::directory_iterator& iterator, Object* parent /*= nullptr*/)
	: DirectoryIterator(*new DirectoryIteratorPrivate, parent)
{
	Q_D(DirectoryIterator);
	d->iterator.reset(new std::filesystem::directory_iterator(iterator));
}

shelllet::common::DirectoryIterator::DirectoryIterator(const Path& p, Object* parent /*= nullptr*/)
	: DirectoryIterator(*new DirectoryIteratorPrivate, parent)
{
	Q_D(DirectoryIterator);
	d->iterator.reset(new std::filesystem::directory_iterator(p));
}

shelllet::common::DirectoryIterator::DirectoryIterator(DirectoryIteratorPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
