
// CorpImServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCorpImServerApp:
// �йش����ʵ�֣������ CorpImServer.cpp
//

class CCorpImServerApp : public CWinApp
{
public:
	CCorpImServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCorpImServerApp theApp;
#include "DataModule.h"
extern CDataModule g_dmCorpIm;//���ݴ���ģ��