#pragma once

namespace shelllet {
	namespace common {
		class ElementParserPrivate;
		class ElementParser : public Object , public boost::serialization::singleton<ElementParser>{
			Q_DECLARE_PRIVATE(ElementParser)
		public:
			ElementParser();
			void parseElement();

			std::list<std::shared_ptr<pugi::xml_document>> data() const;


			String keyDisplay() const;

			String keyDecoration() const;

			String keySystem() const;
		};
	}
}
