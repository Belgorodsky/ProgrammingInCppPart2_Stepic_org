#pragma once
/*
 * typedef ComplexFunction as 
 * pointer to function (int, pointer to function (double) returning int)
 * returning pointer to function
 * (pointer to const char) returning pointer to int
*/
typedef int* (*(*ComplexFunction)(int, int (*)(double)))(const char*);
