#include <iostream>
#include <random>
#include "../MathC/Vector.h"
#include "../MathC/Matrix.h"
#include "../MathC/LinearAlgebra.h"
#include "../MathC/Numerics.h"

void TestVector();
void TestMatrix();
void TestPolynom();
void TestLinalg();
void TestNumerics();

int main()
{
	std::cout << "***Testing proj***\n";
	std::cout << "\n...Vectors...\n\n";
	TestVector();
	std::wcout << "\n...Matrices...\n\n";
	TestMatrix();
	std::cout << "\n...Linalg...\n\n";
	TestLinalg();
	std::cout << "\n...Polynoms...\n\n";
	TestPolynom();
	std::cout << "\n...Numerics...\n\n";
	TestNumerics();

	return 0;
}

void TestVector()
{
	double array[] = { 4.5, 6.7, 1.0, 2.2, 3.1, 5.7, 2.1, 0.9, 3.5, 73, 12.06 };
	size_t size = sizeof(array) / sizeof(double);
	// создание пустого вектора
	Vector v1(10);
	std::cout << "v1 (empty): " << v1.ToString() << std::endl;
	// создание вектора с инициализацией значений
	Vector v2(size, array);
	std::cout << "v2: " << v2.ToString() << std::endl;
	Vector v3(size - 3, array);
	std::cout << "v3: " << v3.ToString() << std::endl;
	// создание через конструктор копирования
	Vector v4(v2);
	std::cout << "v4: " << v4.ToString() << std::endl;
	// создание через конструктор копирования с заданием диапазона копирования
	Vector v5(v4, 1, -2);
	std::cout << "v5: " << v5.ToString() << std::endl;
	try {
		Vector v6(v2, 5, -8);
		std::cout << "v6: " << v6.ToString() << std::endl;
	}
	catch (const char* ex)
	{
		std::cout << "Error! " << ex << std::endl;
	}
	// создание через инициализацию элементами в конструкторе
	Vector v8(7, 4.5, 2.1, 3.3, 7.89, 3.4, 0.9, 1.1);
	std::cout << "v8: " << v8.ToString() << std::endl;
	// создание экземпляра через initializer_list
	Vector v9({ 1.2, 2.1, 1.3, 3.1, 1.4, 4.1, -1.5, -5.1 });
	std::cout << "v9: " << v9.ToString() << std::endl;

	// скалярное произведение
	std::cout << "v2 * v5: " << v2 * v5 << std::endl;
	// умножение на константу
	std::cout << "v5 * 8: " << (v5 * 8.0).ToString() << std::endl;
	// деление на константу
	v3 /= 2.0;
	std::cout << "v3 /= 2.0: " << v3.ToString() << std::endl;
	// сложение векторов
	Vector v7 = v3 + v4;
	std::cout << "v7 = v3 + v4: " << v7.ToString() << std::endl;
	// вычитание векторов
	v7 -= Vector(size, array);
	std::cout << "v7 -= v2: " << v7.ToString() << std::endl;
	// длина вектора
	std::cout << "v2 length: " << v2.Length() << std::endl;
	// разерность вектора
	std::cout << "v2 size: " << v2.Size() << std::endl;
	// отрицательная индексация
	std::cout << "v2(-4) = " << v2.Get(-4) << std::endl;
	// итерирование
	std::cout << "Iterating throw v4: ";
	for (Iterator& iter = v4.begin(); iter != v4.end(); ++iter)
		std::cout << *iter << std::ends;
	std::cout << std::endl;
	// единичный вектор
	std::cout << "ones(4): " << Vector::Ones(4).ToString() << std::endl;
}

