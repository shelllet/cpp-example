#pragma once
#include "object_p.h"
class QFile;
namespace shelllet {
	namespace common {
		class FilePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(File)
		public:

			std::unique_ptr<QFile> file;
		};
	}
}
