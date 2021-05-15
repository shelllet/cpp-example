#include "framework.h"
#include "error.h"

namespace shelllet {
	thread_local std::string glErrorMessage;
}
std::string shelllet::error::GetLastErrorMessage()
{
	return glErrorMessage;
}

void shelllet::error::SetLastErrorMessage(const std::variant<int, std::string>& err)
{
	if (std::holds_alternative<int>(err)) {
		glErrorMessage = std::system_category().message(std::get<int>(err));
	}
	else if (std::holds_alternative<std::string>(err)) {
		glErrorMessage = std::get<std::string>(err);
	}
}