#pragma once
#include <future>
#include <functional>
#include <list>
#include <vector>
#include <cassert>
#include <cmath>
#include <numeric>
#include <type_traits>
#include <algorithm>

template<class InputIt, class UnaryFunctor, class BinaryFunctor>
auto map_reduce_chunk(InputIt begin, InputIt end, UnaryFunctor f1, BinaryFunctor f2) -> decltype(f2(f1(*begin), f1(*begin))) 
{
	std::vector<decltype(f1(*begin))> mappings;
	std::transform(begin, end, std::back_inserter(mappings), f1);
	return std::accumulate(mappings.begin() + 1, mappings.end(), mappings.front(), f2);
}

template<class InputIt, class UnaryFunctor, class BinaryFunctor>
auto map_reduce(InputIt begin, InputIt end, UnaryFunctor f1, BinaryFunctor f2, size_t num) -> decltype(f2(f1(*begin), f1(*begin))) 
{
	using future_t = std::future<decltype(f2(f1(*begin), f1(*begin))) >;
	std::vector<future_t> threads;

	auto d = std::distance(begin, end);
	auto len = d / num;
	auto add = d % num;
	for(size_t i = 0; i < num; ++i) {
		auto till = begin;
		auto l = len;
		if (add > 0) {
			++l;
			--add;
		}
		std::advance(till, l);
		threads.push_back(std::async(std::launch::async, map_reduce_chunk<InputIt, UnaryFunctor, BinaryFunctor>, begin, till, f1, f2));
		begin = till;
	}

	return map_reduce_chunk(threads.begin(), threads.end(), [](future_t& f) { return f.get(); }, f2);
}
