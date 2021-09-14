#pragma once
#include "composite_property.h"

namespace shelllet {
	namespace interpreter {
		class SequencePrivate;
		class Sequence : public CompositeProperty
		{
			Q_OBJECT
				Q_DECLARE_PRIVATE(Sequence)
		public:
			Q_INVOKABLE Sequence(const XmlNode& node = {}, QObject* parent = nullptr);


			//std::unique_ptr<pugi::xml_document> getNode() override;

			void getCode(std::ostringstream& oss) override;



			//std::string getImport() const override;

		};
	}
}

Q_DECLARE_METATYPE(shelllet::interpreter::Sequence*)
