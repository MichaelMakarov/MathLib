#pragma once
#include "Constants.h"
#include "Enumerable.h"

// класс представляет многочлен вида a0 + a1X + a2x^2 + ... + anx^n
class Polynom
{
protected:
	double* p_pValues;					// массив коэффициентов
	size_t p_size;						// степень многочлена

public:
	// Многочлен с единичными коэффициентами.
	// n - степень многочлена.
	Polynom(const size_t n = 1);
	// Многочлен с заданными степенью и коэффициентами.
	// n - количество коэффициентов.
	// pCs - массив коэффициентов.
	Polynom(
		const size_t n, 
		const double* const pCs);
	// Копирование параметров многочлена.
	Polynom(const Polynom& p);
	// Многочлен с заданными степенью и коэффициентами.
	// n - количество коэффициентов.
	// a0 - первый коэффициент и т.д.
	Polynom(
		const size_t n, 
		const double a0, ...);
	// Многочлен с заданными коэффициентами.
	// cs - список коэффициентов.
	Polynom(const std::initializer_list<double> cs);
	// деструктор
	~Polynom();

	// Строковое представление.
	const char* ToString(const char* s = "x") const;
	// Старшая степень многочлена.
	const size_t Degree() const;
	// Массив коэффициентов многочлена.
	const double* const Coefficients() const;
	// Копирование через присовение.
	Polynom& operator = (const Polynom& p);
	// Индексация по массиву коэффициентов.
	// index - степень, которой соответствует коэффициент.
	double& operator [] (const size_t index) const;

	const double operator () (const double arg) const;
	// Сложение полиномов.
	friend Polynom operator + (const Polynom& f, const Polynom& s);
	// Вычитание полиномов.
	friend Polynom operator - (const Polynom& f, const Polynom& s);
	// Перемножение полиномов.
	friend Polynom operator * (const Polynom& f, const Polynom& s);

};

