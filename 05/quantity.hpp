#pragma once
// IntList и Zip уже реализованы

// шаблон Dimension из условия уже определён

template<int a, int b>
struct Plus
{
	static int const value = a + b;    
};

template<int a, int b>
struct Minus
{
	static int const value = a - b;    
};


// реализация класса Quantity

template<class Dimension>
struct Quantity
{
	Quantity() = default;
	explicit Quantity(double val) : m_val(val) {}

	double value() const { return m_val; };

	using dimension = Dimension;
	private:
	double m_val;
};

	template<class Dimension>
Quantity<Dimension> operator+(const Quantity<Dimension> &lhs, const Quantity<Dimension> &rhs)
{
	return Quantity<Dimension>(lhs.value() + rhs.value());
}

	template<class Dimension>
Quantity<Dimension> operator-(const Quantity<Dimension> &lhs, const Quantity<Dimension> &rhs)
{
	return Quantity<Dimension>(lhs.value() - rhs.value());
}


template<class Q>
	Quantity<typename Zip<Dimension<>, typename Q::dimension, Plus>::type>
operator*(const  double &lhs, const Q &rhs)
{
	return Quantity<typename Zip<Dimension<>, typename Q::dimension, Plus>::type>(lhs * rhs.value());
}

template<class Q>
	Quantity<typename Zip<Dimension<>, typename Q::dimension, Minus>::type>
operator/(const  double &lhs, const Q &rhs)
{
	return Quantity<typename Zip<Dimension<>, typename Q::dimension, Minus>::type>(lhs / rhs.value());
}

template<class Q>
	Quantity<typename Zip<typename Q::dimension, Dimension<>, Plus>::type>
operator*(const Q &lhs, const  double &rhs)
{
	return Quantity<typename Zip<typename Q::dimension, Dimension<>, Plus>::type>(lhs.value() * rhs);
}

template<class Q>
	Quantity<typename Zip<typename Q::dimension, Dimension<>, Minus>::type>
operator/(const Q &lhs, const  double &rhs)
{
	return Quantity<typename Zip<typename Q::dimension, Dimension<>, Minus>::type>(lhs.value() / rhs);
}

template<class Q1, class Q2>
	Quantity<typename Zip<typename Q1::dimension, typename Q2::dimension, Plus>::type>
operator*(const Q1 &lhs, const Q2 &rhs)
{
	return Quantity<typename Zip<typename Q1::dimension, typename Q2::dimension, Plus>::type>(lhs.value() * rhs.value());
}

template<class Q1, class Q2>
	Quantity<typename Zip<typename Q1::dimension, typename Q2::dimension, Minus>::type>
operator/(const Q1 &lhs, const Q2 &rhs)
{
	return Quantity<typename Zip<typename Q1::dimension, typename Q2::dimension, Minus>::type>(lhs.value() / rhs.value());
}
