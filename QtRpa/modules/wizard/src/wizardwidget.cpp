#include "wizard/framework.h"
#include "wizard/wizardwidget.h"
#include "wizard/splash_guide.h"
#include "frameless.hpp"
#include "qapplication.h"
#include "qscreen.h"
#include "qstyle.h"
#include "qdesktopwidget.h"
#include "private/qobject_p.h"
#include "events.hpp"
namespace shelllet {
	namespace wizard {
		class WizardWidgetPrivate : public QObjectPrivate {
		public:
			//std::unique_ptr<FramelessWindow> framelessWindow;
		};
	}
}

shelllet::wizard::WizardWidget::WizardWidget(ResponseHandler* handler, QWidget* parent /*= nullptr*/)
	: MainWindow(parent, WindowType::CloseButtonHint)
{
	//Q_D(WizardWidget);
	setWindowTitle("Visual Studio 2020");
	setCentralWidget(new SplashGuide(handler));
	setWindowModality(Qt::ApplicationModal);

	setFixedSize(QApplication::primaryScreen()->availableSize() * 0.5);
}




