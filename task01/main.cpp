#include <iostream>
#include "complex.h"

int main()
{
	Complex _a, _b(2.0), _c(1.0, 1.0);

	std::cin >> _a;
	std::cout << _a << ", " << _b << ", abs: " << _b.abs() << std::endl;

	_a = _b + _c.conj();
	_a = _a * Complex(2.0);
	_a += _c;
	_c = _a + 2 * _b;

	std::cout << _a << ", " << _c << std::endl;

	// Add your usage examples
	setlocale(LC_ALL, "Rus");

	// cоздаем объект пользовательского типа данных Complex
	// вызываем подходящий конструктор для введенных значений
	Complex a(10, 4);
	Complex b(6, -6);

	// вывод чисел 
	std::cout << "a = " << a << "; b =" << b << std::endl;

	// сложение чисел в комплексном поле
	std::cout << "Сумма равна " << a + b << std::endl;
	// разность чисел в комплексном поле
	std::cout << "Разность равна " << a - b << std::endl;
	// умножение чисел в комплексном поле
	std::cout << "Умножение равно " << a * b << std::endl;
	// деление чисел в комплексном поле
	std::cout << "Деление равно " << a / b << std::endl;

	std::cout << "До работы оператора присвания b = " << b << std::endl;
	b = a;
	std::cout << "После работы оператора оператора присваивания b = " << b << std::endl;

	std::cout << "Модуль комплексного числа b равен " << b.abs() << std::endl;

	system("pause");
	return 0;
}