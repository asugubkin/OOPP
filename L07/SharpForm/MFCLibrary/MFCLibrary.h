// MFCLibrary.h : main header file for the MFCLibrary DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCLibraryApp
// See MFCLibrary.cpp for the implementation of this class
//

class CMFCLibraryApp : public CWinApp
{
public:
	CMFCLibraryApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
