#pragma once
#include <qdialog.h>
#include <QWizardPage>
#include "framework.h"

namespace shelllet {
	namespace wizard {

		class SplashGuide : public QWidget
		{
		public:
			SplashGuide(ResponseHandler* response, QWidget* parent = nullptr);
			~SplashGuide();


		private:
			QWidget* content;
		};
	}
}