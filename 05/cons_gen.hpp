#pragma once
#include <cstddef>
// тип IntList уже определён

// реализация метафункции IntCons
template<int H, class IL>
struct IntCons;

template <int H, template<int ...> class IL, int... Vals>
struct IntCons<H,IL<Vals...>>
{
	using type = IL<H, Vals...>;
};

// реализация метафункции Generate
template <size_t N, size_t K = 0>
struct Generate
{
	using type = typename IntCons<K, typename Generate<N - 1, K + 1>::type>::type;
};

template <size_t K>
struct Generate<0, K>
{
	using type = IntList<>;
};
