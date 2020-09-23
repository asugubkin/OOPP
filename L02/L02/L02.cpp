// L02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L02.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region Simple Inheritance


class B
{
	int m_I = 0;

protected:
	int m_J = 0;

public:

	B()
	{
		cout << "B::B()" << endl;
	}

	B(int i)
		:m_I(i)
	{
		cout << "B::B(" << i << ")" << endl;
	}

	virtual ~B()
	{
		cout << "B::~B()" << endl;
	}

	void f()
	{
		cout << "B::f " << m_I << endl;
	}

	virtual void vf()
	{
		cout << "B::vf " << m_I << endl;
	}
};

class D: public B
{
	int m_K = 0;
public:
	D()
	{
		cout << "D::D()" << endl;
	}
	D(int k)
		:B(k*k), m_K(k)
	{
		cout << "D::D(" << k << ")" << endl;
	}
	~D()
	{
		cout << "D::~D()" << endl;
	}

	void f()
	{
		cout << "D::f " << m_K << endl;
	}

	virtual void vf()
	{
		cout << "D::vf " << m_K << endl;
	}
};

void start1()
{
	return;

	{
		D d1;
		d1.f();

		D d2(2);
		d2.f();
		d2.B::f();

	}

	{
		//return;
		cout << "=============" << endl;
		B b(1);
		D d(2);
		B* pb = &b;
		D* pd = &d;

		b = d;
		b.f();

//		d = b;
//		d.f();

//		pb = pd;
		pb->f();

		pd = (D*)pb;
		pd->f();

	}

	{

		//return;

		cout << "=============" << endl;
		B* pd = new D;
		pd->f();
		pd->vf();
		delete pd;
	}	
	
	{
		//return;
		cout << "=============" << endl;
		B b;
		D d;
		B *pb, *pbd;
		D *pd, *pdb;
			
		pb = &b;
		pd = &d;

		int i = 0;
		cin >> i;

		pbd = i ? pd : pb;
		pdb = dynamic_cast<D*>(pbd);

		pb->f();
		pb->vf();

		pd->f();
		pd->vf();

		pbd->f();
		pbd->vf();

		if (pdb)
		{
			pdb->f();
			pdb->vf();
		}
	}


}

#pragma endregion

#pragma region Abstract Classes

class Shape
{
	int m_X = 0;
	int m_Y = 0;
public:
	virtual void Draw() = 0;
	virtual void Erase() = 0;

		void Move(int X, int Y)
	{
		Erase();
		m_X = X;
		m_Y = Y;
		Draw();
	}
};

class Circle: public Shape
{
public:
	void Draw()
	{
		cout << "Circle::Draw" << endl;
	}
	void Erase()
	{
		cout << "Circle::Erase" << endl;
	}
};

class Rect : public Shape
{
public:
	void Draw()
	{
		cout << "Rect::Draw" << endl;
	}
	void Erase()
	{
		cout << "Rect::Erase" << endl;
	}
};

void start2()
{
	return;
	cout << "=============" << endl;
	vector<Shape*> s;
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2)
			s.push_back(new Circle());
		else
			s.push_back(new Rect());
	}
	for (int i = 0; i < 10; ++i)
	{
		s[i]->Move(i, i * 10);
	}
	for (int i = 0; i < 10; ++i)
	{
		delete s[i];
	}
}

#pragma endregion

#pragma region Multiple Inheritance

class B1
{
public:
	int m_I = 1;
	B1()
	{
		cout << "B1::B1" << endl;
	}
	~B1()
	{
		cout << "B1::~B1" << endl;
	}
	void f()
	{
		cout << "B1::f " << m_I << endl;
	}
};

class B2
{
public:
	int m_I = 2;
	B2()
	{
		cout << "B2::B2" << endl;
	}
	~B2()
	{
		cout << "B2::~B2" << endl;
	}
	void f()
	{
		cout << "B2::f " << m_I << endl;
	}
};

class DD : public B1, public B2
{
public:
	DD()
	{
		cout << "DD::DD" << endl;
	}
	~DD()
	{
		cout << "DD::~DD" << endl;
	}
	void f()
	{
		B1::f();
		B2::f();
	}
};

