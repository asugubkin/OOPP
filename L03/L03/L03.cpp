// L03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L03.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region Functions

#pragma region Macros

#define sqr1(x) x*x
/*
	sqr1(a)		a*a
	sqr1(a+b)	a+b*a+b
*/

#define sqr2(x) (x)*(x)
/*
	sqr2(a+b)	(a+b)*(a+b)
	sqr2(a++)	(a++)*(a++)
*/

#pragma endregion

#pragma region Inline

inline double sqr3(double x)
{
	return x * x;
}

inline int max1(int a, int b)
{
	return (a > b)?a:b;
}

inline string max1(string a, string b)
{
	return (a > b) ? a : b;
}

#pragma endregion

#pragma region Templates

template <class T> inline T max2(T a, T b)
{
	return (a > b) ? a : b;
}

#pragma region Explicit
inline char* max22(char* a, char* b)
{
	return (strcmp(a,b) > 0) ? a : b;
}
#pragma endregion

template <class List> inline void ClearList(List& lst)
{
	for (auto& o : lst)
		delete o;
	lst.clear();
}

void start1()
{
	int a = 1, b = 2;
	string s1("abc"), s2("qwe");
	char sz1[] = "abc", sz2[] = "qwe", sz3[] = "cde";

	cout << max2(a, b) << endl;
	cout << max2(s1, s2) << endl;
	cout << max2(sz1, sz2) << endl;
	cout << max2(sz2, sz3) << endl;
	cout << max2<string>(sz1, sz2) << endl;
}

#pragma region Variadic

inline void writeln()
{
	cout << endl;
}

template <class T, typename... Args> inline void writeln(T& value, const Args & ... args)
{
	cout << value << " ";
	writeln(args...);
}

void start2()
{
	// return;
	string s("asd");
	writeln("------------------", 1, "s = ", s);
}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Classes
#pragma region ArrayInt

class ArrayInt
{
	int* m_pData;
	int m_N;
public:
	ArrayInt(int n)
		:m_N(n)
	{
		m_pData = new int[m_N];
	}

	~ArrayInt()
	{
		delete[] m_pData;
	}

	int& get(int i)
	{
		return m_pData[i % m_N];
	}
};

void start3()
{
	return;
	writeln("------------------ 3");
	ArrayInt a(10);
	for (int i = 0; i < 100; ++i)
	{
		a.get(i) = i;
	}
	for (int i = 0; i < 100; ++i)
	{
		cout << a.get(i) << endl;
	}
}
#pragma endregion
#pragma region Array<T>

template<class T>
class Array
{
protected:
	T* m_pData;
	int m_N;
public:
	Array(int n)
		:m_N(n)
	{
		m_pData = new T[m_N];
	}

	~Array()
	{
		delete[] m_pData;
	}

	virtual T& get(int i)
	{
		return m_pData[i % m_N];
	}

#pragma region Operators

	Array(Array<T>& a)
	{
		if (a.m_pData != m_pData)
		{
			delete[] m_pData;
			m_N = a.m_N;
			m_pData = new T[m_N];
			for (int i = 0; i < m_N; ++i)
			{
				m_pData[i] = a.m_pData[i];
			}
		}
	}

	Array<T>& operator = (Array<T>& a)
	{
		if (a.m_pData != m_pData)
		{
			delete[] m_pData;
			m_N = a.m_N;
			m_pData = new T[m_N];
			for (int i = 0; i < m_N; ++i)
			{
				m_pData[i] = a.m_pData[i];
			}
		}
		return *this;
	}

	Array<T>& operator = (const T& v)
	{
		for(int i = 0; i<m_N; ++i)
		{
			m_pData[i] = v;
		}
		return *this;
	}

	Array<T>& operator += (const T& v)
	{
		for (int i = 0; i < m_N; ++i)
		{
			m_pData[i] += v;
		}
		return *this;
	}
		
	Array<T>& operator ++ ()
	{
		writeln("prefix ++");
		(*this) += 1;
		return *this;
	}


	Array<T>& operator ++ (int)
	{
		writeln("postfix ++");
		(*this) += 1;
		return *this;
	}

	T& operator[](int i)
	{
		return get(i);
	}

	T& operator()(int i) const
	{
		return m_pData[i % m_N];
	}

	operator int() const
	{
		return m_N;
	}


	

#pragma endregion
};

void start4()
{
	return;
	writeln("------------------ 4");
	Array<int> a(10);
	for (int i = 0; i < 100; ++i)
	{
		a.get(i) = i;
	}
	for (int i = 0; i < 100; ++i)
	{
		cout << a.get(i) << endl;
	}
}
#pragma endregion
#pragma region ArrayN<T>

template<typename T=int, int N=10>
class ArrayN
{
	T* m_pData;
public:
	ArrayN()
	{
		m_pData = new T[N];
	}

	~ArrayN()
	{
		delete[] m_pData;
	}

	T& get(int i)
	{
		return m_pData[i % N];
	}
};

void start5()
{
	return;
	writeln("------------------ 5");
	ArrayN<int, 10> a;
	ArrayN<int> b;
	ArrayN<> c;
	for (int i = 0; i < 100; ++i)
	{
		a.get(i) = i;
	}
	for (int i = 0; i < 100; ++i)
	{
		cout << a.get(i) << endl;
	}
}
#pragma endregion
#pragma endregion

