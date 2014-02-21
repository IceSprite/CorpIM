// CdlgManageUsers.cpp : 实现文件
//
#pragma  once
#include "stdafx.h"
#include "CorpImServer.h"
#include "CdlgManageUsers.h"
#include "afxdialogex.h"
#include "common.h"

// CdlgManageUsers 对话框

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


// CdlgManageUsers 消息处理程序


void CdlgManageUsers::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CdlgManageUsers::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);
	//获取组织结构信息
	g_dmCorpIm.GetGroups(m_Groups);

	//添加用户信息显示列表内容
	m_Users.InsertColumn(COL_USER_ID,L"用户编号",0,COLUMN_WIDTH);
	m_Users.InsertColumn(COL_USER_NAME,L"用户名称",0,COLUMN_WIDTH);
}

void CdlgManageUsers::OnTvnSelchangedTreeGroups(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//切换用户列表
	if (pNMTreeView->itemNew.hItem!=pNMTreeView->itemOld.hItem)
	{
		g_dmCorpIm.GetUsers(pNMTreeView->itemNew.iImage,m_Users);
	}
	*pResult=0;
}

