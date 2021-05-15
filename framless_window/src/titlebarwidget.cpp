#include "titlebarwidget.h"
#include "qpainter.h"
#include "qstyleoption.h"
#include "private/qwidget_p.h"
#include "qlabel.h"
#include "qtoolbutton.h"
#include "qapplication.h"
#include "qstackedwidget.h"
#include "standardbutton.h"
#include "qboxlayout.h"
#include <boost/core/ignore_unused.hpp>
namespace shelllet {
	namespace frameless {
		class IconButton : public QLabel {
		public:
			IconButton(const std::function<void()>& doubleClicked, QWidget* parent) : QLabel(parent), doubleClicked(doubleClicked) {
			}

		protected:
			void mouseDoubleClickEvent(QMouseEvent* /*event*/) override
			{
				if (doubleClicked)
					doubleClicked();
			}

		private:
			std::function<void()> doubleClicked;
		};

		class TitleBarWidgetPrivate : public QWidgetPrivate {
		public:
			IconButton* icon;
			QLabel* titleText;
			StandardButton* minimizeButton;
			StandardButton* restoreButton;
			StandardButton* maximizeButton;
			StandardButton* closeButton;
			QStackedWidget* customButton;
			QHBoxLayout* horizontalLayout;
			const float factor = 0.8;
			void setupUi(TitleBarWidget* parent) {
				parent->setObjectName("window-title-bar");
				horizontalLayout = new QHBoxLayout(parent);
				horizontalLayout->setSpacing(0);
				horizontalLayout->setContentsMargins(0, 0, 0, 0);
				horizontalLayout->addSpacing(2);

				icon = new IconButton([parent]() { parent->iconDoubleClicked(); }, parent);
				auto extent = static_cast<int>(parent->geometry().height() * factor);
				icon->setPixmap(qApp->windowIcon().pixmap(extent));
				icon->setContextMenuPolicy(Qt::NoContextMenu);

				horizontalLayout->addWidget(icon);
				horizontalLayout->addSpacing(1);

				titleText = new QLabel(parent);
				titleText->setObjectName("window-title-label");
				titleText->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
				titleText->setContextMenuPolicy(Qt::CustomContextMenu);


				titleText->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
				horizontalLayout->addWidget(titleText);

				horizontalLayout->addSpacing(9);
				customButton = new QStackedWidget(parent);
				horizontalLayout->addWidget(customButton);

				minimizeButton = new StandardButton(ButtonType::Minimize, parent);
				minimizeButton->setFixedWidth(45);
				horizontalLayout->addWidget(minimizeButton);

				restoreButton = new StandardButton(ButtonType::Restore, parent);
				restoreButton->setFixedWidth(45);
				horizontalLayout->addWidget(restoreButton);
				restoreButton->setStyleSheet("background-color: #3a3a3a");

				maximizeButton = new StandardButton(ButtonType::Maximize, parent);
				maximizeButton->setFixedWidth(45);
				horizontalLayout->addWidget(maximizeButton);
				maximizeButton->setStyleSheet("background-color: #3a3a3a");
				closeButton = new StandardButton(ButtonType::Close, parent);
				closeButton->setFixedWidth(45);
				horizontalLayout->addWidget(closeButton);
			}
		};
	}
}
shelllet::frameless::TitleBarWidget::TitleBarWidget(QWidget* parent /*= nullptr*/, WindowTypeFlags f /*= WindowTypes()*/)
	: QWidget(*new TitleBarWidgetPrivate, parent, {}) {
	Q_D(TitleBarWidget);
	d->setupUi(this);

	

	d->restoreButton->setVisible(false);
	connect(this, &TitleBarWidget::windowTitleChanged, [d](const QString& title) {d->titleText->setText(title); });
	connect(this, &TitleBarWidget::windowIconChanged, [this, d](const QIcon& icon) {d->icon->setPixmap(icon.pixmap(static_cast<int>(geometry().height() * d->factor))); });

	connect(d->closeButton, SIGNAL(clicked()), this, SIGNAL(closeButtonClicked()));
	connect(d->minimizeButton, SIGNAL(clicked()), this, SIGNAL(minimizeButtonClicked()));
	connect(d->maximizeButton, SIGNAL(clicked()), this, SIGNAL(maximizeButtonClicked()));
	connect(d->restoreButton, SIGNAL(clicked()), this, SIGNAL(restoreButtonClicked()));
	QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, &TitleBarWidget::applicationStateChanged);
}

void shelllet::frameless::TitleBarWidget::applicationStateChanged(Qt::ApplicationState state)
{
	Q_D(TitleBarWidget);

	if (state == Qt::ApplicationActive) {
		d->titleText->setStyleSheet("color: rgb(240, 240, 240)");
	}
	else {
		d->titleText->setStyleSheet("color: rgb(200, 200, 200)");
	}
}

void shelllet::frameless::TitleBarWidget::setWindowTypes(WindowTypeFlags f)
{
	Q_D(TitleBarWidget);
	if (!f.testFlag(WindowType::CloseButtonHint)) {
		d->closeButton->hide();
	}
	if (!f.testFlag(WindowType::MinimizeButtonHint)) {
		d->minimizeButton->hide();
	}
	if (!f.testFlag(WindowType::MaximizeButtonHint)) {
		d->maximizeButton->hide();
	}
}

void shelllet::frameless::TitleBarWidget::setCustomButton(QWidget* c)
{
	Q_D(TitleBarWidget);
	auto* widget = d->customButton->currentWidget();
	if (widget) {
		d->customButton->removeWidget(widget);
		widget->deleteLater();
	}
	d->customButton->addWidget(c);
}

bool shelllet::frameless::TitleBarWidget::underMouse()
{
	Q_D(TitleBarWidget);
	QWidget* action = QApplication::widgetAt(QCursor::pos());
	if (action == this || action == d->titleText || action == d->customButton) {
		return true;
	}
	return false;
}

void shelllet::frameless::TitleBarWidget::switchToMaxButton()
{
	Q_D(TitleBarWidget);
	d->restoreButton->setVisible(false);
	d->maximizeButton->setVisible(true);
}

void shelllet::frameless::TitleBarWidget::switchToRestoreButton()
{
	Q_D(TitleBarWidget);
	d->restoreButton->setVisible(true);
	d->maximizeButton->setVisible(false);
}

void shelllet::frameless::TitleBarWidget::setTitleTextBlurRadius(qreal blurRadius)
{
	Q_D(TitleBarWidget);
	QGraphicsDropShadowEffect* textShadow = new QGraphicsDropShadowEffect;
	textShadow->setBlurRadius(blurRadius);
	textShadow->setColor(QColor(0, 0, 0));
	textShadow->setOffset(.0f);
	d->titleText->setGraphicsEffect(textShadow);
}

void shelllet::frameless::TitleBarWidget::paintEvent(QPaintEvent* event) {
	boost::ignore_unused(event);
	QStyleOption styleOption;
	styleOption.initFrom(this);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}

void shelllet::frameless::TitleBarWidget::resizeEvent(QResizeEvent* event)
{
	//throw std::logic_error("The method or operation is not implemented.");
	Q_D(TitleBarWidget);
	auto extent = static_cast<int>(event->size().height() * d->factor);
	d->icon->setPixmap(qApp->windowIcon().pixmap(extent));
}

