
// LMSServer.h : LMSServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLMSServerApp:
// �йش����ʵ�֣������ LMSServer.cpp
//

class CLMSServerApp : public CWinApp
{
public:
	CLMSServerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLMSServerApp theApp;
