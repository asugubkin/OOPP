// MFCLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


__declspec(dllexport) int f1(int x)
{
	return x * x;
}