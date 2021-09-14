#pragma once
#include "common.hpp"
namespace shelllet {
	namespace common {
		class FilePrivate;
		class File : public Object {
			Q_DECLARE_PRIVATE(File)
		public:
			File();
			File(const String& name);
			File(const Path& path);
			static String readAllAsText(const Path& path);

			File& operator<<(const String& str);

			void write(const String &data);

			static void copy(const Path& src, const Path& target);
		protected:
			File(FilePrivate& d);
		};
	}
}
