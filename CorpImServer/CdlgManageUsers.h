#pragma once
#include "afxcmn.h"


// CdlgManageUsers 对话框

class CdlgManageUsers : public CDialogEx
{
	DECLARE_DYNAMIC(CdlgManageUsers)

public:
	CdlgManageUsers(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CdlgManageUsers();

// 对话框数据
	enum { IDD = IDD_DIALOG_MANAGE_USERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_Groups;
	CListCtrl m_Users;

public:
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
	afx_msg void OnTvnSelchangedTreeGroups(NMHDR *pNMHDR,LRESULT *pResult);
};
