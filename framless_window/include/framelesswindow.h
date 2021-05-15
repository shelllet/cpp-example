#pragma once
#include "qmainwindow.h"
#include "common/object.h"
#include "flags.h"
namespace shelllet {
	namespace frameless {
		class FramelessWindowPrivate;
		class FramelessWindow : public QMainWindow, public Object {
			Q_OBJECT
				Q_DECLARE_PRIVATE_D(Object::d_ptr, FramelessWindow)
		public:
			explicit FramelessWindow(QWidget* parent = nullptr, WindowTypeFlags flags = WindowTypeFlags());
			virtual ~FramelessWindow();

			void setCustomButton(QWidget* c);
			void setContextMenu(QMenu* menu);
			void setTitleTextBlurRadius(qreal blurRadius);
			void disableNativeTitleBar();
			void enableNativeTitleBar();

			virtual	SizePolicyFlags fixedSizeTypes() const = 0;
		protected:
			virtual void minimizeButtonClicked();
			virtual void restoreButtonClicked();
			virtual void maximizeButtonClicked();
			virtual void closeButtonClicked();
			virtual void iconDoubleClicked();

			FramelessWindow(FramelessWindowPrivate& d, QWidget* parent = nullptr, WindowTypeFlags flags = WindowTypeFlags());
		protected:
			void paintEvent(QPaintEvent* event) override;
			void changeEvent(QEvent* event) override;
			bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
		};
	}
}
