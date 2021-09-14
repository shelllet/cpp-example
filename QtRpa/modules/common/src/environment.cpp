#include "common/environment.h"
#include "common/logs.h"
#include "common/private/object_p.h"
#include "qcoreapplication.h"
namespace shelllet {
	namespace common {
		class EnvironmentPrivate : public ObjectPrivate {
		public:
			std::unique_ptr<Options> data = std::make_unique<Options>();

			//Path scripts;
			String script_extension;
			Path current_filepath;
			Path assets;
			String index_xml_filename;
			String pkg_src;
			Path tplPath;
		};

		Q_GLOBAL_STATIC(Environment, __env__)
	}
}
shelllet::common::Environment::Environment() : Object(*new EnvironmentPrivate, nullptr)
{
	Q_D(Environment);
	d->data->modules_path = std::filesystem::current_path() / "modules";
	d->data->extension = ".dll";

	d->data->pkg_extension = ".zip";

#ifdef _DEBUG
	d->data->home = CMAKE_OUT_DIR;
#else
	d->data->home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
#endif // _DEBUG
	d->data->config_filename = "config.yaml";
	d->index_xml_filename = "index.xml";
	d->data->readme_filename = "README.md";
	d->data->mime_data_type = "application/activity";
	d->pkg_src = "src";
	d->data->pkg_res = "res";
	d->script_extension = ".py";
	d->data->pipe_name = "\\\\.\\pipe\\breakpad_crash_service\\shelllet";
	d->data->dump_remote = "https://shelllet.com?apikey=";


#ifdef _DEBUG
	d->assets = CMAKE_SOURCE_DIR "/assets";
	d->data->modPath = CMAKE_SOURCE_DIR "/.mod";
	d->data->module_search_path = CMAKE_SOURCE_DIR "/library";
#else
	d->data->modPath = std::filesystem::path(QCoreApplication::applicationDirPath().toStdString()) / ".mod";
	d->assets = std::filesystem::path(QCoreApplication::applicationDirPath().toStdString()) / "assets";
	d->data->module_search_path = std::filesystem::path(QCoreApplication::applicationDirPath().toStdString()) / "library";
#endif // _DEBUG

	d->data->applicationName = QObject::tr("Hello");
}

void shelllet::common::Environment::setModulePath(const QString& path)
{
	Q_D(Environment);
	d->data->modules_path = path.toStdWString();
}

shelllet::common::Path shelllet::common::Environment::indexXmlPath() const
{
	Q_D(const Environment);
	return (d->pkg_src + "/" + d->index_xml_filename).toStdString();
}




std::filesystem::path shelllet::common::Environment::storagePath() const
{
	Q_D(const Environment);

	std::filesystem::path tmp = d->data->home; 
	
	return tmp /= QCoreApplication::organizationName().toStdWString();
}

std::filesystem::path shelllet::common::Environment::logsPath() const
{
	Q_D(const Environment);
	return storagePath() /= "logs";
}

std::filesystem::path shelllet::common::Environment::dumpPath() const
{
	Q_D(const Environment);
	return storagePath() /= "dump";
}

std::filesystem::path shelllet::common::Environment::modPath() const
{
	Q_D(const Environment);
	return d->data->modPath;
}

QIcon shelllet::common::Environment::getIconByName(const String& name) const
{
	return QIcon(*getIconFileName(name).toQString());
}

QIcon shelllet::common::Environment::iconMods(const std::string& filename) const
{
	Q_D(const Environment);
	auto full_filename = d->data->modPath / filename;
	return QIcon(QString::fromStdString(full_filename.string()));
}

QPixmap shelllet::common::Environment::pixmap(const std::string& name) const
{
	Q_D(const Environment);
	Path filename = d->assets / "images/";
	filename.replaceFileName(name);
	return QPixmap(*filename.toString().toQString());
}

shelllet::common::String shelllet::common::Environment::getIconFileName(const String& name) const
{
	Q_D(const Environment);
	Path filename = d->assets / "icons/";

	filename.replaceFileName(name + ".svg");
	return filename.toString();
}

shelllet::common::Environment* shelllet::common::Environment::getInstanceRef()
{
	return __env__;
}

const shelllet::common::Environment* shelllet::common::Environment::getInstance()
{
	return __env__;
}

shelllet::common::Options const* shelllet::common::Environment::getOptions() const
{
	Q_D(const Environment);
	return d->data.get();
}

shelllet::common::Path shelllet::common::Environment::getViewPath() const
{
	Q_D(const Environment);
	return d->assets / "library";
}

shelllet::common::Path shelllet::common::Environment::getModePath() const
{
	Q_D(const Environment);
	return d->data->module_search_path;
}

shelllet::common::String shelllet::common::Environment::getPkgSrcName() const
{
	Q_D(const Environment);
	return d->pkg_src;
}

shelllet::common::String shelllet::common::Environment::getScriptExtension() const
{
	Q_D(const Environment);
	return d->script_extension;
}

shelllet::common::Path shelllet::common::Environment::getAssetsPath() const
{
	Q_D(const Environment);
	return d->assets;
}

shelllet::common::Path shelllet::common::Environment::getActivitiesPath() const
{
	Q_D(const Environment);
	return d->assets / "activities";
}

shelllet::common::Path shelllet::common::Environment::getCurrentProjectPath() const
{
	Q_D(const Environment);
	return d->current_filepath;
}
void shelllet::common::Environment::setCurrentFilePath(const Path& path)
{
	Q_D(Environment);
	d->current_filepath = path;
}

shelllet::common::Path shelllet::common::Environment::getTemplatePath() const
{
	Q_D(const Environment);
	return d->assets / "template";
}

shelllet::common::String shelllet::common::Environment::getIndexFileName() const
{
	Q_D(const Environment);
	return d->index_xml_filename;
}
