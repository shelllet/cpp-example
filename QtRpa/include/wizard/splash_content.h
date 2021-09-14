#pragma once
#include <qwidget.h>
#include "recent_component.h"
#include "started_component.h"

namespace shelllet {
	namespace wizard {

		class SplashContentComponent : public QWidget
		{
		public:
			SplashContentComponent(ResponseHandler* response, QWidget* parent = nullptr);
			~SplashContentComponent();

		private:

			RencentComponent* recent;
			StartedComponent* start;
		};
	}
}