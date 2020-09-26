#pragma once
#include <math.h>

// Представление комплексного числа.
class Complex
{
private:
	double c_x;			// действительная часть числа
	double c_y;			// мнимая часть числа

public:
	// Создание экземпляра комплексного числа с заданием параметров.
	// х - действительная часть, у - мнимая часть.
	Complex(const double x = 0.0, const double y = 0.0) : c_x(x), c_y(y) {}
	// Копирование комплесного числа.
	Complex(const Complex& c) : c_x(c.c_x), c_y(c.c_y) {}
	// деструктор
	~Complex() { c_x = c_y = 0.0; }

	// Действительная часть.
	const double Re() const { return c_x; }
	// Мнимая часть.
	const double Im() const { return c_y; }
	// Задание действительной части.
	void Re(const double x) { c_x = x; }
	// Задание мнимой части.
	void Im(const double y) { c_y = y; }
	// Модуль числа.
	const double Module() const { return sqrt(c_x * c_x + c_y * c_y); }
	// Аргумент числа.
	const double Arg() const { return atan2(c_y, c_x); }
	// Комплексно-сопряженное число.
	const Complex Conj() const { return Complex(c_x, -c_y); }
	// содержит ли число только действительную часть
	bool IsReal() const { return fabs(c_y) < 1e-10; }
	// Строковое представление.
	const char* ToString() const;

	// Сложение.
	friend Complex operator + (const Complex& f, const Complex& s);
	// Вычитание.
	friend Complex operator - (const Complex& f, const Complex& s);
	// Умножение.
	friend Complex operator * (const Complex& f, const Complex& s);
	// Деление.
	friend Complex operator / (const Complex& f, const Complex& s);
	// Сложение с действительным числом.
	friend Complex operator + (const Complex& c, const double s);
	// Вычитание действительного числа.
	friend Complex operator - (const Complex& c, const double s);
	// Умножение на действительное число.
	friend Complex operator * (const Complex& c, const double s);
	// Деление на действительное число.
	friend Complex operator / (const Complex& c, const double s);
	// Возведение в степень.
	friend Complex operator ^ (const Complex& c, const double n);

	// Оператор присвоения.
	Complex& operator = (const Complex& c);
	// Сложение.
	Complex& operator += (const Complex& c);
	// Вычитание.
	Complex& operator -= (const Complex& c);
	// Умножение.
	Complex& operator *= (const Complex& c);
	// Деление.
	Complex& operator /= (const Complex& c);
	// Сложение.
	Complex& operator += (const double c);
	// Вычитание.
	Complex& operator -= (const double c);
	// Умножение.
	Complex& operator *= (const double c);
	// Деление.
	Complex& operator /= (const double c);
	// Возведение в степень.
	Complex& operator ^ (const double n);

};

