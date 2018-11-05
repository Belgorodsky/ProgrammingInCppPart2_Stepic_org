#pragma once
// определение переменной
#include <algorithm>

auto gen_finder = [](int * begin, int * end)
{
    return [begin, end](int val)->bool
    {
        return std::find(begin, end, val) != end;
    };
};
