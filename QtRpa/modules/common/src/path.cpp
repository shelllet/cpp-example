#include "common/framework.h"
#include "common/alias.h"
#include "common/path.h"
#include "common/logs.h"
#include "common/private/path_p.h"
#include "qcoreapplication.h"

namespace shelllet {
	namespace common {
		std::ostream& operator<<(std::ostream& o, const Path& p)
		{
			o << p.d_func()->path;
			return o;
		}
	}
}
using namespace shelllet::common;

shelllet::common::Path::Path(PathPrivate& d)
	: Object(d, nullptr)
{
	
}

shelllet::common::Path::Path(const char* path)
	: Path(*new PathPrivate)
{
	Q_D(Path);
	d->path = path;
}

shelllet::common::Path::Path(const std::string& path)
	: Path(*new PathPrivate)
{
	Q_D(Path);
	d->path = path;
}

shelllet::common::Path::Path(const std::filesystem::path& path)
	: Path(*new PathPrivate)
{
	Q_D(Path);
	d->path = path;
}

shelllet::common::Path::Path()
	: Path(*new PathPrivate)
{

}

shelllet::common::Path& shelllet::common::Path::operator=(const Path& p)
{
	Q_D(Path);
	d->path = p.d_func()->path;

	return *this;
}

shelllet::common::Path::Path(const Path& p)
	: Path(*new PathPrivate)
{
	Q_D(Path);
	d->path = p.d_func()->path;
}

shelllet::common::Path& shelllet::common::Path::operator/=(const Path& path)
{
	Q_D(Path);
	d->path /= path.d_func()->path;
	return *this;
}

void shelllet::common::Path::replaceExtension(const Path& path)
{
	Q_D(Path);
	d->path.replace_extension(path.d_func()->path);
}

void shelllet::common::Path::replaceFileName(const Path& path)
{
	Q_D(Path);

	d->path.replace_filename(path.d_func()->path);
}

shelllet::common::String shelllet::common::Path::fileName() const
{
	Q_D(const Path);
	return d->path.stem().string();
}

shelllet::common::Path shelllet::common::Path::operator/(const char* path) const
{
	Q_D(const Path);
	return d->path / path;
}

shelllet::common::Path shelllet::common::Path::operator/(const Path& path) const
{
	Q_D(const Path);
	return d->path / path.d_func()->path;
}

shelllet::common::String shelllet::common::Path::toString() const
{
	Q_D(const Path);
	return d->path.string();
}

bool shelllet::common::Path::isExist() const
{
	Q_D(const Path);
	return std::filesystem::exists(d->path);
}

bool shelllet::common::Path::isEmpty() const
{
	Q_D(const Path);
	return d->path.empty();
}

bool shelllet::common::Path::isDir() const
{
	Q_D(const Path);
	return std::filesystem::is_directory(d->path);
}

shelllet::common::String shelllet::common::Path::extension() const
{
	Q_D(const Path);
	return d->path.extension().string();
}

shelllet::common::Path shelllet::common::Path::applicationDirPath()
{
	return String::fromQString(&static_cast<const QString&>(QCoreApplication::applicationDirPath())) ;
}

std::filesystem::path shelllet::common::Path::toStdPath() const
{
	Q_D(const Path);
	return d->path;
}

shelllet::common::Path::Path(const String& path)
	: Path(*new PathPrivate)
{
	Q_D(Path);
	
	d->path = path.toStdString();
}

shelllet::common::Path::operator std::filesystem::path() const
{
	Q_D(const Path);
	return d->path;
}
