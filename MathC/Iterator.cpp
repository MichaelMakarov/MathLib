#include "Iterator.h"

Iterator operator+(const Iterator& iterator, const size_t shift)
{
	Iterator result;
	result.i_pValue = iterator.i_pValue + shift;
	return result;
}

Iterator operator-(const Iterator& iterator, const size_t shift)
{
	Iterator result;
	result.i_pValue = iterator.i_pValue - shift;
	return result;
}
