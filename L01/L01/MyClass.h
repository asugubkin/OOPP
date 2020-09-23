#pragma once

class A
{
public:
	int m_A;
	A(int a)
	{
		m_A = a;
	}
};

class MyClass
{
public:
	int m_I = 123;
	A m_A;
	void f();
	void g()
	{

	}
	MyClass()
		:m_A(0), m_I(0)
	{
		std::cout << "MyClass()" << std::endl;
	}
	MyClass(int i)
		:m_A(i), m_I(i)
	{
		std::cout << "MyClass(" << i << ")" << std::endl;
	}
	
	~MyClass()
	{
		std::cout << "~MyClass(" << m_I << ")" << std::endl;
	}
};

