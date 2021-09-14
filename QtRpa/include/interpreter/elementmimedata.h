#pragma once
#include "common.hpp"
namespace shelllet {
	namespace interpreter {
		class Element;
		class ElementMimeDataPrivate;
		class ElementMimeData : public MimeData
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, ElementMimeData)
		public:
			ElementMimeData();

			void setElementItem(Element* item);

			Element* elementItem()const;
		private:

		};

	}
}