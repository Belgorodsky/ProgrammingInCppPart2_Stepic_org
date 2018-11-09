#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
	std::vector<typename std::iterator_traits<Iterator>::value_type> v(p, q);
	std::sort(v.begin(), v.end());
	size_t res = 0;
	do {
		res += (std::adjacent_find(v.begin(), v.end()) == v.end());
	} while (std::next_permutation(v.begin(), v.end()));
	return res;
}
