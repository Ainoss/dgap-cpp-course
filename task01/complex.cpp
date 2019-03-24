#include "complex.h"

	// конструктор по умолчанию 
	Complex::Complex()
	{
		re = 0;
		im = 0;
	};
	
	// конструктор для вещественного числа
	Complex::Complex(float r)
	{
		re = r;
		im = 0;
	}
	
	// общий конструктор
	Complex::Complex(float r, float i)
	{
		re = r;
		im = i;
	}

	// конструктор копирования
	Complex::Complex(const Complex &c)   
	{
		re = c.re;
		im = c.im;
	}

	// деструктор (для освобождения памяти)
	Complex::~Complex()
	{
	}


	// модуль комплексного числа
	float Complex::abs()
	{
		return sqrt(re * re + im * im);
	}

	float Complex::conj()
	{
		return (re * re + im * im) * (re * re + im * im);
	}

	// перегрузка оператора присваивания
	Complex& Complex::operator = (const Complex &c)
	{
		re = c.re;
		im = c.im;

		// возврат текущего объекта из функции-члена
		return *this; 
	}


	// перегрузка оператора +=
	Complex& Complex::operator += (const Complex &c)
	{
		re += c.re;
		im += c.im;
		return *this;
	}

	// перегрузка оператора сложения
	Complex Complex::operator + (const Complex &c)
	{
		return Complex(re + c.re, im + c.im);
	}

	// перегрузка оператора вычитания
	Complex Complex::operator - (const Complex &c)
	{
		return Complex(re - c.re, im - c.im);
	}

	// перегрузка оператора умножения
	Complex Complex::operator * (const Complex &c)
	{
		return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
	}
	
	//Complex Complex::operator * (const float a)
	//{
	//	return Complex(re * a + im * a);
	//}
	
	Complex Complex::operator *= (const int a)
	{
		re *= a;
		im *= a;
		return *this;
	}

	// перегрузка оператора деления
	Complex Complex::operator / (const Complex &c)
	{
		Complex temp;

		float r = c.re * c.re + c.im * c.im;
		temp.re = (re * c.re + im * c.im) / r;
		temp.im = (im * c.re - re * c.im) / r;

		return temp;
	}

// перегрузка оператора <<
std::ostream& operator<< (std::ostream &out, const Complex &c)
{
	out << "(" << c.re << ", " << c.im << ")";
	return out;
}

// перегрузка оператора >>
std::istream& operator>> (std::istream &in, Complex &c)
{
	in >> c.re >> c.im;
	return in;
}

Complex operator * (const Complex c, const int a)
{
	Complex b(c);
	return b *= a;
}

Complex operator * (const int a, const Complex c)
{
	Complex b(c);
	return b *= a;
}
