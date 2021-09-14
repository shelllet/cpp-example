#pragma once
#include "property.h"
namespace shelllet {
	namespace interpreter {
		enum DiagramType { Step, Conditional, StartEnd, Io };

		class CompositePropertyPrivate;
		class CompositeProperty : public Property
		{
			Q_OBJECT
				Q_DECLARE_PRIVATE(CompositeProperty)
		public:

			CompositeProperty(const XmlNode& node, QObject* parent = nullptr);
			virtual QString identifier() const { return ""; }

			void restore_from_xml(const std::string& xml);



			virtual int getPropertyMetaTypeID() const { return 0; }

			virtual	String category() const;
			virtual void jsCode(std::ostringstream& ss) const {  }
			int32_t getId() const;
			void setId(int32_t id);
			//virtual void toXml(pugi::xml_node& node);
			//virtual void fromXml(const pugi::xml_node& node);
			int32_t getParentId() const;
			void setParentId(int32_t id);

			virtual	void getCode(std::ostringstream& stream) {}
			virtual String getImport() const;
			virtual void exec();
			virtual void getDefines(std::ostringstream& oss);

			virtual std::shared_ptr<XmlDocument> getNode() override;


			std::string json() const override;

		protected:
			CompositeProperty(CompositePropertyPrivate& d, const XmlNode& node, QObject* parent = nullptr);
		public:
			virtual property::PropertySheet* getInput(property::PropertyBrowser*);

			virtual property::PropertySheet* getOutput(property::PropertyBrowser*);

			DiagramType	type();
			float x() const;
			float y() const;

			void setX(float x);
			void setY(float y);

			float width() const;
			float height() const;

			String meta() const;
			QPointF pos() const;

			//std::string meta_;

			static UniquePointer<CompositeProperty> CreateNode(const XmlNode& node);
			//static std::unique_ptr<CompositeProperty> CreateNode(const QString& name);
		};

		extern std::map<std::string, std::function< CompositeProperty* ()>> ACTIVITY_PROPERTIES;

		class AbstractActivityProperty {
		public:
			virtual interpreter::CompositeProperty* getProperty() = 0;
		};
	}
}
Q_DECLARE_METATYPE(shelllet::interpreter::CompositeProperty*)