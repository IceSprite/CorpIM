// DlgMessageInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgMessageInfo.h"
#include "afxdialogex.h"


// CDlgMessageInfo 对话框

IMPLEMENT_DYNAMIC(CDlgMessageInfo, CDialogEx)

CDlgMessageInfo::CDlgMessageInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMessageInfo::IDD, pParent)
	, m_MessageId(0)
	, m_MessageWriter(_T(""))
	, m_MessageTitle(_T(""))
	, m_MessageContent(_T(""))
	, m_IsPublished(FALSE)
	, m_MessageTime(_T(""))
{

}

CDlgMessageInfo::~CDlgMessageInfo()
{
}

void CDlgMessageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_ID, m_MessageId);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_WRITER, m_MessageWriter);
	DDV_MaxChars(pDX, m_MessageWriter, 50);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_TITLE, m_MessageTitle);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_CONTENT, m_MessageContent);
	DDV_MaxChars(pDX, m_MessageTitle, 100);
	DDX_Check(pDX, IDC_CHECK_IS_PUBLISHED, m_IsPublished);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_MESSAGE_TIME, m_MessageTime);
}


BEGIN_MESSAGE_MAP(CDlgMessageInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgMessageInfo 消息处理程序
