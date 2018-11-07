#pragma once
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>
// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).

struct TypesComparator
{
    bool operator()(
        const std::pair<std::type_index, std::type_index> &pt1,
        const std::pair<std::type_index, std::type_index> &pt2
    ) const
    {
        return pt1.first < pt2.first || (pt1.first == pt2.first && pt1.second < pt2.second);
    }
};

template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    using F = std::function<Result (Base*, Base*)>;
    std::map<
        std::pair<std::type_index, std::type_index>,
        F,
        TypesComparator
    >  methods;
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result
    void addImpl( std::type_index t1, std::type_index t2, F f )
    {
        methods[std::make_pair(t1,t2)] = f;
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а 
        if (Commutative)
        {
            std::pair<std::type_index, std::type_index> key1(
                std::type_index( typeid(*a) ),std::type_index( typeid(*b) )
            );
            std::pair<std::type_index, std::type_index> key2(
                std::type_index( typeid(*b) ),std::type_index( typeid(*a) )
            );
            return methods.count(key1) || methods.count(key2);
        }
        else
        {
            std::pair<std::type_index, std::type_index> key(
                std::type_index( typeid(*a) ),std::type_index( typeid(*b) )
            );
            return methods.count(key);
        }
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        if (Commutative)
        {
            std::pair<std::type_index, std::type_index> key1(
                std::type_index( typeid(*a) ),std::type_index( typeid(*b) )
            );
            std::pair<std::type_index, std::type_index> key2(
                std::type_index( typeid(*b) ),std::type_index( typeid(*a) )
            );
            if (methods.count(key1))
            {
                const F &f = methods.at(key1);

                return f(a,b);
            }
            else
            {
                const F &f = methods.at(key2);

                return f(b,a);
            }
        }
        else
        {
            std::pair<std::type_index, std::type_index> key(
                std::type_index( typeid(*a) ),std::type_index( typeid(*b) )
            );
            const F &f = methods.at(key);

            return f(a,b);
        }
    }
};