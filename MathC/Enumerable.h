#pragma once
#include "Iterator.h"

class Enumerable
{
protected:
	Iterator e_iterFirst;			// итератор на начало
	Iterator e_iterLast;			// итератор на конец

	// обновление итераторов для коллекции
	virtual void Invalidate() = 0;
};

