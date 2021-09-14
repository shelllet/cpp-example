#pragma once
#include <qdialog.h>
#include <QWizardPage>
#include <QStackedWidget>
#include "framework.h"
#include "common.hpp"
#define DECLARE_PRIVATE_OBJECT(name) extern name##Private* dx_;
#define DECLARE_PRIVATE_CLASS(name) class name##Private;
#define IMPLEMENT_PRIVATE_CLASS(name) name##Private* dx_ = new name##Private;
#define FREE_PRIVATE_OBJECT delete dx_;

namespace shelllet {
	namespace wizard {

		DECLARE_PRIVATE_CLASS(WizardPage)
		DECLARE_PRIVATE_OBJECT(WizardPage)
		class WizardPage :public QWizardPage
		{
			Q_DECLARE_PRIVATE_D(dx_, WizardPage)
		public:
			WizardPage(QWidget* parent = nullptr);
			~WizardPage();

		public:


		};
	}
}