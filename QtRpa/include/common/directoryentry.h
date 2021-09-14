#pragma once
#include "object.h"
namespace shelllet {
    namespace common{
        class DirectoryEntryPrivate;
        class DirectoryEntry : public Object {
            Q_DECLARE_PRIVATE(DirectoryEntry)
        public:
            DirectoryEntry(Object*parent = nullptr);
            DirectoryEntry(const std::filesystem::directory_entry& entry, Object* parent = nullptr);
            const Path& path() const noexcept;

            operator const Path& () const noexcept;
        protected:
            DirectoryEntry(DirectoryEntryPrivate& d, Object*parent = nullptr);
        };
    }
}
    