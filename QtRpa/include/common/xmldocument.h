#pragma once
#include "xmlnode.h"
namespace shelllet {
	namespace common {
		class XmlDocumentPrivate;
		class XmlDocument : public XmlNode {
			Q_DECLARE_PRIVATE(XmlDocument)
				friend std::ostream& operator<< (std::ostream& out, const XmlDocument& doc);
		public:
			XmlDocument(Object* parent = nullptr);
			XmlDocument(const Path& p, Object* parent = nullptr);

			XmlNode documentElement() const;

			void addDeclaration();

			void loadFile(const Path& path);

			void print(std::ostream& stream);
		protected:
			XmlDocument(XmlDocumentPrivate& d, Object* parent = nullptr);
		};
	}
}
