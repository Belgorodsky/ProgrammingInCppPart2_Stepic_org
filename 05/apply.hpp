#pragma once
#include <tuple>

// тип IntList и метафункция Generate уже определены

// определение функции apply
	template<class F, template<class...> class Tuple, class ...Args, int... Indexes>
	auto apply_impl(F &&f, Tuple<Args...> &&t, IntList<Indexes...> tl)
->decltype(std::forward<F>(f)(std::get<Indexes>(t)...))
{
	return std::forward<F>(f)(std::get<Indexes>(t)...);
}

template<class F, template<class...> class Tuple, class ...Args>
	auto apply(F &&f, Tuple<Args...> &&t)->decltype(
			apply_impl(std::forward<F>(f), std::forward<Tuple<Args...>>(t), typename Generate<sizeof...(Args)>::type{})
			)
{
	return apply_impl(std::forward<F>(f), std::forward<Tuple<Args...>>(t), typename Generate<sizeof...(Args)>::type{});
}
