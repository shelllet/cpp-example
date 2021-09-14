#pragma once
#include "common.hpp"
#include "qsvgwidget.h"
namespace shelllet {
	namespace frameless {
		enum class ButtonType {
			Close,
			Minimize,
			Maximize,
			Restore
		};
		class StandardButtonPrivate;
		class StandardButton : public QSvgWidget, public Object {
			Q_DECLARE_PRIVATE_D(Object::d_ptr, StandardButton)
				Q_OBJECT
		public:
			StandardButton(ButtonType t, QWidget* parent = nullptr);


		signals:
			void clicked();
		protected slots:
			void applicationStateChanged(Qt::ApplicationState state);
		protected:
			void paintEvent(QPaintEvent* event);

			void mousePressEvent(QMouseEvent* event) override;

			void enterEvent(QEvent* event) override;

			void leaveEvent(QEvent* event) override;

			void mouseReleaseEvent(QMouseEvent* event) override;

			QSize sizeHint() const override;
		};

	}
}