
// FinaceManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFinaceManagerApp:
// �йش����ʵ�֣������ FinaceManager.cpp
//

class CFinaceManagerApp : public CWinApp
{
public:
	CFinaceManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFinaceManagerApp theApp;