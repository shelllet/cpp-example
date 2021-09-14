#include "db.h"

shelllet::database::Sqlite::Sqlite()
{
	const QString DRIVER("QSQLITE");
	if (QSqlDatabase::isDriverAvailable(DRIVER)) {
		QSqlDatabase::addDatabase(DRIVER);
	}
}
