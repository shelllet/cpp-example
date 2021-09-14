#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
        class UtilsPrivate;
        class Utils : public Object {
            Q_DECLARE_PRIVATE(Utils)
        public:
            Utils(Object*parent = nullptr);

			static QPixmap brushValuePixmap(const QBrush& b);
			static QIcon brushValueIcon(const QBrush& b);
			static QString colorValueText(const QColor& c);
			static QPixmap fontValuePixmap(const QFont& f);
			static QIcon fontValueIcon(const QFont& f);
			static QString fontValueText(const QFont& f);
			static QString dateFormat();
			static QString timeFormat();
			static QString dateTimeFormat();
        protected:
            Utils(UtilsPrivate& d, Object*parent = nullptr);
        };
    }
}
    