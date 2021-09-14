#pragma once
#include "qmimedata.h"
#include "object.h"
namespace shelllet {
	namespace common {
		class MimeDataPrivate;
		class MimeData : public QMimeData, public Object
		{
			Q_DECLARE_PRIVATE_D(Object::d_ptr, MimeData)

		protected:
			MimeData(MimeDataPrivate&);
		private:

		};


	}
}