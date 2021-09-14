#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
        class CursorDatabasePrivate;
        class CursorDatabase : public Object {
            Q_DECLARE_PRIVATE(CursorDatabase)
        public:
            CursorDatabase(Object*parent = nullptr);

			void clear();

			QStringList cursorShapeNames() const;
			QMap<int, QIcon> cursorShapeIcons() const;
			QString cursorToShapeName(const QCursor& cursor) const;
			QIcon cursorToShapeIcon(const QCursor& cursor) const;
			int cursorToValue(const QCursor& cursor) const;
#ifndef QT_NO_CURSOR
			QCursor valueToCursor(int value) const;
#endif
			static CursorDatabase* getInstance();
		private:
			void appendCursor(Qt::CursorShape shape, const QString& name, const QIcon& icon);
			QStringList m_cursorNames;
			QMap<int, QIcon> m_cursorIcons;
			QMap<int, Qt::CursorShape> m_valueToCursorShape;
			QMap<Qt::CursorShape, int> m_cursorShapeToValue;
        protected:
            CursorDatabase(CursorDatabasePrivate& d, Object*parent = nullptr);
        };
    }
}
    