#pragma region Operators

template<class T>
Array<T>& operator -= (Array<T>& a, const T& v)
{
	int n = a;
	for (int i = 0; i < n; ++i)
	{
		a[i] -= v;
	}
	return a;
}

template<class T>
ostream& operator<< (ostream& out, const Array<T>& a)
{
	int n = a;
	out << "[";
	for (int i = 0; i < n; ++i)
	{
		if (i)
			out << ", ";
		out << a(i);
	}
	out << "]";
	return out;
}

istream& operator >> (istream& in, CString& s)
{
	string tmp;
	in >> tmp;
	s = tmp.c_str();
	return in;
}

CArchive& operator << (CArchive& ar, string& s)
{
	CString tmp(s.c_str());
	ar << tmp;
	return ar;
}

CArchive& operator >> (CArchive& ar, string& s)
{
	CString tmp;
	ar >> tmp;
	s = tmp;
	return ar;
}

void start6()
{
	return;
	writeln("------------------ 6");
	Array<int> a(10);
	for (int i = 0; i < 100; ++i)
	{
		a[i] = i;
	}
	Array<int> b(50);
	b = a;
	Array<int> c(5);
	c = 10;
	b += 5; // b.operator+=(5)
	b++;
	++b;
	c -= 1; // operator-=(ñ, 1)
	writeln(a, b, c);
}

#pragma endregion

#pragma region Namespaces

void f()
{

}

namespace NameA
{
	int i;
	void f() 
	{
		i = 1;
	}
}

namespace NameA
{
	class A {};
}

namespace NameB
{
	int i;
	void f() 
	{
		using NameA::i;
		NameA::f();
		::f();
	}
}

namespace NameC
{
	using namespace NameA;
	using namespace NameB;
	void g()
	{
		NameA::f();
		NameB::f();
	}
}

namespace Dumb
{
	template<class T>
	class Array: public ::Array<T>
	{
		T m_Tmp;
	public:
		using ::Array<T>::Array;
		using ::Array<T>::operator=;
		
		virtual T& get(int i)
		{
			if (i < 0 || i >= ::Array<T>::m_N)
				return m_Tmp;
			return ::Array<T>::get(i);
		}
	};
}

void start7()
{
	return;
	writeln("------------------ 7");
	Dumb::Array<int> a(10);
	for (int i = 0; i < 100; ++i)
	{
		a[i] = i;
	}
	for (int i = 0; i < 100; ++i)
	{
		cout << a[i];
	}
	Dumb::Array<int> b(50);
	b = a;
	Dumb::Array<int> c(5);
	c = 10;
	b += 5; // b.operator+=(5)
	b++;
	++b;
	c -= 1; // operator-=(ñ, 1)
	writeln(a, b, c);
}
#pragma endregion

#pragma region Exceptions

namespace Strict
{
	template<class T>
	class Array : public ::Array<T>
	{
	public:
		using ::Array<T>::Array;
		using ::Array<T>::operator=;

		virtual T& get(int i)
		{
			if (i < 0 || i >= ::Array<T>::m_N)
				throw out_of_range("bad index");
			return ::Array<T>::get(i);
		}
	};
}

void start8()
{
	return;
	writeln("------------------ 8");
	try
	{
		Strict::Array<int> a(10);
		Strict::Array<int> b(50);
		b = a;
		Strict::Array<int> c(5);
		c = 10;
		b += 5; // b.operator+=(5)
		b++;
		++b;
		c -= 1; // operator-=(ñ, 1)
		writeln(a, b, c);
		
		if (true)
			throw 1;
		
		for (int i = 0; i < 100; ++i)
		{
			a[i] = i;
		}
		for (int i = 0; i < 100; ++i)
		{
			cout << a[i];
		}
	}
	catch (int i)
	{
		cout << "int ex:" << i << endl;
	}
	catch (out_of_range& ex)
	{
		cout << "out_of_range:" << ex.what() << endl;
	}
	catch (logic_error& ex)
	{
		cout << "logic_error:" << ex.what() << endl;
	}
	catch (runtime_error& ex)
	{
		cout << "runtime_error:" << ex.what() << endl;
	}
	catch (exception& ex)
	{
		cout << "exception:" << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Some exception" << endl;
		throw;
	}
}



namespace Exceptions
{
	class A
	{
		string m_S;
	public:
		A(const string& s)
			:m_S(s)
		{
			writeln("A::A", m_S);
		}
		~A()
		{
			writeln("A::~A", m_S);
		}
	};
	void g()
	{
		A a("g");
		A* pA = new A("pA");
		throw 100;
		delete pA;
	}
	void f()
	{
		A a("f");
		g();
	}

}

void start9()
{
	return;
	writeln("------------------ 9");
	try
	{
		Exceptions::A a("start9");
		Exceptions::f();
	}
	catch (...)
	{
		cout << "Catched" << endl;
	}
}

#pragma endregion

CWinApp theApp;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			start1();
			start2();
			start3();
			start4();
			start5();
			start6();
			start7();
			start8();
			start9();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
