#include <qboxlayout.h>
#include <qvariant.h>
#include "wizard/started_component.h"
#include "events.hpp"
#include "private/qwidget_p.h"
namespace shelllet {
	namespace wizard {
		class Ui_StartedComponent {
		public:
			QLabel* title;

			QCommandLinkButton* git;
			QCommandLinkButton* open;
			QCommandLinkButton* create;
			QVBoxLayout* layout;
			void setupUi(StartedComponent* parent) {
				git = new QCommandLinkButton(parent);
				open = new QCommandLinkButton(parent);
				create = new QCommandLinkButton(parent);
				title = new QLabel(parent);


				layout = new QVBoxLayout(parent);

				title->setText(QObject::tr("Start"));

				layout->addWidget(title);

				git->setText("Clone or checkout Code");
				layout->addWidget(git);

				open->setText("Open project file");
				layout->addWidget(open);

				create->setText("Create new project file");
				layout->addWidget(create);
			}
		};
		class StartedComponentPrivate : public QWidgetPrivate {
		public:
			Ui_StartedComponent ui;

			ResponseHandler* response;
		};
	}
}

shelllet::wizard::StartedComponent::StartedComponent(ResponseHandler* response, QWidget* parent)
	: QWidget(*new StartedComponentPrivate, parent, {})

{
	Q_D(StartedComponent);
	d->response = response;
	d->ui.setupUi(this);
	connect(d->ui.create, &QPushButton::clicked, this, &StartedComponent::buttonClicked);
	connect(d->ui.git, &QPushButton::clicked, this, &StartedComponent::buttonClicked);
	connect(d->ui.open, &QPushButton::clicked, this, &StartedComponent::buttonClicked);
}

shelllet::wizard::StartedComponent::~StartedComponent()
{
}

void shelllet::wizard::StartedComponent::buttonClicked()
{
	Q_D(StartedComponent);
	QCommandLinkButton* button = dynamic_cast<QCommandLinkButton*>(sender());

	if (button == d->ui.create) {
		//QCoreApplication::postEvent(EventDispatcher::Dispatcher(), new CreateSelectEvent);
		d->response->finshed(ResponseHandler::Exit::Create);
	}
	else if (button == d->ui.git) {
		//QCoreApplication::postEvent(EventDispatcher::Dispatcher(), new GitCloneEvent);
		d->response->finshed(ResponseHandler::Exit::FromGit);
	}
	else if (button == d->ui.open) {
		//QCoreApplication::postEvent(EventDispatcher::Dispatcher(), new OpenSelectEvent);
		//QCoreApplication::postEvent(this, new CloseEvent(3));
		d->response->finshed(ResponseHandler::Exit::Open);
	}

	
}

