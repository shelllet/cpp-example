#pragma once
#include <qsqldatabase.h>
namespace shelllet::database {
	class Sqlite {
	public:
		Sqlite();
	};

	Q_GLOBAL_STATIC(Sqlite, GlobalSqlite)
}