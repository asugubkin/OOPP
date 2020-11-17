
// MFCApplication.h : main header file for the MFCApplication application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplicationApp:
// See MFCApplication.cpp for the implementation of this class
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationApp theApp;
