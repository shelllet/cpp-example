#pragma once
#include "qwidget.h"
class QCheckBox;
namespace shelllet {
    namespace property{
        class BoolEditPrivate;
        class BoolEdit : public QWidget {
            Q_DECLARE_PRIVATE(BoolEdit)
        public:
            BoolEdit(Object*parent = nullptr);
			Q_OBJECT
		public:
			BoolEdit(QWidget* parent = 0);

			bool textVisible() const { return m_textVisible; }
			void setTextVisible(bool textVisible);

			Qt::CheckState checkState() const;
			void setCheckState(Qt::CheckState state);

			bool isChecked() const;
			void setChecked(bool c);

			bool blockCheckBoxSignals(bool block);

		Q_SIGNALS:
			void toggled(bool);

		protected:
			void mousePressEvent(QMouseEvent* event);

		private:
			QCheckBox* m_checkBox;
			bool m_textVisible;
        protected:
            BoolEdit(BoolEditPrivate& d, QWidget*parent = nullptr);

        };
    }
}
    