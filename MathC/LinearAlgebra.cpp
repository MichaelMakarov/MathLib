#include "LinearAlgebra.h"
#include <vector>
#include <list>

namespace linalg 
{
	bool LU(const Matrix& A, Matrix& L, Matrix& U)
	{
		if (!A.IsSquare()) return false;
		double sum;
		size_t size = A.RowsNumber();
		L = Matrix(size, size);
		U = Matrix(size, size);
		size_t m, n, i;
		for (m = 0; m < size; ++m)
		{
			for (n = 0; n < size; ++n)
			{
				sum = 0.0;
				if (m <= n)
				{
					for (i = 0; i <= m; ++i)
						sum += L(m, i) * U(i, n);
					U(m, n) = A(m, n) - sum;
				}
				else {
					for (i = 0; i < m; ++i)
						sum += L(m, i) * U(i, n);
					L(m, n) = (A(m, n) - sum) / U(n, n);
				}
			}
			L(m, m) = 1.0;
		}
		return true;
	}

	bool PLU(
		const Matrix& A, 
		Matrix& L,
		Matrix& U,
		Vector& P,
		size_t& k)
	{
		if (!A.IsSquare()) return false;
		size_t size = A.RowsNumber();
		Matrix B(A);
		P = Vector(size);
		L = Matrix::Identity(size);
		U = Matrix(A);
		k = 0;
		double buf, absv;
		size_t imax, i, m, n;
		for (i = 0; i < size; ++i) P[i] = i;
		for (m = 0; m < size - 1; ++m)
		{
			buf = abs(U(m, m));
			imax = m;
			for (i = m + 1; i < size; ++i)
				if ((absv = abs(U(i, m))) > buf)
				{
					buf = absv;
					imax = i;
				}
			if (buf < 1e-15) return false;
			if (imax != m)
			{
				// меняем местами строки
				for (n = m; n < size; ++n) std::swap(U(m, n), U(imax, n));
				for (n = 0; n < m; ++n) std::swap(L(m, n), L(imax, n));
				std::swap(P[m], P[imax]);
				k++;
			}
			for (n = m + 1; n < size; ++n)
			{
				buf = U(n, m) / U(m, m);
				for (i = m; i < size; ++i) U(n, i) -= buf * U(m, i);
				L(n, m) = buf;
			}
		}
		return true;
	}

	bool QR(const Matrix& A, Matrix& Q, Matrix& R)
	{
		if (!A.IsSquare()) return false;
		size_t size = A.RowsNumber(), n, k;
		Q = Matrix(size, size);
		// вектор из столбцов матрицы
		Vector* pVecs = new Vector[size];
		int column;
		for (n = 0; n < size; ++n)
		{
			column = static_cast<int>(n);
			pVecs[n] = A.GetColumn(column);
			// ортогонализация Грамма-Шмидта
			for (k = 0; k < n; ++k)
				pVecs[n] -= pVecs[k] * (pVecs[n] * pVecs[k]);
			pVecs[n].Normalize();
			// сохраняем вектор в столбец ортогональной матрицы
			Q.SetColumn(column, pVecs[n]);
		}
		delete[] pVecs;
		// R = Q^-1 * A = Q^T * A
		R = Matrix(Q).Transpose() * A;
		return true;
	}

	bool MontanteBareiss(const Matrix& A)
	{
		size_t nRows = A.RowsNumber(),
			   nCols = A.ColsNumber(),
			   ni;
		if (nRows > nCols) return false;
		double div = 1.0, pivot, buf;
		for (size_t ci = 0; ci < nRows; ++ci)
		{
			// находим ведущий элемент
			buf = A(ci, ci);
			for (size_t i = ci + 1; i < nRows; ++i)
				if (abs(A(i, ci)) > buf)
				{
					buf = A(i, ci);
					ni = i;
				}
			// если текущая строка не содержит ведущий элемент, то меняем строки местами
			if (ni != ci)
				for (size_t i = 0; i < nCols; ++i)
					std::swap(A(ci, i), A(ni, i));
			// если ведущий элемент оказался нулевым, то матрица вырожденная
			if (abs(A(ci, ci)) < 1e-15) return false;
			// итерация по диагонализации матрицы
			pivot = A(ci, ci);
			for (size_t m = 0; m < nRows; ++m)
			{
				if (m == ci) continue;
				for (size_t n = 0; n < nCols; ++n)
				{
					if (n == ci) continue;
					A(m, n) = div * (A(m, n) * pivot - A(m, ci) * A(ci, n));
				}
			}
			div = 1 / pivot;
			// заполнение текущего столбцами нулями
			for (size_t m = 0; m < nRows; ++m)
			{
				if (m == ci) continue;
				A(m, ci) = 0.0;
			}
		}
		return true;
	}

