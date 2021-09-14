#include "unicode/unistr.h"
#include "unicode/ustring.h"
#include "unicode/ustream.h"
#include "common/wobjectdefs.h"
#include "common/string.h"
#include "common/private/string_p.h"
#include "common/const_string.h"
#include "boost/lexical_cast.hpp"
#include "common/logs.h"
namespace shelllet {
	using namespace icu;
	namespace common {
		std::ostream& operator<<(std::ostream& o, const String& data)
		{
			o << data.d_func()->str.operator*();
			return o;
		}


		class U8StringPrivate : public ObjectPrivate {
		public:
			std::string str;
		};
	}
}

shelllet::common::U8String& shelllet::common::U8String::append(const char* data, UInt32 n)
{
	Q_D(U8String);
	d->str.append(data, n);
	return *this;
}

shelllet::common::UInt32 shelllet::common::U8String::length() const
{
	Q_D(const U8String);
	return d->str.length();
}

shelllet::common::UInt32 shelllet::common::U8String::capacity() const
{
	Q_D(const U8String);
	return d->str.capacity();
}

void shelllet::common::U8String::reserve(UInt32 cap)
{
	Q_D(U8String);
	d->str.reserve(cap);
}

shelllet::common::U8String::operator const char* () const
{
	Q_D(const U8String);
	return d->str.c_str();
}

shelllet::common::U8String::U8String()
	: U8String(*new U8StringPrivate)
{

}

shelllet::common::U8String::U8String(const U8String& str)
	: U8String(*new U8StringPrivate)
{
	Q_D(U8String);
	d->str = str.d_func()->str;
}

shelllet::common::U8String::U8String(U8StringPrivate& d)
	: Object(d)
{

}

shelllet::common::String::String(const char* str)
	: String(*new StringPrivate)
{
	Q_D(String);
	d->str->setTo(str);
}



shelllet::common::String& shelllet::common::String::append(const String& str)
{
	Q_D(String);
	d->str->append(str.d_func()->str.operator*());
	return *this;
}

bool shelllet::common::String::operator==(const String& str) const
{
	Q_D(const String);
	return d->str == str.d_func()->str;
}

shelllet::common::String shelllet::common::String::operator+(const String& str) const
{
	Q_D(const String);

	return std::move(clone().append(str));
}

bool shelllet::common::String::operator<(const String& str) const
{
	Q_D(const String);
	return d->str < str.d_func()->str;
}

std::string shelllet::common::String::toStdString() const
{
	Q_D(const String);
	std::string result;
	return std::move(d->str->toUTF8String(result));
}


std::wstring shelllet::common::String::toStdWString() const
{
	Q_D(const String);
	std::wstring wstr;

	int32_t requiredSize;
	UErrorCode error = U_ZERO_ERROR;

	// obtain the size of string we need
	u_strToWCS(nullptr, 0, &requiredSize, d->str->getBuffer(), d->str->length(), &error);

	// resize accordingly (this will not include any terminating null character, but it also doesn't need to either)
	wstr.resize(requiredSize);
	error = U_ZERO_ERROR;

	// copy the UnicodeString buffer to the std::wstring.
	u_strToWCS(wstr.data(), wstr.size(), nullptr, d->str->getBuffer(), d->str->length(), &error);

	return wstr;
}

QString* shelllet::common::String::toQString() const
{
	Q_D(const String);
	static QString str;
	str = QString::fromStdString(toStdString());
	return &str;
}

const char16_t* shelllet::common::String::data() const
{
	Q_D(const String);
	return d->str->getBuffer();
}

shelllet::common::String shelllet::common::String::clone() const
{
	Q_D(const String);
	String temp;
	temp.d_func()->str->setTo(*d->str->clone());
	return std::move(temp);
}

shelllet::common::U8String shelllet::common::String::toUtf8() const
{
	Q_D(const String);
	U8String temp;
	d->str->toUTF8String(temp);
	return temp;
}



shelllet::common::String shelllet::common::String::subString(int32_t start, std::int32_t len) const
{
	Q_D(const String);
	String temp;
	temp.d_func()->str->setTo(d->str->tempSubString(start, len));
	return temp;
}

shelllet::common::String shelllet::common::String::fromQString(const QString* str)
{
	return std::move(String(str->toStdString()));
}

void shelllet::common::String::toLower()
{
	Q_D(String);
	d->str->toLower();
}

int shelllet::common::String::toInt() const
{
	Q_D(const String);
	return	boost::lexical_cast<int>(toUtf8());
}

shelllet::common::String shelllet::common::String::removeNamespace(const String& str)
{

	auto pos = str.d_func()->str->lastIndexOf("::");
	if (pos == -1)
		return str;

	String temp;
	temp.d_func()->str->setTo(str.d_func()->str->tempSubString(pos + 2));

	return std::move(temp);
}

shelllet::common::Int32 shelllet::common::String::typeId()
{
	return qRegisterMetaType<String>();
}

bool shelllet::common::String::isEquals(const char* ch1, const char* ch2)
{
	return std::strcmp(ch1, ch2) == 0;
}

shelllet::common::String shelllet::common::String::toLower(const String& str)
{
	auto temp = const_cast<String*>(&str);
	temp->toLower();
	return std::move(*temp);
}

shelllet::common::String& shelllet::common::String::toLower(String&& str)
{
	str.toLower();
	return str;
}

shelllet::common::String::String(const std::vector<char>& v)
	: String(*new StringPrivate)
{
	Q_D(String);
	d->str->setTo(UnicodeString::fromUTF8(std::string(v.begin(), v.end())));
}

shelllet::common::String::String(const String& str)
	: String(*new StringPrivate)
{
	Q_D(String);
	d->str->setTo(str.d_func()->str.operator*());
}

shelllet::common::String::String()
	: String(*new StringPrivate)
{

}

shelllet::common::String::String(std::istream& stream)
	: String(*new StringPrivate)
{
	Q_D(String);
	d->str->setTo(UnicodeString::fromUTF8(std::string{ std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() }));
}
//shelllet::common::String::String(std::ifstream& stream)
//	: Object(*new StringPrivate, nullptr)
//{
//	Q_D(String);
//	d->str = { std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };
//}
shelllet::common::String::String(const std::string& str)
	: String(*new StringPrivate)
{
	Q_D(String);
	d->str->setTo(UnicodeString::fromUTF8(str));
}

shelllet::common::String::String(StringPrivate& d)
	: Object(d, nullptr)
{
	d.str = std::make_unique<icu::UnicodeString>();

	if (!QMetaType::isRegistered(QMetaType::type(QUOTED(String)))) {
		qRegisterMetaType<String>(QUOTED(String));
	}
}

//shelllet::common::String::operator std::string() const
//{
//	Q_D(const String);
//	std::string result;
//	return std::move(d->str->toUTF8String(result));
//}

shelllet::common::String& shelllet::common::String::operator=(const String& str)
{
	Q_D(String);
	d->str->setTo(str.d_func()->str.operator*());

	return *this;
}


