#pragma  once
// CorpImServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "CorpImServerDlg.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDataModule g_dmCorpIm;//���ݴ���ģ��
CString g_CurrentUserID; //��ǰ�û����


// CCorpImServerApp

BEGIN_MESSAGE_MAP(CCorpImServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCorpImServerApp ����

CCorpImServerApp::CCorpImServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCorpImServerApp ����

CCorpImServerApp theApp;


// CCorpImServerApp ��ʼ��

BOOL CCorpImServerApp::InitInstance()
{
	//�������ݿ�
	if(!g_dmCorpIm.ConnectDB())
	{
		AfxMessageBox(L"���ݿ�����ʧ�ܣ�������ODBC��");
		return FALSE;
	}

	//�򿪵�¼����е�¼��֤
	DlgLogin dlgLogin;
	if(IDOK == dlgLogin.DoModal())
	{
		//��¼��֤
		if(!g_dmCorpIm.CheckLoginUser(dlgLogin.m_UserId,dlgLogin.m_Password))
		{
			return FALSE;
		}
		//��¼��ǰ�û����
		g_CurrentUserID = dlgLogin.m_UserId;
	}
	else
	{
		return FALSE;
	}

	CCorpImServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();


	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

extern CString g_CurrentUserID;

