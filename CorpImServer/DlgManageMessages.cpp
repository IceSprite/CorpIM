// DlgManageMessages.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgManageMessages.h"
#include "afxdialogex.h"




//公告管理
enum{COL_MESSAGE_ID,COL_MESSAGE_IS_PUBLISHED,COL_MESSAGE_TITLE,COL_MESSAGE_TIME};
const int COLUMN_WIDTH=100;//列宽

// CDlgManageMessages 对话框

IMPLEMENT_DYNAMIC(CDlgManageMessages, CDialogEx)

CDlgManageMessages::CDlgManageMessages(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgManageMessages::IDD, pParent)
{

}

CDlgManageMessages::~CDlgManageMessages()
{
}

void CDlgManageMessages::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_Messages);
}


BEGIN_MESSAGE_MAP(CDlgManageMessages, CDialogEx)
END_MESSAGE_MAP()


// CDlgManageMessages 消息处理程序

void CDlgManageMessages::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//设定标题
	m_Messages.InsertColumn(COL_MESSAGE_ID,L"公告编号",0,COLUMN_WIDTH);
	m_Messages.InsertColumn(COL_MESSAGE_IS_PUBLISHED,L"是否发布",0,COLUMN_WIDTH/2);
	m_Messages.InsertColumn(COL_MESSAGE_TITLE,L"公告标题",0,COLUMN_WIDTH);
	m_Messages.InsertColumn(COL_MESSAGE_TIME,L"公告时间",0,COLUMN_WIDTH);
}
