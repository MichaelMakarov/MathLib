﻿#pragma once
#include "Matrix.h"

namespace linalg
{

	// LU-разложение матрицы (A = L * U).
	// A - исходная матрица
	// L - нижне-треугольная матрица
	// U - верхне-треугольная матрица
	// true, если расчёт прошёл без ошибок.
	bool LU(
		const Matrix& A,
		Matrix& L,
		Matrix& U);	

	// PLU-разложение матрицы (P * A = L * U).
	// Исходная матрица должна быть не вырожденной.
	// A - исходная матрица
	// L - нижне-треугольная матрица
	// U - верхне-треугольная матрица
	// P - вектор индексов столбцов исх. матрицы
	// k - количество перестановок
	// true, если расчёт прошёл без ошибок.
	bool PLU(
		const Matrix& A,
		Matrix& L,	
		Matrix& U,
		Vector& P,
		size_t& k);	

	// QR-разложение матрицы (A = Q * R).
	// Исходная матрица квадратная.
	// A - исходная матрица
	// Q - ортогональная матрица
	// R - верхне-треугольная
	// true, если расчёт прошёл без ошибок.
	bool QR(
		const Matrix& A,
		Matrix& Q,
		Matrix& R);	

	// Диагонализация матрицы методом Монтанте.
	// Исходная матрица изменяется.
	// Результатом является матрица, на диагонали которой определители исходной.
	// Правые столбцы расширенной прямоугольной матрицы также изменяются,
	// что даёт возможность решать СЛАУ.
	// true, если расчёт прошёл без ошибок.
	bool MontanteBareiss(const Matrix& A);

	// расчёт определителя матрицы
	const double Determinant(const Matrix& A);

	// Расчёт обратной матрицы методом Гаусса-Жордана.
	// Исходная матрица должна быть квадратной.
	// A - исходная матрица
	// I - обратная матрица
	// false, если матрица вырожденная.
	bool Inverse(
		const Matrix& A,
		Matrix& I);	

	// Расчёт обратной матрицы для диагональной матрицы.
	// Исходная матрица должна быть квадратной.
	// D - исходная матрица
	// I - обратная матрица
	// false, если матрица вырожденная.
	bool InverseD(
		const Matrix& D,
		Matrix& I);

	// Умножение матрицы на диагональную справа.
	// Более быстрое перемножение по сравнению с общим случаем.
	// A - исходная матрица
	// D - квадратная диагональная матрица
	Matrix AxD(
		const Matrix& A,
		const Matrix& D); 

	// Умножпение матрицы на диагональную слева.
	// Более быстрое перемножение по сравнению с общим случаем.
	// D - квадратная диагональная матрица
	// A - исходная матрица
	Matrix DxA(
		const Matrix& D,
		const Matrix& A);

	// Сингулярное разложение матрицы A = U * S * V.
	// A - исходная матрица
	// U - ортонормальная по столбцам матрица
	// S - диагональная матрица из сингулярных значений
	// V - ортонормальная по столбцам матрица
	// true, если расчёт прошёл без ошибок.
	bool SVD(
		const Matrix& A,
		Matrix& U,
		Matrix& S,
		Matrix& V);

	// Решение СЛАУ A * X = B.
	// A - матрица системы
	// B - вектор правой части
	// X - вектор-решение СЛАУ
	// true, если расчёт прошёл без ошибок.
	bool Solve(
		const Matrix& A,
		const Vector& B,
		Vector& X);	
}
