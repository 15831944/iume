
// iUMeVideo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiUMeVideoApp:
// �йش����ʵ�֣������ iUMeVideo.cpp
//

class CiUMeVideoApp : public CWinApp
{
public:
	CiUMeVideoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CiUMeVideoApp theApp;