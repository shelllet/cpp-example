#pragma once
#include "framework.h"
#include "object.h"
#include "qstring.h"
#include "qstandardpaths.h"
#include "boost/serialization/singleton.hpp"
#include "qicon.h"
#include "path.h"
namespace shelllet {
	namespace common {
		struct Options {
			std::filesystem::path modules_path;
			QString extension;
			QString pkg_extension;
			std::filesystem::path home;

			QString config_filename;
			
			QString pkg_res;
			QString readme_filename;
		
			QString mime_data_type;
		//	QString version;
			//QString organization_name;
			QString pipe_name;
			QString dump_remote;
			
			QString applicationName;
		
			std::filesystem::path modPath;
			std::filesystem::path module_search_path;
			int depth = 1; // tree depth
		};
		class EnvironmentPrivate;
		class Environment : public Object {
			Q_DECLARE_PRIVATE(Environment)
		public:
			Environment();
		public:
			void setModulePath(const QString& path);
			Path indexXmlPath() const;
		
			std::filesystem::path storagePath() const;
			std::filesystem::path logsPath() const;
			std::filesystem::path dumpPath() const;
			
			std::filesystem::path modPath() const;
			QIcon getIconByName(const String &name) const;
			QIcon iconMods(const std::string& filename) const;
			QPixmap pixmap(const std::string& name) const;
			String getIconFileName(const String &name) const;
			static Environment* getInstanceRef();
			static const Environment* getInstance();

			Options const* getOptions() const;

			Path getViewPath() const;
			Path getModePath() const;
			String getPkgSrcName() const;
			String getScriptExtension() const;
			Path getAssetsPath() const;
			Path getActivitiesPath() const;

			Path getCurrentProjectPath() const;
			void setCurrentFilePath(const Path& path);

			Path getTemplatePath() const;
			String getIndexFileName() const;
		};
	}
}