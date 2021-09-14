#pragma once
#include <filesystem>
#include <QMetaType>
#include <QString>
#include <QDataStream>
#include <QDebug>
#include <QDebugStateSaver>
#include <tuple>
#include <yaml-cpp/yaml.h>


namespace shelllet {
	namespace common {

		static inline void add_declaration(pugi::xml_document& doc)
		{
			pugi::xml_node decl = doc.append_child(pugi::node_declaration);
			decl.append_attribute("version") = "1.0";
			decl.append_attribute("encoding") = "utf-8";
			decl.append_attribute("standalone") = "yes";
		}
		
	/*	static inline void AddDocumentElement(pugi::xml_document& doc)
		{
			doc.append_child("items");			
		}*/


		template<typename T>
		static inline QString GetNamespace(const char * name) {
			return QString(typeid(T).name()).remove("class ").chopped(strlen(name));
		}

	
	}
}
