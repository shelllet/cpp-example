#include <qcoreapplication.h>
#include "wizard/splash_guide.h"
#include "wizard/splash_content.h"
#include "wizard/framework.h"
shelllet::wizard::SplashGuide::SplashGuide(ResponseHandler* response, QWidget* parent)
	: QWidget(parent)
{
	auto* layout = new QVBoxLayout(this);
	content = new SplashContentComponent(response,this);
	layout->addWidget(content);
}

shelllet::wizard::SplashGuide::~SplashGuide()
{
}
