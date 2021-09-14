#pragma once
#include "qstring.h"
#include "qbytearray.h"
#include "qbuffer.h"
#include "qdatastream.h"
#include "pugixml.hpp"
namespace std {

	std::ostream& operator<< (std::ostream& out, const QString& data);
	std::wostream& operator<< (std::wostream& out, const std::wstring& data);



	std::ostream& operator<< (std::ostream& out, const QStringList& data);
	std::ostream& operator<< (std::ostream& out, const QPoint& data);
	std::ostream& operator<< (std::ostream& out, const QPointF& data);
	std::ostream& operator<< (std::ostream& out, const QSize& data);
	std::ostream& operator<< (std::ostream& out, const QSizeF& data);
	std::ostream& operator<< (std::ostream& out, const QByteArray& data);

	std::ostream& operator<< (std::ostream& out, const QRect& data);
	std::ostream& operator<< (std::ostream& out, const QRectF& data);
	


	std::istream& operator >> (std::istream& in, QString& data);
	std::istream& operator>> (std::istream& in, QStringList& data);


}


namespace shelllet {
	struct XmlByteArrayWriter : pugi::xml_writer
	{
		QByteArray result;

		virtual void write(const void* data, size_t size)
		{
			result.append(static_cast<const char*>(data), size);
		}
	};
}

//Q_DECLARE_METATYPE(std::string)







