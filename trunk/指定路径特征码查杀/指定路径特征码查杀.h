
// ָ��·���������ɱ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cָ��·���������ɱApp:
// �йش����ʵ�֣������ ָ��·���������ɱ.cpp
//

class Cָ��·���������ɱApp : public CWinApp
{
public:
	Cָ��·���������ɱApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cָ��·���������ɱApp theApp;