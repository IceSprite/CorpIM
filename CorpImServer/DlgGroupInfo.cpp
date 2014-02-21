// DlgGroupInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgGroupInfo.h"
#include "afxdialogex.h"


// CDlgGroupInfo 对话框

IMPLEMENT_DYNAMIC(CDlgGroupInfo, CDialogEx)

CDlgGroupInfo::CDlgGroupInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgGroupInfo::IDD, pParent)
	, m_GroupId(0)
	, m_GroupName(_T(""))
	, m_GroupMemo(_T(""))
{

}

CDlgGroupInfo::~CDlgGroupInfo()
{
}

void CDlgGroupInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUP_ID, m_GroupId);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_GroupName);
	DDV_MaxChars(pDX, m_GroupName, 50);
	DDX_Text(pDX, IDC_EDIT_GROUP_MEMO, m_GroupMemo);
}


BEGIN_MESSAGE_MAP(CDlgGroupInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgGroupInfo 消息处理程序
