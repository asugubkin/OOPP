#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Control
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include <array>

#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

#include <stack>
#include <queue>

#include <unordered_map>
#include <unordered_set>

#include <functional>
#include <algorithm>

#include <tuple>


using namespace std;

// https://boost.org/

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

#pragma endregion
