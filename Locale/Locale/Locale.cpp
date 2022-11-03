// Locale.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Locale.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

string Console1()
{
	setlocale(LC_ALL, ".1251");
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	cout << GetConsoleCP() << endl;
//	cout << GetConsoleOutputCP() << endl;

	cout << "Введите строку" << endl;

	string s;
	cin >> s;
	cout << s << endl;
	return s;
}

string Console2()
{
	setlocale(LC_ALL, ".1251");
	cout << "Введите строку" << endl;
	setlocale(LC_ALL, ".866");
	SetConsoleCP(1251);
	//	CharToOemBuff
	//	OemToCharBuff

	//	CString s;
	//	s.AnsiToOem();
	//	s.OemToAnsi();


	string s;
	cin >> s;
 	cout << s << endl;
	return s;
}

void WriteString1(const CString& s)
{
	CString tmp = s;
	tmp.CharToOem();
	cout << tmp << endl;
}

void WriteString2(const char* s)
{
	setlocale(LC_ALL, ".1251");
	cout << s << endl;
	setlocale(LC_ALL, ".866");
}

void start()
{
	cout << "Строка 0" << endl;
	WriteString1("Строка 1");
	WriteString2("Строка 2");
	WriteString1(Console1().c_str());
	WriteString2(Console2().c_str());
}


CWinApp theApp;

using namespace std;

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
			start();
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
