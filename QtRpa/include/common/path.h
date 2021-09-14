#pragma once
#include "qdir.h"
#include "object.h"
#include "string.h"

namespace shelllet {
	namespace common {
		class PathPrivate;
		class Path : public Object{
			Q_DECLARE_PRIVATE(Path)
				friend std::ostream& operator<< (std::ostream&, const Path&);
		public:
			Path();
			Path(const String& path);
			Path(const Path& path);
			Path(const std::filesystem::path& path);
			Path(const std::string& path);
			Path(const char* path);
			Path& operator =(const Path& path);
		protected:
			Path(PathPrivate& d);
		public:

			Path& operator/=(const Path& path);
			Path operator/(const Path& path) const;
			Path operator/(const char* path) const;
			operator std::filesystem::path() const;
			void replaceExtension(const Path& path);
			void replaceFileName(const Path& path);
			String fileName() const;
			String toString() const;
			bool isExist() const;
			bool isEmpty() const;
			bool isDir() const;
			String extension() const;

			static Path applicationDirPath();
			std::filesystem::path toStdPath() const;
		private:
		};
	}
}