void start3()
{
	return;
	cout << "=============" << endl;
	DD d;
	d.f();

	d.B1::m_I = 12345;
	d.B2::m_I = 54321;
	d.f();
}

#pragma endregion

#pragma region Virtual Inheritance

class B00
{
public:
	int m_K = 1;
	B00(int K)
		:m_K(K)
	{
		cout << "B00::B00(" << K << ")" << endl;
	}
	B00()
	{
		cout << "B00::B00" << endl;
	}
	~B00()
	{
		cout << "B00::~B00" << endl;
	}
	void g()
	{
		cout << "B00::g " << m_K << endl;
	}
};

class B01: public virtual B00
{
public:
	int m_I = 1;
	B01(int I)
		:m_I(I), B00(I*I)
	{
		cout << "B01::B01(" <<  I << ")" << endl;
	}
	B01()
	{
		cout << "B01::B01" << endl;
	}
	~B01()
	{
		cout << "B01::~B01" << endl;
	}
	void f()
	{
		cout << "B01::f " << m_I << endl;
	}
};

class B02: public virtual B00
{
public:
	int m_I = 2;
	B02(int I)
		:m_I(I), B00(I* I)
	{
		cout << "B02::B02(" << I << ")" << endl;
	}
	B02()
	{
		cout << "B02::B02" << endl;
	}
	~B02()
	{
		cout << "B02::~B02" << endl;
	}
	void f()
	{
		cout << "B02::f " << m_I << endl;
	}
};

class DDD : public B01, public B02
{
public:
	DDD(int I)
		:B01(I), B02(I*2), B00(I*100)
	{
		cout << "DDD::DDD" << endl;
	}
	DDD()
	{
		cout << "DDD::DDD" << endl;
	}
	~DDD()
	{
		cout << "DDD::~DDD" << endl;
	}
	void f()
	{
		B01::f();
		B02::f();
	}
};

void start4()
{
	return;
	cout << "=============" << endl;
	DDD d;
	d.g();

	cout << "=============" << endl;
	DDD dd(1);
}

#pragma endregion

#pragma region MFC Serialization

class Base : public CObject
{
public:
	DECLARE_SERIAL(Base)

	int m_I;

	Base(int I):m_I(I){}

	Base() {}
	virtual ~Base() {}

	virtual void f()
	{
		cout << "Base::f " << m_I << endl;
	}

	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << m_I;
		}
		else
		{
			ar >> m_I;
		}
	}
};
IMPLEMENT_SERIAL(Base, CObject, 0)

class Derived : public Base
{
public:
	DECLARE_SERIAL(Derived)

	CString m_S;

	Derived(int I)
		:Base(I)
	{
		m_S.Format("String %d", I*I);
	}

	Derived() {}
	~Derived() {}

	virtual void f()
	{
		cout << "Derived::f " << m_S << " " << m_I << endl;
	}

	virtual void Serialize(CArchive& ar)
	{
		Base::Serialize(ar);
		if (ar.IsStoring())
		{
			ar << m_S;
		}
		else
		{
			{
				if (ar.GetObjectSchema() > 0)
				{

				}
			}
			ar >> m_S;
		}
	}
};
IMPLEMENT_SERIAL(Derived, Base, VERSIONABLE_SCHEMA | 0)

void start5()
{
	return;
	cout << "=============" << endl;
	vector<Base*> v;
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2)
			v.push_back(new Base(i));
		else
			v.push_back(new Derived(i));
	}
	for (auto o : v)
	{
		o->f();
	}
	// return;
	cout << "=============" << endl;

	{
		CFile f("f.dat", CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&f, CArchive::store);
		ar << v.size();
		for (auto o : v)
		{
			ar << o;
			delete o;
		}
		v.clear();
	}

	{
		CFile f("f.dat", CFile::modeRead);
		CArchive ar(&f, CArchive::load);
		int n;
		ar >> n;
		for (int i = 0; i<n; ++i)
		{
			Base* o;
			ar >> o;
			v.push_back(o);
		}


		for (auto o : v)
		{
			o->f();
			delete o;
		}
		v.clear();
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
