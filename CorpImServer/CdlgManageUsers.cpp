// CdlgManageUsers.cpp : ʵ���ļ�
//
#pragma  once
#include "stdafx.h"
#include "CorpImServer.h"
#include "CdlgManageUsers.h"
#include "afxdialogex.h"
#include "common.h"

// CdlgManageUsers �Ի���

IMPLEMENT_DYNAMIC(CdlgManageUsers, CDialogEx)

CdlgManageUsers::CdlgManageUsers(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdlgManageUsers::IDD, pParent)
{

}

CdlgManageUsers::~CdlgManageUsers()
{
}

void CdlgManageUsers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_GROUPS, m_Groups);
	DDX_Control(pDX, IDC_LIST_USERS, m_Users);
}


BEGIN_MESSAGE_MAP(CdlgManageUsers, CDialogEx)
	
END_MESSAGE_MAP()


// CdlgManageUsers ��Ϣ�������


void CdlgManageUsers::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CdlgManageUsers::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//��ȡ��֯�ṹ��Ϣ
	g_dmCorpIm.GetGroups(m_Groups);

	//����û���Ϣ��ʾ�б�����
	m_Users.InsertColumn(COL_USER_ID,L"�û����",0,COLUMN_WIDTH);
	m_Users.InsertColumn(COL_USER_NAME,L"�û�����",0,COLUMN_WIDTH);
}

void CdlgManageUsers::OnTvnSelchangedTreeGroups(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//�л��û��б�
	if (pNMTreeView->itemNew.hItem!=pNMTreeView->itemOld.hItem)
	{
		g_dmCorpIm.GetUsers(pNMTreeView->itemNew.iImage,m_Users);
	}
	*pResult=0;
}

