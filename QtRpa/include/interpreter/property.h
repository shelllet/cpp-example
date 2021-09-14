#pragma once
#include "pugixml.hpp"
#include "qobject.h"
#include "qstring.h"
#include <boost/archive/basic_archive.hpp>
#include "boost/serialization/split_free.hpp"
#include "boost/serialization/split_free.hpp"
#include "boost/serialization/list.hpp"
#include "boost/serialization/string.hpp"
#include "boost/serialization/version.hpp"
#include "common.hpp"

namespace shelllet {
	namespace property {
		class PropertySheet;
		class PropertyBrowser;
	}
	namespace interpreter {
		class PropertyPrivate;
	
		class Property : public QObject {
			Q_OBJECT
				Q_DECLARE_PRIVATE(Property)
		public:
			Property(QObject* parent = nullptr);
			Property(const XmlNode& node, QObject* parent = nullptr);
			virtual void initialize();
			String displayName() const;

			void deleteLater();

			/*pugi::xml_node getNode() const;*/

			virtual	property::PropertySheet* getMisc(property::PropertyBrowser*);

			virtual std::vector<property::PropertySheet*> getProp(property::PropertyBrowser* browser);

			virtual	property::PropertySheet* getInput(property::PropertyBrowser*);

			virtual property::PropertySheet* getOutput(property::PropertyBrowser*);

			virtual	std::shared_ptr<XmlDocument> getNode();

			//virtual QByteArray toData() const = 0;
			virtual std::string json() const = 0;
		//	virtual void fromData(const QByteArray& data) =0;
			virtual QString metaName() const;
			 String tagName() const;

			 QIcon icon() const;

			//virtual void toXml(pugi::xml_node& node);
			//virtual void fromXml(const pugi::xml_node& node);

		signals:
			void displayNameChanged();
		public:
			static QString Prefix();


		protected:
			Property(PropertyPrivate& d, const XmlNode& node, QObject* parent = nullptr);
		private:

			//pugi::xml_node node_;
		};

	}
}
Q_DECLARE_METATYPE(pugi::xml_node)
Q_DECLARE_METATYPE(shelllet::interpreter::Property*)