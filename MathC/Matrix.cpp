#include "Matrix.h"
#include <strstream>

void Matrix::Invalidate()
{
	e_iterFirst = Iterator(m_pValues);
	e_iterLast = e_iterFirst + m_nRows * m_nCols;
}

Matrix::Matrix(
	const size_t nRows, 
	const size_t nCols)
{
	if (nRows == 0 || nCols == 0) 
		throw "The dimensions of te matrix should be greater than zero!";
	m_nRows = nRows;
	m_nCols = nCols;
	m_pValues = new double[m_nCols * m_nRows];
	std::memset(m_pValues, 0, DOUBLE_SIZE * m_nRows * m_nCols);
	Invalidate();
}

Matrix::Matrix(
	const size_t nRows,
	const size_t nCols,
	const double* const pValues)
{
	if (nRows == 0 || nCols == 0)
		throw "The dimensions of the matrix should be greater than zero!";
	m_nRows = nRows;
	m_nCols = nCols;
	m_pValues = new double[m_nRows * m_nCols];
	std::memcpy(m_pValues, pValues, DOUBLE_SIZE * m_nRows * m_nCols);
	Invalidate();
}

Matrix::Matrix(const Matrix& matrix)
{
	m_nRows = matrix.m_nRows;
	m_nCols = matrix.m_nCols;
	m_pValues = new double[m_nRows * m_nCols];
	std::memcpy(m_pValues, matrix.m_pValues, DOUBLE_SIZE * m_nRows * m_nCols);
	Invalidate();
}

Matrix::Matrix(
	const Matrix& matrix, 
	int firstRowIndex, int lastRowIndex, 
	int firstColIndex, int lastColIndex)
{
	int nRows = static_cast<int>(matrix.m_nRows),
		nCols = static_cast<int>(matrix.m_nCols);
	if (firstRowIndex < 0) firstRowIndex += nRows;
	if (firstRowIndex >= nRows || firstRowIndex < 0) 
		throw "Invalid first row index!";
	if (lastRowIndex < 0) lastRowIndex += nRows;
	if (lastRowIndex >= nRows || lastRowIndex < 0)
		throw "Invalid last row index!";
	if (lastRowIndex < firstRowIndex)
		throw "Last row index can not be less than first one!";

	if (firstColIndex < 0) firstColIndex += nCols;
	if (firstColIndex >= nCols || firstColIndex < 0)
		throw "Invalid first column index!";
	if (lastColIndex < 0) lastColIndex += nCols;
	if (lastColIndex >= nCols || lastColIndex < 0)
		throw "Invalid last column index!";
	if (lastColIndex < firstColIndex)
		throw "Last column index can not be less than first one!";

	m_nRows = lastRowIndex - firstRowIndex + 1;
	m_nCols = lastColIndex - firstColIndex + 1;
	m_pValues = new double[m_nRows * m_nCols];
	for (size_t m = 0; m < m_nRows; ++m)
		for (size_t n = 0; n < m_nCols; ++n)
			m_pValues[m * m_nCols + n] = 
				matrix.m_pValues[(firstRowIndex + m) * matrix.m_nCols + firstColIndex + n];
	Invalidate();
}

Matrix::Matrix(const size_t nRows, const size_t nCols, const double value, ...)
{
	va_list args;
	if (nRows == 0 || nCols == 0) throw "Invalid dimensions!";
	__crt_va_start(args, nCols);
	m_nRows = nRows;
	m_nCols = nCols;
	m_pValues = new double[m_nRows * m_nCols];
	m_pValues[0] = value;
	for (size_t i = 0; i < m_nRows * m_nCols; ++i)
		m_pValues[i] = __crt_va_arg(args, double);
	__crt_va_end(args);
}

Matrix::Matrix(
	const size_t nRows, 
	const size_t nCols,
	const std::initializer_list<double> values)
{
	if (nRows == 0 || nCols == 0)
		throw "The dimensions of the matrix should be greater than zero!";
	m_nRows = nRows;
	m_nCols = nCols;
	m_pValues = new double[m_nRows * m_nCols];
	size_t i = 0;
	for (auto v : values) m_pValues[i++] = v;
}

Matrix::~Matrix()
{
	delete[] m_pValues;
	m_pValues = nullptr;
	m_nRows = m_nCols = 0;
}

const size_t Matrix::RowsNumber() const
{
	return m_nRows;
}

