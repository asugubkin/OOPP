// MFCLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MFCLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMFCLibraryApp

BEGIN_MESSAGE_MAP(CMFCLibraryApp, CWinApp)
END_MESSAGE_MAP()


// CMFCLibraryApp construction

CMFCLibraryApp::CMFCLibraryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCLibraryApp object

CMFCLibraryApp theApp;


// CMFCLibraryApp initialization

BOOL CMFCLibraryApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

struct CppStruct
{
	int i;
	double d;
	char s[100];
};

extern "C"
{
	__declspec(dllexport) int __stdcall GetSize(char* FileName)
	{
		return (int)filesystem::file_size(FileName)+1;
	}

	__declspec(dllexport) void GetFile(char* FileName, char* FileData)
	{
		ifstream in(FileName, ios::binary);
		string s(istreambuf_iterator<char>{in}, {});
		strcpy(FileData, s.c_str());
	}

	__declspec(dllexport) void GetStruct(CppStruct& s)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString str;
		str.Format("C++ GetStruct: %d %.2f %s", s.i, s.d, s.s);
		AfxMessageBox(str);
		s.i++;
		s.d+=100;
		strcpy(s.s, "String from C++");
	}
}


