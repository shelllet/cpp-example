#pragma once
#include "common/alias.h"
#include "object_p.h"
#ifdef U_NAMESPACE_BEGIN
U_NAMESPACE_BEGIN
#endif // U_NAMESPACE_BEGIN
class UnicodeString;
#ifdef U_NAMESPACE_END
U_NAMESPACE_END
#endif // U_NAMESPACE_END
namespace shelllet {
	namespace common {
		class StringPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(String)
		public:
			UniquePointer<icu::UnicodeString> str;
		};
	}
}
