#pragma once
#include "Vector.h"

// представление матрицы
class Matrix : public Enumerable
{
private:
	double* m_pValues;							// массив со значениями
	size_t m_nRows;								// количсетво строк
	size_t m_nCols;								// количество столбцов

protected:
	// обновление итераторов
	void Invalidate() override;

public:
	// конструктор по умолчанию (матрица из нулей)
	Matrix(
		const size_t nRows = 3,					// количество строк
		const size_t nCols = 3);				// количество столбцов
	// конструктор с копированием эелементов из одномерного массива
	Matrix(
		const size_t nRows,						// количество строк
		const size_t nCols,						// количество столбцов
		const double* const pValues);			// массив со значениями для матрицы
	// конструктор копирования параметров и значений матрицы
	Matrix(const Matrix& matrix);
	// копирование среза матрицы по строкам и столбцам, включая последние элементы
	Matrix(
		const Matrix& matrix,					// матрица
		int firstRowIndex,						// индекс первой строки
		int lastRowIndex,						// индекс последней строки
		int firstColIndex,						// индекс первого столбца
		int lastColIndex);						// индекс последнего столбца
	// конструктор на основе непосредственного задания элементов
	Matrix(
		const size_t nRows,						// количество строк
		const size_t nCols,						// количество столбцов
		const double value,						// первое значение инициализации
		...);									// следующие значения инициализации
	// конструктор на основе списка
	Matrix(
		const size_t nRows,						// количество строк
		const size_t nCols,						// количество столбцов
		const std::initializer_list<double> values);
	// деструктор
	~Matrix();

	// количество строк в матрице
	const size_t RowsNumber() const;
	// количество столбцов в матрице
	const size_t ColsNumber() const;
	// норма матрицы (норма Фробениуса)
	const double Norm() const;
	// флаг того, что матрица является квадратной
	bool IsSquare() const;
	// флаг того, что матрица является диагональной
	bool IsDiagonal(
		const double precision = 1e-15			// порог учета элементов матрицы
	) const;
	// указатель на массив элементов матрицы
	double* Values() const;
	// строковое представление матрицы
	const char* ToString() const;
	// транспонирование
	Matrix& Transpose();

	// оператор индексации
	double& operator ()(
		const size_t rowIndex,					// индекс строки
		const size_t colIndex					// индекс столбца
	) const;
	// индексация с поддержкой отрицательных индексов,
	// где -1 - последний элемент с конца,
	// -2 - предполседний, -3 - предпредпоследний и т.д.
	double& Get(
		int rowIndex,							// индекс строки
		int colIndex							// индекс столбца
	) const;
	// возрат строки по индексу (поддерживаются отрицательные индексы)
	Vector GetRow(int index) const;
	// возврат столбца по индексу (поддерживаются отрицательные индексы)
	Vector GetColumn(int index) const;
	// задание значений строки по индексу (поддерживаются отрицательные индексы)
	bool SetRow(
		int index,								// индекс строки матрицы 
		const Vector& values);						// вектор значений
	// задание значений столбца по индексу (поддерживаются отрицательные индексы)
	bool SetColumn(
		int index,								// индекс столбца матрицы
		const Vector& values);						// вектор значений
	
	// оператор присваивания
	Matrix& operator = (const Matrix& matrix);
	// сложение с матрицой
	Matrix& operator += (const Matrix& matrix);
	// вычитание матрицы
	Matrix& operator -= (const Matrix& matrix);
	// умножение на число
	Matrix& operator *= (const double number);
	// деление на число
	Matrix& operator /= (const double number);

	// сложение матриц
	friend Matrix operator + (const Matrix& first, const Matrix& second);
	// вычитание матриц
	friend Matrix operator - (const Matrix& first, const Matrix& second);
	// умножение матриц
	friend Matrix operator * (const Matrix& first, const Matrix& second);
	// умножение на число
	friend Matrix operator * (const Matrix& matrix, const double number);
	// деление на число
	friend Matrix operator / (const Matrix& matrix, const double number);
	// умножение на вектор
	friend Vector operator * (const Matrix& matrix, const Vector& vector);

	// единичная матрица заданной размерности
	static Matrix Identity(size_t size);

	// итератор на первый элемент матрицы
	Iterator& begin() { return e_iterFirst; }
	// итератор на конец
	Iterator& end() { return e_iterLast; }
};

