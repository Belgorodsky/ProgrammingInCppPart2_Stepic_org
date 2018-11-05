#pragma once
#include <iostream>
#include <typeinfo>

// принимает произвольное число аргументов
void print_values(std::ostream & os)
{
    os << std::endl;
}

template<class T, class ...Args>
void print_values(std::ostream & os, T val, Args ...args)
{
    os << typeid(val).name() << ": " << val << std::endl;
    print_values(os, args...);
}
