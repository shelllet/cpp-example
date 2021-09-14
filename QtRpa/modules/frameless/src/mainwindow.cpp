#include "frameless/mainwindow.h"
#include "qapplication.h"
#include "qstyle.h"
#include "qdesktopwidget.h"
#include "frameless/private/mainwindow_p.h"
namespace shelllet {


}

shelllet::frameless::MainWindow::MainWindow(QWidget* parent /*= nullptr*/, WindowTypeFlags flags /*= WindowFlags()*/)
	: MainWindow(*new MainWindowPrivate, parent, flags)
{
}

void shelllet::frameless::MainWindow::moveToCentral()
{
	//	Q_D(FramelessWindow);
		//QSize size = QApplication::primaryScreen()->availableSize() * 0.5;

	LOG_DEBUG(PROJECT_NAME) << "# geometry size: " << geometry() << std::endl;
	setGeometry(QStyle::alignedRect(
		Qt::LeftToRight,
		Qt::AlignCenter,
		geometry().size(),
		qApp->desktop()->availableGeometry())); ;
}

void shelllet::frameless::MainWindow::setFixedHeight(int h)
{

	Q_D(MainWindow);
	d->fixedSize = SizePolicy::FixedHeigth;
	__super::setFixedHeight(h);
}

void shelllet::frameless::MainWindow::setFixedWidth(int w)
{

	Q_D(MainWindow);
	d->fixedSize = SizePolicy::FixedWidth;
	__super::setFixedWidth(w);
}

void shelllet::frameless::MainWindow::setFixedSize(const QSize& s)
{

	Q_D(MainWindow);
	d->fixedSize = SizePolicy::FixedAll;
	__super::setFixedSize(s);
}

shelllet::frameless::SizePolicyFlags shelllet::frameless::MainWindow::fixedSizeTypes() const
{
	Q_D(const MainWindow);

	return d->fixedSize;
}

shelllet::frameless::MainWindow::MainWindow(MainWindowPrivate& d, QWidget* parent /*= nullptr*/, WindowTypeFlags flags /*= WindowFlags()*/)
	: FramelessWindow(d, parent, flags)
{

}

void shelllet::frameless::MainWindow::setFixedSize(int w, int h)
{
	Q_D(MainWindow);
	d->fixedSize = SizePolicy::FixedAll;
	__super::setFixedSize(w, h);
}
