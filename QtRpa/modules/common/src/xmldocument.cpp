#include "common.hpp"
#include "pugixml.hpp"
#include "qsharedpointer.h"
#include "common/private/xmldocument_p.h"

namespace shelllet {
	namespace common {
		using namespace pugi;
		template <typename F, typename... TArgs>
		decltype(auto) __invoke__(const XmlDocumentPrivate* p, F fuc, TArgs&& ... args) {
			if (std::holds_alternative<SharedPointer<pugi::xml_document>>(p->node)) {
				return (*std::get<1>(p->node).*fuc)(std::forward<TArgs>(args)...);
			}
			throw std::logic_error("The method or operation is not implemented.");
			//return (*std::get<0>(p->node).*fuc)(std::forward<TArgs>(args)...);
		}
		std::ostream& operator<<(std::ostream& out, const XmlDocument& doc)
		{
			__invoke__(doc.d_func(), static_cast<void(pugi::xml_document::*)(std::basic_ostream<char, std::char_traits<char> >&
				, const char_t *
				, unsigned int
				, pugi::xml_encoding encoding
				, unsigned int
				) const>(&pugi::xml_document::print), out, "\t", pugi::format_default, pugi::encoding_auto, 0);
			return out;
		}


	}
}


shelllet::common::XmlDocument::XmlDocument(Object* parent/* = nullptr*/)
	:XmlDocument(*new XmlDocumentPrivate, parent)
{

}

shelllet::common::XmlNode shelllet::common::XmlDocument::documentElement() const
{
	Q_D(const XmlDocument);
	auto node = __invoke__(d, &pugi::xml_document::document_element);
	return XmlNode::from(&node);
}

void shelllet::common::XmlDocument::addDeclaration()
{
	Q_D(XmlDocument);
	pugi::xml_node decl = __invoke__(d, static_cast<pugi::xml_node(pugi::xml_document::*)(pugi::xml_node_type)>(&pugi::xml_document::append_child), pugi::node_declaration);
	decl.append_attribute("version") = "1.0";
	decl.append_attribute("encoding") = "utf-8";
	decl.append_attribute("standalone") = "yes";
}

void shelllet::common::XmlDocument::loadFile(const Path& path)
{
	Q_D(XmlDocument);


	pugi::xml_parse_result result = __invoke__(d, static_cast<pugi::xml_parse_result(pugi::xml_document::*)(const char*, unsigned int, pugi::xml_encoding)>(&pugi::xml_document::load_file)
		, path.toString().toUtf8()
		, pugi::parse_default
		, pugi::encoding_auto
	);

	if (!result)
	{
		LOG_WARNING(PROJECT_NAME) << "# error description: " << result.description() << "\n"
			<< "error offset: " << result.offset << " (error at " << result.offset << ".\n\n";
	}
}

void shelllet::common::XmlDocument::print(std::ostream& stream)
{
	Q_D(XmlDocument);
	stream << *this;
}

shelllet::common::XmlDocument::XmlDocument(const Path& p, Object* parent /*= nullptr*/)
	: XmlDocument(*new XmlDocumentPrivate, parent)
{
	loadFile(p);
}

shelllet::common::XmlDocument::XmlDocument(XmlDocumentPrivate& d, Object* parent/* = nullptr*/)
	: XmlNode(d, parent)
{
	d.node = std::make_shared<pugi::xml_document>();
}