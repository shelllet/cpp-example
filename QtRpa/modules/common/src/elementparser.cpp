#include "common.hpp"
#include "pugixml.hpp"
#include "common/elementparser.h"
#include "common/environment.h"
#include "yaml-cpp/yaml.h"
#include "common/private/object_p.h"
#include "common/private/elementparser_p.h"
namespace shelllet {
	namespace fs = std::filesystem;
	using namespace YAML;
	using namespace pugi;
}

shelllet::common::ElementParser::ElementParser()
	: Object(*new ElementParserPrivate, nullptr)
{

}

void shelllet::common::ElementParser::parseElement()
{
	Q_D(ElementParser);


	for (auto& p : fs::directory_iterator(Environment::getInstance()->modPath())) {
		fs::path config = p.path() / d->key_filename;
		if (!fs::exists(config)) {
			continue;
		}

		Node root = LoadFile(config.string());
		Node elements = root[d->key_elements];
		if (elements && elements.IsSequence()) {
			std::shared_ptr<xml_document> doc = std::make_shared<xml_document>();
			auto e = doc->append_child(p.path().filename().string().c_str());
			e.append_attribute(d->key_display) = root[d->key_name].as<std::string>().c_str();

			for (std::size_t i = 0; i < elements.size(); ++i) {
				if (auto tmp = elements[i][d->key_name]) {
					xml_node node = e.append_child(tmp.as<std::string>().c_str());
					if (auto tmp = elements[i][d->key_description]) {
						node.append_attribute(d->key_description) = tmp.as<std::string>().c_str();
					}
					if (auto tmp = elements[i][d->key_display]) {
						node.append_attribute(d->key_display) = tmp.as<std::string>().c_str();
					}

					xml_node p = node.append_child(d->key_properties);
					auto properties = elements[i][d->key_properties];
					if (properties && properties.IsSequence())
					{
						for (std::size_t i = 0; i < properties.size(); ++i) {
							const_iterator it = properties[i].begin();
							auto ch = p.append_child(it->first.as<std::string>().c_str());
							ch.text().set(it->second.as<std::string>().c_str());

							for (it = properties[i].begin(), it++; it != properties[i].end(); ++it) {
								std::string key = it->first.as<std::string>();
								std::string value = it->second.as<std::string>();

								ch.append_attribute(key.c_str()) = value.c_str();
							}

						}
					}
				}


			}
			LOG_DEBUG("rpa") << *doc << std::endl;

			d->data.push_back(doc);
		}
	}

}

std::list<std::shared_ptr<pugi::xml_document>> shelllet::common::ElementParser::data() const
{
	Q_D(const ElementParser);
	return d->data;
}

String shelllet::common::ElementParser::keyDisplay() const
{
	Q_D(const ElementParser);
	return d->key_display;
}

String shelllet::common::ElementParser::keyDecoration() const
{
	Q_D(const ElementParser);
	return d->key_icon;
}

String shelllet::common::ElementParser::keySystem() const
{
	Q_D(const ElementParser);
	return d->key_system;
}
