#pragma once
#include <iostream> 

class Complex        
{
private:
	float re, im;      

public:
	
	Complex();

	
	Complex(float r);

	
	Complex(float r, float i);

	
	Complex(const Complex &c);

	
	~Complex();

	
	float abs();

	
	float conj();

	
	Complex& operator = (const Complex &c);

	
	Complex& operator += (const Complex &c);

	
	Complex operator + (const Complex &c);

	
	Complex operator - (const Complex &c);

	Complex operator*(const Complex & c);

	
	Complex operator *= (const int a);


	
	Complex operator / (const Complex &c);

	friend std::ostream & operator<< (std::ostream &, const Complex &);
	friend std::istream & operator>> (std::istream &, Complex &);

};

std::ostream& operator<< (std::ostream &out, const Complex &c);

std::istream& operator>> (std::istream &in, Complex &c);

Complex operator * (const Complex c, const int a);
Complex operator * (const int a, const Complex c);

