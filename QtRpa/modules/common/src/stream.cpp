#include "common.hpp"

namespace std {
	template<typename T>
	T&& operator-(T&& t) { return std::forward<T>(t); }

	template<typename T>
	std::ostream& operator<(std::ostream& out, const T& data)
	{
		QString message;
		QDebug debug(&message);
		debug << data;
		out << message;
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const QString& data)
	{
		std::string s = data.toUtf8().constData();
		out << data.toUtf8().constData();
		return out;
	}
	std::wostream& operator<<(wostream& out, const wstring& data)
	{
		out << data;
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const QStringList& data)
	{
		QByteArray bytes;
		{
			QBuffer buffer(&bytes);
			buffer.open(QIODevice::WriteOnly);
			QDataStream stream(&buffer);
			stream << data;
			out << bytes.constData();
		}
		return out;
	}

	/*std::ostream& operator<<(ostream& out, const pugi::xml_node& node)
	{
		node.print(out);
		return out;
	}*/

	std::ostream& operator<<(ostream& out, const QPoint& data)
	{
		out << "(" << data.x() << ", " << data.y() << ")";
		return out;
	}

	std::ostream& operator<<(ostream& out, const QSizeF& data)
	{
		out << "(" << data.width() << ", " << data.height() << ")";
		return out;
	}

	std::ostream& operator<<(ostream& out, const QSize& data)
	{
		out << "(" << data.width() << ", " << data.height() << ")";
		return out;
	}

	std::ostream& operator<<(ostream& out, const QPointF& data)
	{
		out << "(" << data.x() << ", " << data.y() << ")";
		return out;
	}

	std::ostream& operator<<(ostream& out, const QRectF& data)
	{
		QByteArray bytes;
		{
			QBuffer buffer(&bytes);
			buffer.open(QIODevice::WriteOnly);
			QDataStream stream(&buffer);
			stream << data;
		}
		out << bytes.constData();
		out < -data;
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const QRect& data)
	{
		/*	QByteArray bytes;
			{
				QBuffer buffer(&bytes);
				buffer.open(QIODevice::WriteOnly);
				QDataStream stream(&buffer);
				stream << data;
			}*/
		out < -data;
		return out;
	}

	/*std::ostream& operator<<(ostream& out, const pugi::xml_document& doc)
	{
		doc.print(out);
		return out;
	}*/

	std::ostream& operator<<(ostream& out, const QByteArray& data)
	{
		out < -data;
		return out;
	}

	

	std::istream& operator>>(std::istream& in, QString& data)
	{
		std::string temp;
		in >> temp;
		data = QString::fromStdString(temp);
		return in;
	}

	std::istream& operator>>(std::istream& in, QStringList& data)
	{
		std::string temp;
		in >> temp;
		QBuffer buffer;
		buffer.setData(temp.c_str(), static_cast<int>(temp.size()));
		buffer.open(QIODevice::ReadOnly);
		QDataStream stream(&buffer);
		stream >> data;
		return in;
	}

}