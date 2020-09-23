#include <iostream>

#include "MyClass.h"

void MyClass::f()
{
	std::cout << this->m_I << std::endl;
}