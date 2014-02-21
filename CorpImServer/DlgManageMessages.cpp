// DlgManageMessages.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DlgManageMessages.h"
#include "afxdialogex.h"




//�������
enum{COL_MESSAGE_ID,COL_MESSAGE_IS_PUBLISHED,COL_MESSAGE_TITLE,COL_MESSAGE_TIME};
const int COLUMN_WIDTH=100;//�п�

// CDlgManageMessages �Ի���

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


// CDlgManageMessages ��Ϣ�������

void CDlgManageMessages::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//�趨����
	m_Messages.InsertColumn(COL_MESSAGE_ID,L"������",0,COLUMN_WIDTH);
	m_Messages.InsertColumn(COL_MESSAGE_IS_PUBLISHED,L"�Ƿ񷢲�",0,COLUMN_WIDTH/2);
	m_Messages.InsertColumn(COL_MESSAGE_TITLE,L"�������",0,COLUMN_WIDTH);
	m_Messages.InsertColumn(COL_MESSAGE_TIME,L"����ʱ��",0,COLUMN_WIDTH);
}
