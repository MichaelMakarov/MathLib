#pragma once
#include "Polynom.h"
#include "Vector.h"

namespace num
{
	// Создание многочлена P(x) аппроксимирующего массив данных Y(x).
	// n - степень многочлена.
	// number (>1) - количество точек.
	// pX - массив точек по координате x.
	// pY - массив точек по координате у.
	// true, если введены верно.
	bool PolyFromLeastSquares(
		size_t n,
		size_t number,
		const double* const pX,
		const double* const pY,
		Polynom& p);

	// 
	
}


