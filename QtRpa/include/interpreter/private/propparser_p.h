#pragma once
#include "common.hpp"
namespace shelllet {
    namespace interpreter{
		class PropParserPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(PropParser)
		public:

			py::object ooo;
		};
    }
}
    