const size_t Matrix::ColsNumber() const
{
	return m_nCols;
}

const double Matrix::Norm() const
{
	double result = 0.0;
	double buf = 0.0;
	for (size_t m = 0; m < m_nRows; ++m)
		for (size_t n = 0; n < m_nCols; ++n)
		{
			buf = m_pValues[m * m_nCols + n];
			result += buf * buf;
		}
	return sqrt(result);
}

bool Matrix::IsSquare() const
{
	return m_nRows == m_nCols;
}

bool Matrix::IsDiagonal(const double precision) const
{
	for (size_t m = 0; m < m_nRows; ++m)
		for (size_t n = 0; n < m_nCols; ++n)
		{
			if (m == n) continue;
			if (abs(m_pValues[m * m_nCols + n]) > precision)
				return false;
		}
	return true;
}

double* Matrix::Values() const
{
	return m_pValues;
}

const char* Matrix::ToString() const
{
	std::strstream str;
	size_t last = m_nRows - 1;
	str << "( ";
	for (size_t m = 0; m < last; ++m)
	{
		str << "( ";
		for (size_t n = 0; n < m_nCols; ++n)
			str << m_pValues[m * m_nCols + n] << " ";
		str << ")\n  ";
	}
	str << "( ";
	for (size_t n = 0; n < m_nCols; ++n)
		str << m_pValues[last * m_nCols + n] << " ";
	str << ") )\n";
	str << '\0';
	return str.str();
}

Matrix& Matrix::Transpose()
{
	double buf;
	size_t m, n;
	double* pValues = new double[m_nRows * m_nCols];
	for (m = 0; m < m_nRows; ++m)
		for (n = 0; n < m_nCols; ++n)
			pValues[n * m_nRows + m] = m_pValues[m * m_nCols + n];
	delete[] m_pValues;
	m_pValues = pValues;
	std::swap(m_nRows, m_nCols);
	return *this;
}

double& Matrix::operator()(
	const size_t rowIndex, 
	const size_t colIndex) const
{
	if (rowIndex >= m_nRows) throw "Invalid row index!";
	if (colIndex >= m_nCols) throw "Invalid column index!";
	return m_pValues[rowIndex * m_nCols + colIndex];
}

double& Matrix::Get(
	int rowIndex, 
	int colIndex) const
{
	int nRows = static_cast<int>(m_nRows),
		nCols = static_cast<int>(m_nCols);
	if (rowIndex < 0) rowIndex += nRows;
	if (rowIndex >= nRows || rowIndex < 0)
		throw "Invalid row index!";
	if (colIndex < 0) colIndex += nCols;
	if (colIndex >= nCols || colIndex < 0)
		throw "Invalid column index!";
	return m_pValues[rowIndex * nCols + colIndex];
}

Vector Matrix::GetRow(int index) const
{
	int nRows = static_cast<int>(m_nRows),
		nCols = static_cast<int>(m_nCols);
	if (index < 0) index += nRows;
	if (index >= nRows || index < 0) throw "Invalid row index!";
	Vector row(nCols);
	for (int i = 0; i < nCols; ++i)
		row[i] = m_pValues[index * nCols + i];
	return row;
}

Vector Matrix::GetColumn(int index) const
{
	int nRows = static_cast<int>(m_nRows),
		nCols = static_cast<int>(m_nCols);
	if (index < 0) index += nCols;
	if (index >= nCols || index < 0) throw "Invalid column index!";
	Vector column(nRows);
	for (int i = 0; i < nRows; ++i)
		column[i] = m_pValues[i * nCols + index];
	return column;
}

bool Matrix::SetRow(int index, const Vector& values)
{
	if (m_nCols != values.Size()) return false;
	int nRows = static_cast<int>(m_nRows),
		nCols = static_cast<int>(m_nCols);
	if (index < 0) index += nRows;
	if (index >= nRows || index < 0) throw "Invalid row index!";
	for (int i = 0; i < nCols; ++i)
		m_pValues[index * nCols + i] = values[i];
	return true;
}

