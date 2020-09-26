#include "Numerics.h"
#include "LinearAlgebra.h"

namespace num
{
	bool PolyFromLeastSquares(
		size_t n, 
		const size_t number, 
		const double* const pX, 
		const double* const pY, 
		Polynom& p)
	{
		n++;
		if (number < 1) return false;
		Matrix A(number, n);
		Vector Y(number, pY), X;
		size_t i, k;
		for (i = 0; i < number; ++i)
		{
			A(i, 0) = 1.0;
			for (k = 1; k < n; ++k) A(i, k) = A(i, k - 1) * pX[i];
		}
		Matrix AT(A);
		AT.Transpose();
		if (!linalg::Solve(AT * A, AT * Y, X)) return false;
		p = Polynom(X.Size(), X.Values());
		return true;
	}
}

