#include "Vector.h"
#include <algorithm>
#include <strstream>


void Vector::Invalidate()
{
	e_iterFirst = Iterator<double>(v_pValues);
	e_iterLast = e_iterFirst + v_size;
}

Vector::Vector(const size_t size)
{
	if (size == 0) throw std::exception("Invalid size!");
	v_size = size;
	v_pValues = new double[v_size];
	std::memset(v_pValues, 0, v_size * DOUBLE_SIZE);
	Invalidate();
}

Vector::Vector(const size_t size, const double* const pArray)
{
	if (size == 0) throw std::exception("Invalid size!");
	if (!pArray) throw std::exception("Invalid array!");
	v_size = size;
	v_pValues = new double[v_size];
	std::memcpy(v_pValues, pArray, v_size * DOUBLE_SIZE);
	Invalidate();
}

Vector::Vector(const Vector& vector)
{
	v_size = vector.v_size;
	v_pValues = new double[v_size];
	std::memcpy(v_pValues, vector.v_pValues, v_size * DOUBLE_SIZE);
	Invalidate();
}

Vector::Vector(const size_t size, const double value, ...)
{
	va_list args;
	if (size == 0) throw std::exception("Invalid size!");
	__crt_va_start(args, value);
	v_size = size;
	v_pValues = new double[v_size];
	v_pValues[0] = value;
	for (size_t i = 1; i < size; ++i)
		v_pValues[i] = __crt_va_arg(args, double);
	__crt_va_end(args);
	Invalidate();
}

Vector::Vector(std::initializer_list<double> values)
{
	if (values.size() == 0) throw std::exception("Invalid number of values!");
	v_size = values.size();
	v_pValues = new double[v_size];
	size_t i = 0;
	for (auto v : values) v_pValues[i++] = v;
	Invalidate();
}

Vector::~Vector()
{
	delete[] v_pValues;
	v_pValues = nullptr;
	v_size = 0;
}

const size_t Vector::Size() const
{
	return v_size;
}

double* Vector::Values() const
{
	return v_pValues;
}

const double Vector::Length() const
{
	double result = 0.0;
	for (size_t i = 0; i < v_size; ++i)
		result += v_pValues[i] * v_pValues[i];
	return sqrt(result);
}

const char* Vector::ToString() const
{
	std::strstream str;
	str << "( ";
	for (size_t i = 0; i < v_size; ++i)
		str << v_pValues[i] << " ";
	str << ")";
	str << '\0';
	return str.str();
}

double& Vector::operator[](const size_t index) const
{
	if (index >= v_size) throw std::exception("Invalid index!");
	return v_pValues[index];
}

double& Vector::Get(int index) const
{
	if (index < 0) index += v_size;
	if (index > v_size || index < 0) throw std::exception("Invalid index!");
	return v_pValues[index];
}

Vector& Vector::Normalize()
{
	double length = Length();
	for (size_t i = 0; i < v_size; ++i)
		v_pValues[i] /= length;
	return *this;
}

Vector& Vector::operator=(const Vector& vector)
{
	v_size = vector.v_size;
	if (v_pValues) delete[] v_pValues;
	v_pValues = new double[v_size];
	std::memcpy(v_pValues, vector.v_pValues, v_size * DOUBLE_SIZE);
	Invalidate();
	return *this;
}

Vector& Vector::operator+=(const Vector& vector)
{
	if (vector.v_size > v_size)
	{
		double* pValues = v_pValues;
		v_pValues = new double[vector.v_size];
		std::memcpy(v_pValues, pValues, v_size * DOUBLE_SIZE);
		std::memset(&v_pValues[v_size], 0, (vector.v_size - v_size) * DOUBLE_SIZE);
		v_size = vector.v_size;
		Invalidate();
		delete[] pValues;
	}
	for (size_t i = 0; i < vector.v_size; ++i)
		v_pValues[i] += vector.v_pValues[i];
	return *this;
}

Vector& Vector::operator-=(const Vector& vector)
{
	if (vector.v_size > v_size)
	{
		double* pValues = v_pValues;
		v_pValues = new double[vector.v_size];
		std::memcpy(v_pValues, pValues, v_size * DOUBLE_SIZE);
		std::memset(&v_pValues[v_size], 0, (vector.v_size - v_size) * DOUBLE_SIZE);
		v_size = vector.v_size;
		Invalidate();
		delete[] pValues;
	}
	for (size_t i = 0; i < v_size; ++i)
		v_pValues[i] -= vector.v_pValues[i];
	return *this;
}

Vector& Vector::operator*=(double number)
{
	for (size_t i = 0; i < v_size; ++i)
		v_pValues[i] *= number;
	return *this;
}

Vector& Vector::operator/=(double number)
{
	if (abs(number) < 1e-16) throw std::exception("Invalid number to divide!");
	for (size_t i = 0; i < v_size; ++i)
		v_pValues[i] /= number;
	return *this;
}

Vector Vector::Ones(const size_t size)
{
	Vector result(size);
	for (size_t i = 0; i < size; ++i)
		result.v_pValues[i] = 1.0;
	return result;
}

Vector operator+(const Vector& first, const Vector& second)
{
	if (first.v_size > second.v_size)
	{
		Vector result(first);
		for (size_t i = 0; i < second.v_size; ++i)
			result.v_pValues[i] += second.v_pValues[i];
		return result;
	}
	else {
		Vector result(second);
		for (size_t i = 0; i < first.v_size; ++i)
			result.v_pValues[i] += first.v_pValues[i];
		return result;
	}
}

Vector operator-(const Vector& first, const Vector& second)
{
	if (first.v_size >= second.v_size)
	{
		Vector result(first.v_size);
		for (size_t i = 0; i < second.v_size; ++i)
			result.v_pValues[i] = first.v_pValues[i] - second.v_pValues[i];
		return result;
	}
	else {
		Vector result(second.v_size);
		for (size_t i = 0; i < first.v_size; ++i)
			result.v_pValues[i] = first.v_pValues[i] - second.v_pValues[i];
		for (size_t i = first.v_size; i < second.v_size; ++i)
			result.v_pValues[i] = -second.v_pValues[i];
		return result;
	}
}

const double operator*(const Vector& first, const Vector& second)
{
	double result = 0.0;
	size_t size = first.v_size <= second.v_size ? first.v_size : second.v_size;
	for (size_t i = 0; i < size; ++i)
		result += first.v_pValues[i] * second.v_pValues[i];
	return result;
}

Vector operator/(const Vector& vector, const double number)
{
	Vector result(vector);
	for (size_t i = 0; i < result.v_size; ++i)
		result.v_pValues[i] /= number;
	return result;
}

Vector operator*(const Vector& vector, const double number)
{
	Vector result(vector);
	for (size_t i = 0; i < result.v_size; ++i)
		result.v_pValues[i] *= number;
	return result;
}
