#include "Header.h"

int gI = 0;

int& f(int i)
{
	return gI;
}