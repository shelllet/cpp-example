#pragma once
namespace shelllet {
	namespace common {
		class ElementParserPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(ElementParser)
		public:

			std::list<std::shared_ptr<pugi::xml_document>> data;


			const char* key_filename = "config.yaml";
			const char* key_description = "description";
			const char* key_name = "name";
			const char* key_properties = "properties";
			const char* key_type = "type";
			const char* key_elements = "elements";
			const char* key_display = "display";
			const char* key_icon = "icon";
			const char* key_system = "system";
		};
	}
}
