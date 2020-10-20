// L04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L04.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region Containers
void start1()
{
	return;
	array<int,10> a = { 1, 2, 3, 4 };

	int ai[] {1, 2, 3, 4, 5};
	int* p = new int[] {1, 2, 3, 4, 5};
	delete[]p;

	vector<int> v = {1, 2, 3, 4, 5};
	map<string, int> m { {"one", 1}, {"two", 2}, {"three", 3} };
	set<int> s{ 5, 4, 3, 2, 1,  2, 3, 4};

	writeln(a.front(), a.back(), v.front(), v.back(), s.size());
	
	writeln("\nenumeration 1");
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		writeln(v[i], v.at(i));
	}
	writeln("\nenumeration 2");
	for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		writeln(*i);
	}
	writeln("\nenumeration 3");
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		writeln(i->first, i->second);
	}
	if (!m["four"])
	{
		writeln("not found four");
	}
	writeln("\nenumeration 4");
	for (auto& i: m)
	{
		writeln(i.first, i.second);
	}
	if (m.find("five") == m.end())
	{
		writeln("not found five");
	}
	writeln("\nenumeration 5");
	for (auto&[k, v]: m)
	{
		writeln(k, v);
		v++;
	}
	if (find(v.begin(), v.end(), 7) == v.end())
	{
		writeln("not found 7");
	}

	for (auto i = v.begin(); i != v.end();)
	{
		if (*i % 2)
		{
			i = v.erase(i);
		}
		else
		{
			++i;
		}
	}

	for (auto i = m.begin(); i != m.end();)
	{
		if (i->second % 2)
		{
			m.erase(i++);
		}
		else
		{
			++i;
		}
	}

	writeln("\nenumeration 6");
	for (auto& i : v)
	{
		writeln(i);
	}
	writeln("\nenumeration 7");
	for (auto& [k, v] : m)
	{
		writeln(k, v);
	}
}

#pragma endregion

#pragma region Algorithms

void PrintInt(int& i)
{
	writeln(i);
	++i;
}

bool SortDec(int& i1, int& i2)
{
	return (i1 > i2);
}

class Printer
{
public:
	ostream& out;
	Printer(ostream& o) :out(o) {}
	void operator()(int& i) { out << i << endl; }
};

void PrinterInt(ofstream& out, int i)
{
	out << i << endl;
}

void start2()
{
	return;
	writeln("------------------ 2");
	vector<int> v = { 1, 2, 3, 4, 5 };
	writeln("\nenumeration 1");
	for_each(v.begin(), v.end(), PrintInt);
	writeln("\nenumeration 2");
	for_each(v.begin(), v.end(), PrintInt);
	writeln("sort 1");
	sort(v.begin(), v.end(), SortDec);
	for_each(v.begin(), v.end(), PrintInt);
	writeln("sort 2");
	sort(v.begin(), v.end(), less<int>());
	for_each(v.begin(), v.end(), PrintInt);

	{
		ofstream out("out.1.txt");
		for_each(v.begin(), v.end(), Printer(out));
	}

	{
		ofstream out("out.2.txt");
		for_each(v.begin(), v.end(), std::bind(PrinterInt, ref(out), placeholders::_1));
	}
	{
		ofstream out("out.3.txt");
		for_each(v.begin(), v.end(), [&out](int i) {out << i << endl; });
		
		for_each(v.begin(), v.end(), [&out](int i) 
		{
				out << i << endl;
		});
	}

	auto s1 = [](int i1, int i2)->bool {return i1 > i2; };
	auto s2 = [&](int i1, int i2) {return i1 > i2; };
	auto s3 = [=](int i1, int i2)->bool {return i1 > i2; };

	auto r = [](int i) {return i % 2; };

	sort(v.begin(), v.end(),  s1);
	auto end = remove_if(v.begin(), v.end(), r);
	v.erase(end, v.end());
	writeln("sort 3");
	for_each(v.begin(), v.end(), PrintInt);
}

#pragma endregion

#pragma region IO iterators

