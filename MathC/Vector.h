#pragma once
#include "Constants.h"
#include "Enumerable.h"

// представление математического вектора 
class Vector : public Enumerable
{
private:
	double* v_pValues;						// массив значений
	size_t v_size;							// количество элементов в массиве

protected:
	// обновление значений итераторов
	void Invalidate() override;

public:
	// конструктор по-умолчанию
	Vector(const size_t size = 3); 
	// конструктор с заданием значений
	Vector(
		const size_t size,					// размер				
		const double* const pArray);		// массив значений
	// конструктор копирования
	Vector(const Vector& vector);
	// копирование среза элементов
	Vector(
		const Vector& vector,				// исходный вектор
		int firstIndex,						// индекс первого элемента
		int lastIndex);						// индекс последнего элемента
	// конструктор на основе задания значений
	Vector(
		const size_t size,					// размер вектора
		const double value,					// первое значение инициализации
		...);								// следующие значения для инициализации
	// конструктор на основе списка
	Vector(
		std::initializer_list<double> values// список значений
	);
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
	Iterator& begin() { return e_iterFirst; }
	// итератор на конец
	Iterator& end() { return e_iterLast; }

};

