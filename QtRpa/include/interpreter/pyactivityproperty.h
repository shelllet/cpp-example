#pragma once
#include "object.h"
namespace shelllet {
    namespace interpreter{
        class PyActivityPropertyPrivate;
        class PyActivityProperty : public CompositeProperty {
            Q_DECLARE_PRIVATE(PyActivityProperty)
            public:
            PyActivityProperty(const XmlNode& node);

            std::shared_ptr<XmlDocument> getNode() override;


            void exec() override;
            static void embedded(py::module_& m);

            static void importModule();
        protected:
            PyActivityProperty(PyActivityPropertyPrivate& d, const XmlNode&node);

            virtual property::PropertySheet* getInput(property::PropertyBrowser*) override;

			virtual property::PropertySheet* getOutput(property::PropertyBrowser*) override;

        };
    }
}
    