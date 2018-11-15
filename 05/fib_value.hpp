#pragma once
// определите метафункцию Fib<N>
template <size_t N>
class Fib 
{
	public:
		static int constexpr value = Fib<N-1>::value + Fib<N-2>::value;
};

template <>
class Fib<0>
{
	public:
		static int constexpr value = 0;
};

template <>
class Fib<1> 
{
	public:
		static int constexpr value = 1;
};
