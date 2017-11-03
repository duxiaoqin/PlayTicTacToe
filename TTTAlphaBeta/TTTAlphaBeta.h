/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// TTTAlphaBeta.h : main header file for the TTTAlphaBeta application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTTTAlphaBetaApp:
// See TTTAlphaBeta.cpp for the implementation of this class
//

class CTTTAlphaBetaApp : public CWinApp
{
public:
	CTTTAlphaBetaApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTTTAlphaBetaApp theApp;