void TestMatrix()
{
	double array1[] = { 5.5, 6.7, 2, 5, 1.1, 13, 1, 1, 3, 8.8, 6.6, -2.9 };
	double array2[] = { 4.5, 6.0, 3.0, 1.1, 2.2, 3.3, 9.9, 0.0, 1.0 };
	size_t size1 = sizeof(array1) / sizeof(double),
		size2 = sizeof(array2) / sizeof(double);
	// создание нулевой матрицы
	Matrix m1(5, 5);
	std::cout << "m1:\n" << m1.ToString() << std::endl;
	// создание с инициализацией
	Matrix m2(4, 3, array1);
	std::cout << "m2:\n" << m2.ToString() << std::endl;
	Matrix m3(3, 3, array2);
	std::cout << "m3:\n" << m3.ToString() << std::endl;
	// создание через копирование
	Matrix m4(m3);
	std::cout << "m4:\n" << m4.ToString() << std::endl;
	// копирование с заданием диапазонов
	Matrix m5(m4, -1, 2, 2, 2);
	std::cout << "m5:\n" << m5.ToString() << std::endl;
	Matrix m6(m2, 0, -1, -2, -1);
	std::cout << "m6:\n" << m6.ToString() << std::endl;
	// проверка, является ли матрица квадратной
	std::cout << "m2 is square: " << m2.IsSquare() << std::endl;
	std::cout << "m3 is square: " << m3.IsSquare() << std::endl;
	// перемножение матриц
	std::cout << "m2 * m3:\n" << (m2 * m3).ToString() << std::endl;
	// перемножение матрицы на другую и на константу
	Matrix m7 = m4 + m3;
	std::cout << "m7 = m4 + m3:\n" << m7.ToString() << std::endl;
	m7 /= 2;
	std::cout << "m7 /= 2:\n" << m7.ToString() << std::endl;
	// вычитание матриц
	try {
		std::cout << "m2 - m3:\n" << (m2 - m3).ToString() << std::endl;
	}
	catch (const char* ex)
	{
		std::cout << ex << std::endl;
	}
	// умножение на вектор
	Vector v = Vector::Ones(3);
	std::cout << "m2 * v:\n" << (m2 * v).ToString() << std::endl;
	// доступ по индексу к элементу
	std::cout << "m2(3, 1) = " << m2(3, 1) << std::endl;
	std::cout << "m2(-1, 1) = " << m2.Get(-1, 1) << std::endl;
	m2(2, 2) = 22;
	std::cout << "m2(2, 2) = 22: " << m2.ToString() << std::endl;
	// получение строки и столбца по индексу
	std::cout << "m3, row 0: " << m3.GetRow(0).ToString() << std::endl;
	std::cout << "m3, column 2: " << m3.GetColumn(2).ToString() << std::endl;
	m3.SetRow(1, Vector(3));
	m3.SetColumn(1, Vector(3));
	std::cout << "m3: \n" << m3.ToString() << std::endl;
	// единичная матрица
	Matrix m8 = Matrix::Identity(5);
	std::cout << "Identity(5): \n" << m8.ToString() << std::endl;
	// проверка, является ли матрица диагональной
	std::cout << "m3 is diagonal: " << m3.IsDiagonal() << std::endl;
	std::cout << "m8 is diagonal: " << m8.IsDiagonal() << std::endl;
	// итераторы
	std::cout << "m8:\n";
	for (auto iter = m8.begin(); iter != m8.end(); ++iter)
		std::cout << *iter << std::ends;
	std::cout << std::endl;
}

void TestPolynom()
{
	const double array[] = { 4.5, -0.67, 0.01, -1e4 };
	const size_t n = sizeof(array) / DOUBLE_SIZE;
	Polynom p1(7);
	std::cout << "p1: " << p1.ToString() << std::endl;
	
	Polynom p2(5, 5.0, 3.0, -1.0, 1.0, -2.0);
	std::cout << "p2: " << p2.ToString() << std::endl;
	Polynom p3 = p1 * p2;
	std::cout << p3.ToString() << std::endl;
}

