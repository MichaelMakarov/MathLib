#pragma once
#include "Iterator.h"

template<class T>
class Enumerable
{
protected:
	Iterator<T> e_iterFirst;			// итератор на начало
	Iterator<T> e_iterLast;				// итератор на конец

	// обновление итераторов для коллекции
	virtual void Invalidate() = 0;
};

