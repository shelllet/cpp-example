#pragma once

namespace shelllet {
	namespace error {
		std::string GetLastErrorMessage();
		void SetLastErrorMessage(const std::variant<int, std::string>& err);
	}
}