#pragma once
#include "Constants.h"
#include "Enumerable.h"

// представление математического вектора 
class Vector : public Enumerable<double>
{
private:
	double* v_pValues;						// массив значений
	size_t v_size;							// количество элементов в массиве

protected:
	// обновление значений итераторов
	void Invalidate() override;

public:
	// Создание нулевого вектора заданной размерности.
	Vector(const size_t size = 3); 
	// Создание вектора заданной размерности с заданием значений координат.
	Vector(
		const size_t size,				
		const double* const pArray);
	// конструктор копирования
	Vector(const Vector& vector);
	// Создание вектора заданной размерности с заданием значений координат.
	Vector(
		const size_t size,
		const double value,
		...);
	// Создание вектора через список значений координат.
	Vector(std::initializer_list<double> values);
	// деструктор
	~Vector();

	// количество координат вектора
	const size_t Size() const;
	// массив значений координат
	double* Values() const;
	// длина вектора (евклидова норма)
	const double Length() const;

	// строковое представление для вывода
	const char* ToString() const;

	// индексация
	double& operator [](const size_t index) const;
	// индексация с поддержкой отрицательных индексов
	// ( -1 - последний элемент, -2 - предпоследний, -3 - предпердпоследний и т.д.)
	double& Get(int index) const;
	// нормализация вектора
	Vector& Normalize();

	// присвоение через копирование
	Vector& operator =(const Vector& vector);
	// сложение
	Vector& operator += (const Vector& vector);
	// вычитание
	Vector& operator -= (const Vector& vector);
	// умножение на число
	Vector& operator *= (double number);
	// деление на число
	Vector& operator /= (double number);

	// сложение векторов
	friend Vector operator + (const Vector& first, const Vector& second);
	// вычитание векторов
	friend Vector operator - (const Vector& first, const Vector& second);
	// скалярное умножение векторов
	friend const double operator * (const Vector& first, const Vector& second);
	// деление вектора на число покоординатно
	friend Vector operator / (const Vector& vector, const double number);
	// умножение вектора на число покоординатно
	friend Vector operator * (const Vector& vector, const double number);

	// вектор из единиц
	static Vector Ones(const size_t size);

	// итератор на первый элемент
	Iterator<double>& begin() { return e_iterFirst;	}
	// итератор на конец
	Iterator<double>& end() { return e_iterLast; }
};

