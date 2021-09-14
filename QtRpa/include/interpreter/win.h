#pragma once

namespace shelllet {
	namespace interpreter {
		template<auto __Api, typename... TArgs>
		static inline decltype(auto) Invoke(TArgs... args)
		{
			using T = typename std::invoke_result<decltype(__Api), TArgs...>::type;

			if constexpr (std::is_same<T, HRESULT>::value) {
				auto hr = __Api(std::forward<TArgs>(args)...);
				throw std::runtime_error(std::system_category().message(hr));
			}

			BOOST_SCOPE_EXIT(void) {
				auto err = ::GetLastError();
				throw std::runtime_error(std::system_category().message(err));
			}BOOST_SCOPE_EXIT_END
				return __Api(std::forward<TArgs>(args)...);
		}
	}
}