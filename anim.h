
// anim.h : main header file for the anim application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CanimApp:
// See anim.cpp for the implementation of this class
//

class CanimApp : public CWinApp
{
public:
	CanimApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CanimApp theApp;
