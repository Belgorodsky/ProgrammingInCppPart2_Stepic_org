#pragma once
#include <algorithm>
// так как в задании не указан тип элементов,
// // которые хранятся в списке, то давайте сделаем
// // эту функцию шаблонной
// // Параметр It — это тип итератора 
	template<class It>
size_t max_increasing_len(It p, It q)
{
	size_t max_len = 1;
	size_t curr_len = 1;
	for (++p; p != q; ++p) {
		if (*std::prev(p) < *p) max_len = std::max(max_len, ++curr_len);
		else curr_len = 1;
	}
	return max_len;
}
