#pragma once
#include <qdialog.h>
#include <QWizardPage>
#include <QStackedWidget>
#include <QComboBox>
#include "framework.h"

namespace shelllet {
	namespace wizard {


		class CreatePage : public QWizardPage
		{
		public:
			CreatePage(QWidget* parent = nullptr);
			~CreatePage();

		public:

		protected:

		
		private:
			QStackedWidget* widget_;
			QLineEdit* lineEdit_;
			QComboBox* comboBox_;

		};
	}
}