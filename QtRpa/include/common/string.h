#pragma once
#include <iostream>
//#include <fstream>
#include "object.h"
#include "alias.h"

#include "yaml-cpp/yaml.h"

class QString;
namespace shelllet {
	namespace common {
		class U8StringPrivate;
		class U8String : public Object {
			Q_DECLARE_PRIVATE(U8String)
		public:
			U8String();
			U8String(const U8String& str);
			U8String& append(const char* data, UInt32 n);
			UInt32 length() const;
			UInt32 capacity() const;
			void reserve(UInt32 cap);

			operator const char* () const;
		protected:
			U8String(U8StringPrivate& d);
		};
		class StringPrivate;
		class String : public Object {
			Q_DECLARE_PRIVATE(String)
				friend std::ostream& operator<< (std::ostream&, const String&);

		public:
			String();
			String(const char* str);
			String(const std::string& str);
			String(const String& str);
			String(const std::vector<char>& v);

			String(std::istream& stream);
			//String(std::ifstream& stream);
		public:
			//operator std::string() const;
			String& append(const String& str);
			String& operator =(const String& str);
			String operator +(const String& str) const;
			bool operator ==(const String& str) const;
			bool operator <(const String& str) const;
			std::string toStdString() const;
			std::wstring toStdWString() const;
			QString* toQString() const;
			const char16_t* data() const;
			String clone() const;
			//friend String operator+(const String& lhs, String const& rhs) {
			//	return lhs + rhs;
			//}
			U8String toUtf8()const;

			String subString(std::int32_t start, std::int32_t len = INT32_MAX) const;

			bool isEmpty() const;
			void toLower();
			int toInt() const;
			static String fromQString(const QString* str);
			static String& toLower(String&& str);
			static String toLower(const String& str);
			static String removeNamespace(const String& str);

			static Int32 typeId();

			static bool isEquals(const char* ch1, const char* ch2);
		protected:
			String(StringPrivate& d);

		};


	}
}
W_REGISTER_ARGTYPE(shelllet::common::String)

Q_DECLARE_METATYPE(shelllet::common::String)
//std::ostream& operator<< (std::ostream& out, const shelllet::common::String& data);

static inline YAML::Emitter& operator << (YAML::Emitter& out, const shelllet::common::String& v) {
	out << YAML::DoubleQuoted;
	out << v.toUtf8();
	return out;
}