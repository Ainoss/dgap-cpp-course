#pragma once
#include <iostream> //библиотека для работы с функциями ввода и вывода

class Complex         // реализация класса комплексных чисел
{
	// поля

	//"личные" данные
private:
	float re, im;      // действительная и мнимая части

public:
	// выбор конструктора осуществляется по правилам перегрузки

	// конструктор по умолчанию 
	Complex();

	// конструктор для вещественного числа
	Complex(float r);

	// общий конструктор
	Complex(float r, float i);

	// конструктор копирования
	Complex(const Complex &c);

	// деструктор (для освобождения памяти)
	~Complex();

	// модуль комплексного числа
	float abs();

	//комплексно сопряженное выражение
	float conj();

	// перегрузка оператора присваивания
	Complex& operator = (const Complex &c);

	// перегрузка оператора +=
	Complex& operator += (const Complex &c);

	// перегрузка оператора сложения
	Complex operator + (const Complex &c);

	// перегрузка оператора вычитания
	Complex operator - (const Complex &c);

	Complex operator*(const Complex & c);

	// перегрузка оператора умножения
	Complex operator *= (const int a);


	// перегрузка оператора деления
	Complex operator / (const Complex &c);

	// укажем дружественные операторы, которым мы разрешаем доступ
	// к "личным" (private) данным
	friend std::ostream & operator<< (std::ostream &, const Complex &);
	friend std::istream & operator>> (std::istream &, Complex &);

};

// перегрузка оператора <<
std::ostream& operator<< (std::ostream &out, const Complex &c);

// перегрузка оператора >>
std::istream& operator>> (std::istream &in, Complex &c);

Complex operator * (const Complex c, const int a);
Complex operator * (const int a, const Complex c);

