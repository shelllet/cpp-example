#pragma once
namespace shelllet {
	namespace interpreter {
		class Element;
	}
	namespace interpreter {

		class PropParserPrivate;
		class PropParser : public Object {
			Q_DECLARE_PRIVATE(PropParser)
		public:

			PropParser(const XmlNode& node, interpreter::Element* parentItem = nullptr, Object* parent = nullptr);
			//py::object loadPy(const XmlNode& node);
			interpreter::Element* element();

			CompositeProperty* prop();
			//	static PropParser* getInstance();
		protected:
			PropParser(PropParserPrivate& d);
		};
	}
}
