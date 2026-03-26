#include <print>


namespace snw
{
	template<class ...args>
	inline void LOG(std::format_string<args...> message, args&&... values)
	{
		std::println(message, std::forward<args>(values)...);
	}
}