// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin �Ի���

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
	ON_WM_SHOWWINDOW()  //��ʼ��ʾʱ������û���������
END_MESSAGE_MAP()


// DlgLogin ��Ϣ�������
void DlgLogin::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialog::OnShowWindow(bShow,nStatus);

	//��ʼ����Ϊ��
	m_UserId=L"";
	m_Password=L"";

	UpdateData(FALSE);
}