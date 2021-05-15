#pragma once
#include "qwidget.h"
#include "qevent.h"
#include "flags.h"
namespace shelllet {
	namespace frameless {
		class TitleBarWidgetPrivate;
		class TitleBarWidget : public QWidget {
			Q_OBJECT
				Q_DECLARE_PRIVATE(TitleBarWidget)
		public:
			explicit TitleBarWidget(QWidget* parent = nullptr, WindowTypeFlags f = WindowTypeFlags());
			virtual ~TitleBarWidget() {}

			void applicationStateChanged(Qt::ApplicationState state);
			void setWindowTypes(WindowTypeFlags f);

			void setCustomButton(QWidget* c);

			bool underMouse();
	
			void switchToMaxButton();
			void switchToRestoreButton();
			void setTitleTextBlurRadius(qreal blurRadius);
		signals:
			void minimizeButtonClicked();
			void restoreButtonClicked();
			void maximizeButtonClicked();
			void closeButtonClicked();
			void iconDoubleClicked();
		protected:
			void paintEvent(QPaintEvent* event);
			void resizeEvent(QResizeEvent* event);
		};

	}
}
