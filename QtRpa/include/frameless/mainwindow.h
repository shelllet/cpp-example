#pragma once
#include "framelesswindow.h"

namespace shelllet {
	namespace frameless {
		class MainWindowPrivate;
		class MainWindow : public FramelessWindow {
			Q_DECLARE_PRIVATE_D(Object::d_ptr, MainWindow)
		public:
			MainWindow(QWidget* parent = nullptr, WindowTypeFlags flags = WindowTypeFlags());


			void moveToCentral();

			void setFixedHeight(int h);
			void setFixedWidth(int w);
			void setFixedSize(int w, int h);
			void setFixedSize(const QSize& s);

			SizePolicyFlags fixedSizeTypes() const override;

		protected:
			MainWindow(MainWindowPrivate&d, QWidget* parent = nullptr, WindowTypeFlags flags = WindowTypeFlags());
		};
	}
}
