#pragma once

namespace shelllet {
#define STR(str) #str
#define QUOTED(str) #str

	static inline const char K_CONST_MARK_UNKNOWN[] = "unknown";
	static inline const char K_CONST_ERROR_CALLED[] = "# invalid object.";
	static inline const char K_CONST_ERROR_NULL_PTR[] = "# this null.";
	static inline const char K_CONST_ERROR_INVLAID_PARAM[] = "# invalid param.";
}