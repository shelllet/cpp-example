#include "creator.hpp"
#include "common.hpp"
#include <qfiledialog.h>
#include <libzippp/libzippp.h>
#include <qdatetime.h>
#include <iostream>
#include <fstream>
#include <pugixml.hpp>
#include <yaml-cpp/yaml.h>


namespace shelllet {
	//using namespace libzippp;
}
void shelllet::creator::New::messageCallback(Callback* call)
{
	auto* parent = dynamic_cast<QWidget*>(call);

	//auto fmt = boost::format("%1% (*%2%)") % QObject::tr("Project File").toStdString() % common::Environment::getInstance()->getOptions()->pkg_extension.toStdString();

	auto fileName = QFileDialog::getSaveFileName(parent, QObject::tr("Save File"), QString::fromStdString(common::Environment::getInstance()->storagePath().string()));

	if (fileName.isEmpty())
		return;
	Path file = String::fromQString(&fileName);

	std::filesystem::create_directories(file);
	std::filesystem::create_directory(file / Environment::getInstance()->getPkgSrcName());
	YAML::Emitter config;
	{
		config << YAML::BeginMap;
		config << YAML::Key << "name";
		config << YAML::Value << file.fileName();

		config << YAML::Key << "created";
		config << YAML::Value << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();

		config << YAML::EndMap;

		std::ofstream ss(file / Environment::getInstance()->getOptions()->config_filename.toStdString());
		ss << config.c_str();

	}
	std::string readme = "# description";
	{

		std::ofstream ss(file / "README.md");
		ss << readme;
	}

	//std::string code = "";
	{
		//XmlDocument doc;
		//doc.addDeclaration();
		///AddDocumentElement(doc);
	
	//	auto prop = Helper::createRoot();

		//auto* sequence = new PropParser();

		//doc.appendCopy(std::make_unique<Sequence>()->getNode()->documentElement());

		/*std::stringstream stream;
		doc.print(stream);
		xml = stream.str();*/

		;

		File::copy(Environment::getInstance()->getTemplatePath() / Environment::getInstance()->getIndexFileName(),
			file / Environment::getInstance()->indexXmlPath());
	}



	call->callbk(this, 1, file);
}
