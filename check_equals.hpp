#pragma once
#include <typeinfo>

bool check_equals(Expression const *left, Expression const *right)
{
    return typeid(*left) == typeid(*right);
}
