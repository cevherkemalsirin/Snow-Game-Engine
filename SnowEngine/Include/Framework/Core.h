#pragma once
#include <print>
#include <memory>


namespace snw
{
	template <class T>
	using unique = std::unique_ptr<T>;

	template <class T>
	using shared = std::shared_ptr<T>;

	template <class T>
	using weak = std::weak_ptr<T>;

	template<class ...args>
	inline void LOG(std::format_string<args...> message, args&&... values)
	{
		std::println(message, std::forward<args>(values)...);
	}
}