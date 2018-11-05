#pragma once
#include <utility> // для std::move и std::forward

// реализация функции apply
template <class F, class... Args>
auto apply (F &&f, Args &&...args)->decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}
