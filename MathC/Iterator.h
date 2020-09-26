#pragma once
#include <iterator>

// двунаправленный итератор на значения типа double
class Iterator : public std::iterator<std::bidirectional_iterator_tag, double>
{
private:
	double* i_pValue;			// указатель на значение

public:
	// конструктор по-умолчанию
	Iterator() : i_pValue(nullptr) {}
	// конструктор с присовением значения
	Iterator(double* value) : i_pValue(value) {}
	// конструктор копирования
	Iterator(const Iterator& other) : i_pValue(other.i_pValue) {}

	// проерка на неравенство
	bool operator != (const Iterator& other) { return i_pValue != other.i_pValue; }
	// проверка на равенство
	bool operator == (const Iterator& other) { return i_pValue == other.i_pValue; }
	// разыменование итератора как указателя
	double& operator * () { return *i_pValue; }
	// доступ к указателю
	double* operator ->() { return i_pValue; }
	// оператор присвоения
	Iterator operator = (const Iterator& other) { i_pValue = other.i_pValue; return *this; }
	// сдвиг вправо
	Iterator& operator ++ () { i_pValue++; return *this; }
	// сдвиг влево
	Iterator& operator -- () { i_pValue--; return *this; }
	// сдвиг вправо на фиксированное значение
	friend Iterator operator + (const Iterator& iterator, const size_t shift);
	// сдвиг влево на фиксированное значение
	friend Iterator operator - (const Iterator& iterator, const size_t shift);

};

