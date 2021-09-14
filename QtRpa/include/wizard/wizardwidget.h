#pragma once
#include "common.hpp"
#include "frameless.hpp"
namespace shelllet {
	namespace wizard {
		class WizardWidgetPrivate;
		class WizardWidget : public MainWindow
		{
			//Q_DECLARE_PRIVATE(WizardWidget)
	
		public:
			WizardWidget(ResponseHandler * handler, QWidget* parent = nullptr);
		};
	}
}