void start3()
{
	return;
	writeln("------------------ 3");
	{
		ifstream in("out.1.txt");
		istreambuf_iterator<char> i(in);
		istreambuf_iterator<char> eof;
		for (; i != eof; ++i)
		{
			cout << *i;
		}
	}
	
	{
		ifstream in("out.2.txt");
		string s1(istreambuf_iterator<char>(in), istreambuf_iterator<char>());
		string s2(istreambuf_iterator<char>(in), (istreambuf_iterator<char>()));
		cout << "out.2.txt:\n" << s2 << endl;
	}

	{
		ifstream in("out.3.txt");
		string s(istreambuf_iterator<char>{in}, {});
		cout << "out.3.txt:\n" << s << endl;
	}

	{
		stringstream sout;
		vector<int> v = { 1, 2, 3, 4, 5 };
		for_each(v.begin(), v.end(), Printer(sout));
		cout << sout.str() << endl;
	}

}
	
#pragma endregion

#pragma region Custom iterators

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

	struct iterator
	{
		typedef T& reference;
		typedef T* pointer;
		typedef std::input_iterator_tag iterator_category;
		typedef T value_type;
		typedef int difference_type;

		Array<T>* m_pArray;
		int m_I;

		iterator& operator++()
		{
			m_I++;
			return *this;
		}
		iterator operator++(int)
		{
			iterator it(*this);
			m_I++;
			return it;
		}
		T& operator *()
		{
			return m_pArray->get(m_I);
		}
		bool operator==(const typename Array<T>::iterator& i)
		{
			return m_I == i.m_I;
		}
		bool operator!=(const typename Array<T>::iterator& i)
		{
			return m_I != i.m_I;
		}
	};

	iterator begin()
	{
		return iterator{ this, 0 };
	}
	iterator end()
	{
		return iterator{ this, m_N };
	}
};

void start4()
{
	return;
	writeln("------------------ 4");
	vector<int>::iterator i;

	Array<int> a(10);
	a = 12345;
	for (auto i = a.begin(); i != a.end(); i++)
	{
		writeln(*i);
		(*i)++;
	}
	for (auto i : a)
	{
		writeln(i);
	}
}

#pragma endregion

#pragma region Tuples

tuple<string, int> f()
{
	return std::make_tuple("123", 12345);
}

auto fauto()
{
	return std::make_tuple("123", 12345);
}

void start5()
{
	return;
	writeln("------------------ 5");

	int i;
	string s;
	auto t = f();
	std::tie(s, i) = f();

	auto [ss, ii] = f();
	auto [sss, iii] = fauto();
	writeln(get<0>(t), get<1>(t), s, i, ss, ii, sss, iii);
}

#pragma endregion

#pragma region Smart pointers

class A: public enable_shared_from_this<A>
{
	string s;
public:
	A(const string& _s = ""):s(_s) { writeln("A::A", s); }
	~A() { writeln("A::~A", s); }
	void f() { writeln("A::f", s); }
	shared_ptr<A> getptr() { return shared_from_this(); }
};

void f(shared_ptr<A> a1, shared_ptr<A> a2)
{
	writeln("a1 use count", a1.use_count());
}

void g(unique_ptr<A> a)
{
	a->f();
}

void start6()
{
	// return;
	writeln("------------------ 6");

	A* pA = new A;
	shared_ptr<A> spA(pA);

	f(shared_ptr<A>(new A), shared_ptr<A>(new A));
	f(make_shared<A>(), make_shared<A>());

	auto sp = make_shared<A>();
	writeln("use count", sp.use_count());
	auto sp2 = sp;
	writeln("use count", sp.use_count());

	unique_ptr<A> up = make_unique<A>("unique");
	//auto up2 = up;
	g(move(up));
	

	weak_ptr<A> wp;
	{
		auto swp = make_shared<A>("weak");
		sp = make_shared<A>("shared");
		wp = swp;
		if (!wp.expired())
		{
			wp.lock()->f();
		}
		writeln("swp done");
	}
	sp.get()->f();
	sp->f();
	if(wp.expired())
		writeln("wp expired", wp.use_count());
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
