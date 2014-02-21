// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin 对话框

IMPLEMENT_DYNAMIC(DlgLogin, CDialogEx)

DlgLogin::DlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgLogin::IDD, pParent)
	, m_UserId(_T(""))
	, m_Password(_T(""))
{

}

DlgLogin::~DlgLogin()
{
}

void DlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERID, m_UserId);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(DlgLogin, CDialogEx)
	ON_WM_SHOWWINDOW()  //初始显示时候清除用户名及密码
END_MESSAGE_MAP()


// DlgLogin 消息处理程序
void DlgLogin::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialog::OnShowWindow(bShow,nStatus);

	//初始化置为空
	m_UserId=L"";
	m_Password=L"";

	UpdateData(FALSE);
}