#include "common/file.h"
//#include "common/private/file_p.h"

namespace shelllet {
	namespace common {
		class FilePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(File)
		public:
			std::unique_ptr<QFile> file;
		};
	}
}


shelllet::common::String shelllet::common::File::readAllAsText(const Path& path)
{
	std::ifstream stream(path.toStdPath());
	BOOST_ASSERT_MSG(path.isExist(), "file not exist");
	return stream;
}

shelllet::common::File& shelllet::common::File::operator<<(const String& str)
{
	return *this;
}

void shelllet::common::File::write(const String& data)
{
	Q_D(File);
	if (!d->file->isOpen()) {
		BOOST_VERIFY_MSG(d->file->open(QIODevice::WriteOnly), "Open file failed.");

	}
	d->file->write(data.toUtf8());
}

void shelllet::common::File::copy(const Path& src, const Path& target)
{
	std::filesystem::copy_file(src, target);
}

shelllet::common::File::File(const Path& path)
	: File(*new FilePrivate)
{
	Q_D(File);
	d->file->setFileName(*path.toString().toQString());
}

shelllet::common::File::File(const String& name)
	: File(*new FilePrivate)
{
	Q_D(File);
	d->file->setFileName(*name.toQString());
}

shelllet::common::File::File()
	: File(*new FilePrivate)
{

}

shelllet::common::File::File(FilePrivate& d)
	: Object(d, nullptr)
{
	d.file = std::make_unique<QFile>();
}
