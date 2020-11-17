// DllTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "DllTest.h"
#include "../MFCLibrary/DllClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// #pragma comment (lib, "MFCLibrary.lib")

// #pragma comment (lib, "delayimp.lib")
// #pragma comment (linker, "/DelayLoad:MFCLibrary.dll")


__declspec(dllimport) int f1(int x);

void start()
{
	cout << "start" << endl;
	cout << f1(10) << endl;
	DllClass dc;

	// return;

	HMODULE hLib = LoadLibrary("MyDll.dll");
	if(!hLib)
	{
		cout << "Error loading library" << endl;
		return;
	}

	// typedef int (*PF)(int);
	// using PF = int(*)(int);
	// PF f2 = (PF)GetProcAddress(hLib, "f2");

	auto f2 = (int(*)(int))GetProcAddress(hLib, "f2");
	if(!f2)
	{
		cout << "Error getting address" << endl;
		return;
	}
	cout << f2(20) << endl;

	FreeLibrary(hLib);
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
