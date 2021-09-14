#pragma once
#include <qcommandlinkbutton.h>
#include <qlabel.h>
#include "wizard/framework.h"

namespace shelllet {
	namespace wizard {
		class StartedComponentPrivate;
		class StartedComponent : public QWidget
		{
			Q_DECLARE_PRIVATE(StartedComponent)
		public:
			StartedComponent(ResponseHandler* response, QWidget* parent = nullptr);
			~StartedComponent();

		protected:
			void buttonClicked();
		};
	}
}