#pragma once
#include <type_traits>
#include <cstddef>

template<class T>
struct call_method_needed
{
    template<class U, size_t (U::*)()const = &U::size>
    struct call_size_method {};

    template<class U>
    std::true_type constexpr static get_size_check(call_size_method<U>*);

    template<class U>
    std::false_type constexpr static get_size_check(...);

    static constexpr bool value{decltype(get_size_check<T>(0))::value};
};


template<class T>
size_t get_size_impl(typename std::enable_if<call_method_needed<T>::value, T>::type& t)
{
    return t.size();
}


template<class T>
size_t get_size_impl(typename std::enable_if<!call_method_needed<T>::value, T>::type &t)
{
    return t.size;
}

template<class T>
size_t get_size(T &t)
{
        return get_size_impl<T>(t);
}