bool Matrix::SetColumn(int index, const Vector& values)
{
	if (m_nRows != values.Size()) return false;
	int nRows = static_cast<int>(m_nRows),
		nCols = static_cast<int>(m_nCols);
	if (index < 0) index += nRows;
	if (index >= nRows || index < 0) throw "Invalid row index!";
	for (int i = 0; i < nCols; ++i)
		m_pValues[i * nCols + index] = values[i];
	return true;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	m_nRows = matrix.m_nRows;
	m_nCols = matrix.m_nCols;
	if (m_pValues) delete[] m_pValues;
	m_pValues = new double[m_nRows * m_nCols];
	std::memcpy(m_pValues, matrix.m_pValues, DOUBLE_SIZE * m_nRows * m_nCols);
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
	if (m_nRows != matrix.m_nRows ||
		m_nCols != matrix.m_nCols)
		throw "The dimensions of the matrices are not equal!";
	for (size_t i = 0; i < m_nRows * m_nCols; ++i)
			m_pValues[i] += matrix.m_pValues[i];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
	if (m_nRows != matrix.m_nRows ||
		m_nCols != matrix.m_nCols)
		throw "The dimensions of the matrices are not equal!";
	for (size_t i = 0; i < m_nRows * m_nCols; ++i)
		m_pValues[i] -= matrix.m_pValues[i];
	return *this;
}

Matrix& Matrix::operator*=(const double number)
{
	for (size_t i = 0; i < m_nRows * m_nCols; ++i)
		m_pValues[i] *= number;
	return *this;
}

Matrix& Matrix::operator/=(const double number)
{
	if (abs(number) < 1e-16) throw "The number is equal zero!";
	for (size_t i = 0; i < m_nRows * m_nCols; ++i)
		m_pValues[i] /= number;
	return *this;
}

Matrix Matrix::Identity(size_t size)
{
	if (size == 0) throw "the size of the matrix should be greater than zero!";
	Matrix matrix(size, size);
	for (size_t i = 0; i < size; ++i)
		matrix.m_pValues[i * size + i] = 1.0;
	return matrix;
}

Matrix operator+(const Matrix& first, const Matrix& second)
{
	if (first.m_nRows != second.m_nRows ||
		first.m_nCols != second.m_nCols)
		throw "The dimensions of the matrices are not equal!";
	Matrix result(first.m_nRows, first.m_nCols);
	for (size_t i = 0; i < first.m_nRows * first.m_nCols; ++i)
		result.m_pValues[i] = first.m_pValues[i] + second.m_pValues[i];
	return result;
}

Matrix operator-(const Matrix& first, const Matrix& second)
{
	if (first.m_nRows != second.m_nRows ||
		first.m_nCols != second.m_nCols)
		throw "The dimensions of the matrices are not equal!";
	Matrix result(first.m_nRows, first.m_nCols);
	for (size_t i = 0; i < first.m_nRows * first.m_nCols; ++i)
		result.m_pValues[i] = first.m_pValues[i] - second.m_pValues[i];
	return result;
}

Matrix operator*(const Matrix& first, const Matrix& second)
{
	if (first.m_nCols != second.m_nRows)
		throw "The dimensions of the matrices are inconsistent!";
	Matrix result(first.m_nRows, second.m_nCols);
	for (size_t m = 0; m < first.m_nRows; ++m)
		for (size_t k = 0; k < second.m_nRows; ++k)
			for (size_t n = 0; n < second.m_nCols; ++n)
				result.m_pValues[m * result.m_nCols + n] += 
					first.m_pValues[m * first.m_nCols + k] * 
						second.m_pValues[k * second.m_nCols + n];
	return result;
}

Matrix operator*(const Matrix& matrix, const double number)
{
	Matrix result(matrix);
	for (size_t i = 0; i < result.m_nRows * result.m_nCols; ++i)
		result.m_pValues[i] *= number;
	return result;
}

Matrix operator/(const Matrix& matrix, const double number)
{
	if (abs(number) < 1e-16) throw "The number is equal zero!";
	Matrix result(matrix);
	for (size_t i = 0; i < result.m_nRows * result.m_nCols; ++i)
		result.m_pValues[i] /= number;
}

Vector operator*(const Matrix& matrix, const Vector& vector)
{
	if (matrix.m_nCols != vector.Size())
		throw "The number of the columns is not equal the size of the vector!";
	Vector result(matrix.m_nRows);
	for (size_t m = 0; m < matrix.m_nRows; ++m)
		for (size_t n = 0; n < matrix.m_nCols; ++n)
			result[m] += matrix.m_pValues[m * matrix.m_nCols + n] * vector[n];
	return result;
}
