// DlgSetSystem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgSetSystem.h"
#include "afxdialogex.h"


// CDlgSetSystem �Ի���

IMPLEMENT_DYNAMIC(CDlgSetSystem, CDialogEx)

CDlgSetSystem::CDlgSetSystem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetSystem::IDD, pParent)
	, m_ServicePort(0)
	, m_ServiceName(_T(""))
	, m_ServiceIp(0)
{

}

CDlgSetSystem::~CDlgSetSystem()
{
}

void CDlgSetSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_ServicePort);
	DDX_Text(pDX, IDC_EDIT_SERVER_NAME, m_ServiceName);
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_ServiceIp);
}


BEGIN_MESSAGE_MAP(CDlgSetSystem, CDialogEx)
END_MESSAGE_MAP()


// CDlgSetSystem ��Ϣ�������

void CDlgSetSystem::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//��ȡ���ݿ�����Ϣ
	g_dmCorpIm.GetSystemInfo(m_ServiceIp,m_ServicePort,m_ServiceName);
	UpdateData(FALSE);
}