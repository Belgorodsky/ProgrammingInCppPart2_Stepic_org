#pragma once
#include <string>
#include <sstream>
#include <exception>

struct bad_from_string : std::exception 
{ 
    bad_from_string(char const * s) : msg(s) {}
    char const * what() const noexcept { return msg.c_str(); }
    std::string msg;
};

template<class T>
T from_string(std::string const& s)
{
    // создаётся поток
    std::istringstream is(s);
    
    // включаются исключения
    is.exceptions(std::istringstream::failbit | std::istringstream::badbit);
    
    // отключается игнорировние пробелов
    is >> std::noskipws;
    
    // значение, которое мы собираемся считать
    T t;
    try 
    {
        is >> t;
    } 
    // если при чтении произошла ошибка, то бросаем исключение выше
    catch (std::istringstream::failure & f)
    {
        throw bad_from_string(f.what());
    }
    // в этот момент понятно, что чтение прошло успешно.
    // мы должны проверить, что в потоке ничего не осталось
    try
    {
        // пробуем прочесть один символ
        char c = 0;
        is >> c;  
    } 
    // если ошибка, то возвращаем прочитанное значение
    catch (std::istringstream::failure & f)
    {
        return t;
    }
    // если ошибки не было, значит в потоке что-то оставалось
    throw bad_from_string("Conversion error");
}