void TestLinalg()
{
	double array[] = {
		3, 1, 5, 7, -4,
		-3, 9, 0, 0, 2,
		1, 1, 2, 1, 1,
		-12, -3, -4, 0, 0,
		8, 1, 4, 1, 5
	};
	size_t size = 5;
	Matrix A(size, size, array);
	
	std::cout << "Initial matrix:\n" << A.ToString() << std::endl;
	// QR-разложение
	Matrix Q, R;
	if (!linalg::QR(A, Q, R)) std::cout << "Failed to calculate QR-decomposition!\n";
	else {
		std::cout << "Q:\n" << Q.ToString() << "R:\n" << R.ToString();
		std::cout << "Q * R:\n" << (Q * R).ToString() << std::endl;
	}
	// определитель матрицы
	std::cout << "Det(A): " << linalg::Determinant(A) << std::endl << std::endl;
	// обращение матрицы
	std::cout << "Inversing testing!\n";
	Matrix I;
	if (!linalg::Inverse(A, I)) std::cout << "Matrix is degenerate!\n";
	else {
		std::cout << "A:\n" << A.ToString();
		std::cout << "I:\n" << I.ToString();
		std::cout << "I * A:\n" << (I * A).ToString() << std::endl;
	}
	// PLU-разложение
	std::cout << "PLU decomposition testing!\n";
	Vector P;
	size_t k;
	Matrix L, U;
	if (!linalg::PLU(A, L, U, P, k)) std::cout << "Matrix is degenerate!\n";
	else {
		std::cout << "L:\n" << L.ToString();
		std::cout << "U:\n" << U.ToString();
		std::cout << "L * U:\n" << (L * U).ToString();
		std::cout << "P: " << P.ToString() << std::endl;
		Matrix mP(size, size);
		for (size_t i = 0; i < size; ++i) mP(i, P[i]) = 1.0;
		std::cout << "P * A:\n" << (mP * A).ToString();
	}
	// сингулярное разложение матрицы
	//A = Matrix(3, 2, 4.0, 2.0, 1.0, -5.0, 3.2, 2.0);
	Matrix S, V;
	linalg::SVD(A, U, S, V);
	std::cout << "A:\n" << A.ToString();
	std::cout << "U * S * V:\n" << (U * S * V).ToString();
	// решение СЛАУ
	Matrix M(4, 4, 
		1.0, 2.0, 3.1, 4.2, 
		5.5, 2.0, 6.0, 9.1,
		2.2, -1.0, 1.0, 1.0, 
		3.3, 2.5, -1.2, -5.3);
	Vector B(4, 10.0, 0.0, -10.0, 0.0), X;
	if (!linalg::Solve(M, B, X)) std::cout << "Failed to solve!\n";
	else {
		std::cout << "A:\n" << M.ToString();
		std::cout << "B: " << B.ToString() << std::endl;
		std::cout << "X: " << X.ToString() << std::endl;
		std::cout << "A * X: " << (M * X).ToString() << std::endl;
	}
	// тестирование svd на матрице с большей разменостью
	M = Matrix(11, 9,
		{
			4.5, 1.2, -5.0, -3.3, 2.1, 1.2, 8.0, 7.7, 0.4, 
			0.0, 0.0, 0.0, 1.2, -3.3, -5.1, -8.9, -0.2, 0.7,
			-1.0, -1.0, -1.0, -29.0, 7.89, 12.0, 11.2, -3.4, 4.5,
			4.5, 5.8, 5.5, 4.4, 2.3, 1.2, 0.03, 12.3, -7.8, 
			-23.06, 0, 0, -5.11, -7.77, 8.8, -9.05, 2.55, 3.33,
			5.12, 1.2, 0, 5.5, -0.98, -0.554, -.777, 16, 17.909,
			1.0, 1.0, 1.0, 11.1, 1.2, 1.3, 1.4, 2.1, 3.1,
			-8.88, -0.9, -7.65, 5.65, -3.33, -2.22, 1.234, 0.001, 0,
			1.11, 1, 1, 0.0, 0, 0.3, 7.89, 45.6, -25.4, 
			-0.78, -45.6, 45.6, 2, 3, 4, 5, 6, 7,
			0.9876, -0.6789, 1.4, 3.2, -7.098, 6.58, 0.0007, 1e-6, 1.0
		});
	if (!linalg::SVD(M, U, S, V)) std::cout << "Failed to calculate svd!";
	else {
		std::cout << "\nA:\n" << M.ToString();
		std::cout << "U * S * V:\n" << (U * S * V).ToString();
	}
}

void TestNumerics()
{
	double x[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		y[10] = { 1.0, 1.3, 2.1, 3.3, 3.7, 4.5, 5.01, 6.0, 7.0, 7.67 };
	size_t n = 10;
	Polynom p;
	if (!num::PolyFromLeastSquares(1, n, x, y, p)) 
		std::cout << "Failed to calculate the least squares method!";
	else {
		std::cout << "x: ";
		for (size_t i = 0; i < n; ++i) std::cout << x[i] << std::ends;
		std::cout << "\ny: ";
		for (size_t i = 0; i < n; ++i) std::cout << y[i] << std::ends;
		std::cout << "\nValues by polynom: ";
		for (size_t i = 0; i < n; ++i) std::cout << p(x[i]) << std::ends;
		std::cout << "\nCoefficients: ";
		for (size_t i = 0; i < p.Degree() + 1; ++i)
			std::cout << p[i] << std::ends;
	}
	std::cout << std::endl;
}