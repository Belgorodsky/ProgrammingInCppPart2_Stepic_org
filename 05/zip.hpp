#pragma once
// IntList и IntCons уже определены

// Определение метафункции Zip
template <class L1,class L2, template <int, int> class F>
struct Zip
{
	using type = typename IntCons<
		F<L1::Head, L2::Head>::value, 
		typename Zip<typename L1::Tail, typename L2::Tail, F>::type
			>::type;
};

template <template <int, int> class F>
struct Zip<IntList<>,IntList<>, F>
{
	using type = IntList<>;
};
