#include "events/file_browser_event.h"

using namespace shelllet::events;
FileBrowserEvent::FileBrowserEvent(const std::filesystem::path& root, const std::filesystem::path& filename)
	: QEvent(FileBrowserEvent::Type)
	, fileName_(filename)
	, root_(root)

{
}

std::filesystem::path shelllet::events::FileBrowserEvent::getFileName() const
{
	return fileName_;
}

std::filesystem::path shelllet::events::FileBrowserEvent::filePath() const
{
	return root_;
}