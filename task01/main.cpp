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

	// c������ ������ ����������������� ���� ������ Complex
	// �������� ���������� ����������� ��� ��������� ��������
	Complex a(10, 4);
	Complex b(6, -6);

	// ����� ����� 
	std::cout << "a = " << a << "; b =" << b << std::endl;

	// �������� ����� � ����������� ����
	std::cout << "����� ����� " << a + b << std::endl;
	// �������� ����� � ����������� ����
	std::cout << "�������� ����� " << a - b << std::endl;
	// ��������� ����� � ����������� ����
	std::cout << "��������� ����� " << a * b << std::endl;
	// ������� ����� � ����������� ����
	std::cout << "������� ����� " << a / b << std::endl;

	std::cout << "�� ������ ��������� ��������� b = " << b << std::endl;
	b = a;
	std::cout << "����� ������ ��������� ��������� ������������ b = " << b << std::endl;

	std::cout << "������ ������������ ����� b ����� " << b.abs() << std::endl;

	system("pause");
	return 0;
}