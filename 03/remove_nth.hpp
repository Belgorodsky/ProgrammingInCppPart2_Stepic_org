#pragma once
#include <algorithm>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
	template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
	return remove_if(p,q,[&n](typename FwdIt::reference) { return !n--;});
}
