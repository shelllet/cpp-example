#include "common.hpp"
#include <QString>
namespace std {
	std::ostream& operator<< (std::ostream& os, const QString& arr)
	{
		os << arr.toStdString();
		return os;
	}
}