#include "property/framework.h"
#include "qcursor.h"
#include "qglobalstatic.h"
#include "qcoreapplication.h"
#include "property/cursordatabase.h"
#include "property/private/cursordatabase_p.h"

namespace shelllet{
    namespace property{
        

		Q_GLOBAL_STATIC(CursorDatabase, cursorDatabase)

    }
}
using namespace shelllet::property;
CursorDatabase::CursorDatabase(Object* parent /*= nullptr*/)
    :CursorDatabase(*new CursorDatabasePrivate, parent)
{

}
CursorDatabase::CursorDatabase(CursorDatabasePrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{
	appendCursor(Qt::ArrowCursor, QCoreApplication::translate("CursorDatabase", "Arrow"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-arrow.png")));
	appendCursor(Qt::UpArrowCursor, QCoreApplication::translate("CursorDatabase", "Up Arrow"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-uparrow.png")));
	appendCursor(Qt::CrossCursor, QCoreApplication::translate("CursorDatabase", "Cross"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-cross.png")));
	appendCursor(Qt::WaitCursor, QCoreApplication::translate("CursorDatabase", "Wait"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-wait.png")));
	appendCursor(Qt::IBeamCursor, QCoreApplication::translate("CursorDatabase", "IBeam"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-ibeam.png")));
	appendCursor(Qt::SizeVerCursor, QCoreApplication::translate("CursorDatabase", "Size Vertical"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizev.png")));
	appendCursor(Qt::SizeHorCursor, QCoreApplication::translate("CursorDatabase", "Size Horizontal"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeh.png")));
	appendCursor(Qt::SizeFDiagCursor, QCoreApplication::translate("CursorDatabase", "Size Backslash"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizef.png")));
	appendCursor(Qt::SizeBDiagCursor, QCoreApplication::translate("CursorDatabase", "Size Slash"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeb.png")));
	appendCursor(Qt::SizeAllCursor, QCoreApplication::translate("CursorDatabase", "Size All"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeall.png")));
	appendCursor(Qt::BlankCursor, QCoreApplication::translate("CursorDatabase", "Blank"),
		QIcon());
	appendCursor(Qt::SplitVCursor, QCoreApplication::translate("CursorDatabase", "Split Vertical"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-vsplit.png")));
	appendCursor(Qt::SplitHCursor, QCoreApplication::translate("CursorDatabase", "Split Horizontal"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hsplit.png")));
	appendCursor(Qt::PointingHandCursor, QCoreApplication::translate("CursorDatabase", "Pointing Hand"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hand.png")));
	appendCursor(Qt::ForbiddenCursor, QCoreApplication::translate("CursorDatabase", "Forbidden"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-forbidden.png")));
	appendCursor(Qt::OpenHandCursor, QCoreApplication::translate("CursorDatabase", "Open Hand"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-openhand.png")));
	appendCursor(Qt::ClosedHandCursor, QCoreApplication::translate("CursorDatabase", "Closed Hand"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-closedhand.png")));
	appendCursor(Qt::WhatsThisCursor, QCoreApplication::translate("CursorDatabase", "What's This"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-whatsthis.png")));
	appendCursor(Qt::BusyCursor, QCoreApplication::translate("CursorDatabase", "Busy"),
		QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-busy.png")));
}

CursorDatabase* CursorDatabase::getInstance()
{
	return cursorDatabase;
}


void CursorDatabase::clear()
{
	m_cursorNames.clear();
	m_cursorIcons.clear();
	m_valueToCursorShape.clear();
	m_cursorShapeToValue.clear();
}

void CursorDatabase::appendCursor(Qt::CursorShape shape, const QString& name, const QIcon& icon)
{
	if (m_cursorShapeToValue.contains(shape))
		return;
	const int value = m_cursorNames.count();
	m_cursorNames.append(name);
	m_cursorIcons.insert(value, icon);
	m_valueToCursorShape.insert(value, shape);
	m_cursorShapeToValue.insert(shape, value);
}

QStringList CursorDatabase::cursorShapeNames() const
{
	return m_cursorNames;
}

QMap<int, QIcon> CursorDatabase::cursorShapeIcons() const
{
	return m_cursorIcons;
}

QString CursorDatabase::cursorToShapeName(const QCursor& cursor) const
{
	int val = cursorToValue(cursor);
	if (val >= 0)
		return m_cursorNames.at(val);
	return QString();
}

QIcon CursorDatabase::cursorToShapeIcon(const QCursor& cursor) const
{
	int val = cursorToValue(cursor);
	return m_cursorIcons.value(val);
}

int CursorDatabase::cursorToValue(const QCursor& cursor) const
{
#ifndef QT_NO_CURSOR
	Qt::CursorShape shape = cursor.shape();
	if (m_cursorShapeToValue.contains(shape))
		return m_cursorShapeToValue[shape];
#endif
	return -1;
}

#ifndef QT_NO_CURSOR
QCursor CursorDatabase::valueToCursor(int value) const
{
	if (m_valueToCursorShape.contains(value))
		return QCursor(m_valueToCursorShape[value]);
	return QCursor();
}
#endif
