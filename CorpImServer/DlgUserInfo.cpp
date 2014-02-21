// DlgUserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgUserInfo.h"
#include "afxdialogex.h"


// CDlgUserInfo 对话框

IMPLEMENT_DYNAMIC(CDlgUserInfo, CDialogEx)

CDlgUserInfo::CDlgUserInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUserInfo::IDD, pParent)
	, m_UserId(_T(""))
	, m_UserName(_T(""))
	, m_Job(_T(""))
	, m_JobPhone(_T(""))
	, m_HandPhone(_T(""))
	, m_Fax(_T(""))
	, m_Email(_T(""))
	, m_JobAddress(_T(""))
	, m_PostCode(_T(""))
	, m_Other(_T(""))
	, m_Sex(_T(""))
{

}

CDlgUserInfo::~CDlgUserInfo()
{
}

void CDlgUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_UserId);
	DDV_MaxChars(pDX, m_UserId, 20);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_UserName);
	DDV_MaxChars(pDX, m_UserName, 50);
	DDX_Text(pDX, IDC_EDIT_JOB, m_Job);
	DDV_MaxChars(pDX, m_Job, 50);
	DDX_Text(pDX, IDC_EDIT_JOB_PHONE, m_JobPhone);
	DDV_MaxChars(pDX, m_JobPhone, 50);
	DDX_Text(pDX, IDC_EDIT_HAND_PHONE, m_HandPhone);
	DDV_MaxChars(pDX, m_HandPhone, 50);
	DDX_Text(pDX, IDC_EDIT_FAX, m_Fax);
	DDV_MaxChars(pDX, m_Fax, 50);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_Email);
	DDV_MaxChars(pDX, m_Email, 50);
	DDX_Text(pDX, IDC_EDIT_JOB_ADDRESS, m_JobAddress);
	DDV_MaxChars(pDX, m_JobAddress, 100);
	DDX_Text(pDX, IDC_EDIT_POSTCODE, m_PostCode);
	DDV_MaxChars(pDX, m_PostCode, 10);
	DDX_Text(pDX, IDC_EDIT1_OHTER, m_Other);
	DDX_CBString(pDX, IDC_COMBO_SEX, m_Sex);
	DDV_MaxChars(pDX, m_Sex, 1);
}


BEGIN_MESSAGE_MAP(CDlgUserInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgUserInfo 消息处理程序
