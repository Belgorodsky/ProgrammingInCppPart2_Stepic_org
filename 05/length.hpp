#pragma once
// тип IntList уже определён

// // определите метафункцию Length для вычисления длины списка
template <typename T>
struct Length;

template<template<int ...> class IntList, int ...Values>
struct Length<IntList<Values...>>
{
	static constexpr size_t value = sizeof...(Values);
};
