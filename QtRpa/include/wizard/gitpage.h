#pragma once
#include <qdialog.h>
#include <QWizardPage>
#include <QStackedWidget>
#include <QComboBox>
#include "framework.h"

namespace shelllet {
	namespace wizard {
		class GitPage : public QWizardPage
		{
		public:
			GitPage(QWidget* parent = nullptr);
			~GitPage();

		public:

		protected:


		private:
			QStackedWidget* widget_;
			QLineEdit* lineEdit_;
			QComboBox* comboBox_;

		};
	}
}