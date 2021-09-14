#include "common/path.h"
#include "common/directoryentry.h"
#include "common/private/directoryentry_p.h"

shelllet::common::DirectoryEntry::DirectoryEntry(Object* parent /*= nullptr*/)
	:DirectoryEntry(*new DirectoryEntryPrivate, parent)
{

}

const shelllet::common::Path& shelllet::common::DirectoryEntry::path() const noexcept
{
	Q_D(const DirectoryEntry);
	static Path path;
	path= d->entry->path();
	return path;
}

shelllet::common::DirectoryEntry::DirectoryEntry(const std::filesystem::directory_entry& entry, Object* parent /*= nullptr*/)
	: DirectoryEntry(*new DirectoryEntryPrivate, parent)
{
	Q_D(DirectoryEntry);
	d->entry.reset(new std::filesystem::directory_entry(entry));
}

shelllet::common::DirectoryEntry::operator const shelllet::common::Path& () const noexcept
{
	Q_D(const DirectoryEntry);
	static Path path;
	path = d->entry->operator const std::filesystem::path &() ;
	return path;
}

shelllet::common::DirectoryEntry::DirectoryEntry(DirectoryEntryPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
