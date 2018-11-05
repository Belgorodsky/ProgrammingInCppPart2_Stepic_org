#pragma once
#include <tuple>

// принимает std::tuple произвольного размера
/* тут должен быть заголовок to_pair */
template<size_t ID1,size_t ID2, class... Args>
auto to_pair(const std::tuple<Args...> &tuple)->
	decltype(
			std::make_pair(std::get<ID1>(tuple), std::get<ID2>(tuple))
	)
{
    return std::make_pair(std::get<ID1>(tuple), std::get<ID2>(tuple));
}
