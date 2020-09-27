#pragma once
#include <iterator>

// двунаправленный итератор
template<class T>
class Iterator
{
protected:
	T* i_pValue;			// указатель на значение

public:
	// конструктор по-умолчанию
	Iterator() : i_pValue(nullptr) {}
	// конструктор с присовением значения
	Iterator(T* pValue) : i_pValue(pValue) {}
	// конструктор копирования
	Iterator(const Iterator& other) : i_pValue(other.i_pValue) {}
	// деструктор
	~Iterator() {}

	// проерка на неравенство
	bool operator != (const Iterator& other) { return i_pValue != other.i_pValue; }
	// проверка на равенство
	bool operator == (const Iterator& other) { return i_pValue == other.i_pValue; }
	// разыменование итератора как указателя
	T& operator * () { return *i_pValue; }
	// доступ к указателю
	T* operator ->() { return i_pValue; }
	// оператор присвоения
	Iterator operator = (const Iterator& other) { i_pValue = other.i_pValue; return *this; }
	// сдвиг вправо
	Iterator& operator ++ () { ++i_pValue; return *this; }
	// сдвиг влево
	Iterator& operator -- () { --i_pValue; return *this; }
	// сдвиг вправо на фиксированное значение
	friend Iterator operator + (const Iterator& iterator, const size_t shift)
	{
		return Iterator(iterator.i_pValue + shift);
	}
	// сдвиг влево на фиксированное значение
	friend Iterator operator - (const Iterator& iterator, const size_t shift)
	{
		return Iterator(iterator.i_pValue - shift);
	}

};