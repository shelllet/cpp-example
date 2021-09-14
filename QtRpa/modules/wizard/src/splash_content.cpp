#include "wizard/splash_content.h"
#include "wizard/splash_guide.h"


shelllet::wizard::SplashContentComponent::SplashContentComponent(ResponseHandler* response, QWidget* parent)
	: QWidget(parent)
{
	recent = new RencentComponent(this);
	start = new StartedComponent(response, this);


	auto* h = new QHBoxLayout(this);
	h->addWidget(recent);
	h->addWidget(start);

}

shelllet::wizard::SplashContentComponent::~SplashContentComponent()
{
}