	const double Determinant(const Matrix& A)
	{
		Matrix L, U;
		Vector P;
		size_t k;
		double det = 1.0;
		if (!PLU(A, L, U, P, k)) return 0.0;
		for (size_t i = 0; i < A.RowsNumber(); ++i)
			det *= U(i, i);
		if (k % 2 != 0) det = -det;
		return det;
	}

	bool Inverse(const Matrix& A, Matrix& I)
	{
		if (!A.IsSquare()) return false;
		size_t size = A.RowsNumber(), i, m, n;
		Matrix B(A);
		I = Matrix::Identity(size);
		double cur, fabs;
		for (size_t i = 0; i < size; ++i)
		{
			// находим строку с максимальным по модулю элементом в данном столбце
			cur = abs(B(i, i));
			m = i;
			for (n = i + 1; n < size; ++n)
				if ((fabs = abs(B(i, n))) > cur)
				{
					cur = fabs;
					m = n;
				}
			if (cur <= 1e-15) return false;
			// меняем строки местами
			if (m != i)
				for (n = 0; n < size; ++n)
				{
					std::swap(B(i, n), B(m, n));
					std::swap(I(i, n), I(m, n));
				}
			// текущий элеент на главной диагонали
			cur = B(i, i);
			// норируем текущую строку
			for (n = 0; n < size; ++n)
			{
				B(i, n) /= cur;
				I(i, n) /= cur;
			}
			// складываем с отстальными строками
			// обнуляем все элементы текущего столбца кроме элемента главной диагонали
			for (m = 0; m < size; ++m)
			{
				if (m == i) continue;
				cur = B(m, i);
				for (n = 0; n < size; ++n)
				{
					B(m, n) -= B(i, n) * cur;
					I(m, n) -= I(i, n) * cur;
				}
			}
		}
		return true;
	}

	Matrix AxD(const Matrix& A, const Matrix& D)
	{
		size_t nRows = A.RowsNumber(),
			nCols = D.ColsNumber(),
			m, n;
		if (A.ColsNumber() != nCols) throw "The matrices are not consistent!";
		Matrix M(A);
		for (m = 0; m < nRows; ++m)
			for (n = 0; n < nCols; ++n)
				M(m, n) *= D(n, n);
		return M;
	}

	Matrix DxA(const Matrix& D, const Matrix& A)
	{
		size_t nRows = D.RowsNumber(),
			nCols = A.ColsNumber(),
			m, n;
		if (nRows != A.RowsNumber()) throw "The matrices are not consistent!";
		Matrix M(A);
		for (m = 0; m < nRows; ++m)
			for (n = 0; n < nCols; ++n)
				M(m, n) *= D(m, m);
		return M;
	}

	bool SVD(const Matrix& A, Matrix& U, Matrix& S, Matrix& V)
	{
		const char* str = A.ToString();;
		Matrix M(A);
		M.Transpose();
		M = M * A;
		size_t size = M.RowsNumber(), m, n;
		int i;
		double currValue, prevValue, eps = 1e-5;
		std::vector<double> values(size);
		std::vector<Vector> vectors(size);
		Vector v(size);
		for (i = 0; i < size; ++i)
		{
			str = M.ToString();
			// нахождение собственных значений
			currValue = 2.0;
			prevValue = 1.0;
			for (n = 0; n < size; ++n) v[n] = 1.0;
			while (abs((currValue - prevValue) / currValue) > eps)
			{
				prevValue = currValue;
				v = (M * v).Normalize();
				currValue = v[0];
			}
			str = v.ToString();
			// сохраняем собственные значение и вектор
			vectors[i] = v;
			currValue = v * (M * v);
			values[i] = currValue;
			for (m = 0; m < size; ++m)
				for (n = 0; n < size; ++n)
					M(m, n) -= currValue * v[m] * v[n];
		}
		// инициализируем матрицы
		V = Matrix(i, size);
		S = Matrix(i, i);
		// находим собственные вектора
		for (n = 0; n < i; ++n)
		{
			// заполняем диагнальную матрицу
			S(n, n) = sqrt(values[n]);
			// заполняем матрицу из собственных векторов
			V.SetColumn(n, vectors[n]);
		}
		Matrix Sinv(S), VT(V);
		for (n = 0; n < size; ++n) Sinv(n, n) = 1 / Sinv(n, n);
		U = A * VT.Transpose() * Sinv;

		return true;
	}

	bool Solve(const Matrix& A, const Vector& B, Vector& X)
	{
		size_t nRows = A.RowsNumber(), nCols = A.ColsNumber(), m, n;
		if (nRows != B.Size()) return false;
		X = Vector(nRows);
		Matrix M(nRows, nCols + 1), D;
		for (m = 0; m < nRows; ++m)
		{
			for (n = 0; n < nCols; ++n)
				M(m, n) = A(m, n);
			M(m, nCols) = B[m];
		}
		if (!MontanteBareiss(M)) return false;
		for (m = 0; m < nRows; ++m)
			X[m] = M(m, nRows) / M(m, m);
		return true;
	}
}

