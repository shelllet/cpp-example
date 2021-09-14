#pragma once
#include <filesystem>
#include <qobject.h>
#include <qglobalstatic.h>
#include <qgraphicsitem.h>
#include <qevent.h>
namespace shelllet {
	namespace events {
		class FileBrowserEvent : public QEvent {
		public:

			static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
			FileBrowserEvent(const std::filesystem::path& root, const std::filesystem::path& filename);
			std::filesystem::path getFileName() const;
			std::filesystem::path filePath() const;
		private:
			std::filesystem::path fileName_;
			std::filesystem::path root_;
		};
	}
}
