// DlgSetSystem.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgSetSystem.h"
#include "afxdialogex.h"


// CDlgSetSystem 对话框

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


// CDlgSetSystem 消息处理程序

void CDlgSetSystem::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//获取数据库中信息
	g_dmCorpIm.GetSystemInfo(m_ServiceIp,m_ServicePort,m_ServiceName);
	UpdateData(FALSE);
}