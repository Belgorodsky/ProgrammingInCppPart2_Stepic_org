#pragma once

template<class T, class U>
bool compare(const T &a, const T &b, U (T::*mptr)() const)
{
    return (a.*mptr)() < (b.*mptr)();
}
