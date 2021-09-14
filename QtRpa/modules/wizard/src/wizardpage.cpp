#include "qcoreapplication.h"
#include "qcoreapplication.h"
#include "qboxlayout.h"
#include "wizard/wizardpage.h"
#include "private/qwidget_p.h"
#include "common/private/object_p.h"
namespace shelllet {
	namespace wizard {
		class WizardPagePrivate : public ObjectPrivate {
		public:
			QStackedWidget* stackedWidget_;

		};
		IMPLEMENT_PRIVATE_CLASS(WizardPage)
	}
}
shelllet::wizard::WizardPage::WizardPage(QWidget* parent)
	: QWizardPage(parent)
{
	Q_D(WizardPage);
	setLayout(new QVBoxLayout);
	d->stackedWidget_ = new QStackedWidget(this);

	//d->stackedWidget_->addWidget(new GitPage);
	layout()->addWidget(d->stackedWidget_);
}

shelllet::wizard::WizardPage::~WizardPage()
{
	FREE_PRIVATE_OBJECT
}

