#pragma once
#include "Polynom.h"
#include "Vector.h"

namespace num
{
	// �������� ���������� P(x) ����������������� ������ ������ Y(x).
	// n - ������� ����������.
	// number (>1) - ���������� �����.
	// pX - ������ ����� �� ���������� x.
	// pY - ������ ����� �� ���������� �.
	// true, ���� ������� �����.
	bool PolyFromLeastSquares(
		size_t n,
		size_t number,
		const double* const pX,
		const double* const pY,
		Polynom& p);

	// 
	
}


