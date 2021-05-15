#pragma once
#include "resource.h"
#include <boost/serialization/singleton.hpp>
#include <qstring.h>

namespace shelllet {
	namespace options {
		struct options_data {
			std::filesystem::path modules_path;
			std::string extension;
		};
		class options_manager : public boost::serialization::singleton<options_manager> {
		public:
			options_manager();
		public:
			void set_modules_path(const QString& path);
		public:
			options_data options;
		};
	}
}