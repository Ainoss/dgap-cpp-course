#include "complex.h"

	
	Complex::Complex()
	{
		re = 0;
		im = 0;
	};
	
	
	Complex::Complex(float r)
	{
		re = r;
		im = 0;
	}
	
	
	Complex::Complex(float r, float i)
	{
		re = r;
		im = i;
	}

	
	Complex::Complex(const Complex &c)   
	{
		re = c.re;
		im = c.im;
	}

	
	Complex::~Complex()
	{
	}


	
	float Complex::abs()
	{
		return sqrt(re * re + im * im);
	}

	float Complex::conj()
	{
		return (re * re + im * im) * (re * re + im * im);
	}

	
	Complex& Complex::operator = (const Complex &c)
	{
		re = c.re;
		im = c.im;

		
		return *this; 
	}


	
	Complex& Complex::operator += (const Complex &c)
	{
		re += c.re;
		im += c.im;
		return *this;
	}

	
	Complex Complex::operator + (const Complex &c)
	{
		return Complex(re + c.re, im + c.im);
	}

	
	Complex Complex::operator - (const Complex &c)
	{
		return Complex(re - c.re, im - c.im);
	}

	
	Complex Complex::operator * (const Complex &c)
	{
		return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
	}
	
	Complex Complex::operator *= (const int a)
	{
		re *= a;
		im *= a;
		return *this;
	}

	
	Complex Complex::operator / (const Complex &c)
	{
		Complex temp;

		float r = c.re * c.re + c.im * c.im;
		temp.re = (re * c.re + im * c.im) / r;
		temp.im = (im * c.re - re * c.im) / r;

		return temp;
	}

std::ostream& operator<< (std::ostream &out, const Complex &c)
{
	out << "(" << c.re << ", " << c.im << ")";
	return out;
}


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
