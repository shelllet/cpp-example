#pragma once
#include "object_p.h"
namespace shelllet {
    namespace common{
        class DirectoryEntryPrivate : public ObjectPrivate {
            Q_DECLARE_PUBLIC(DirectoryEntry)
        public:

            UniquePointer<std::filesystem::directory_entry> entry = std::make_unique<std::filesystem::directory_entry>();
        };
    }
}
