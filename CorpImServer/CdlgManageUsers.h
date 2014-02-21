#pragma once
#include "afxcmn.h"


// CdlgManageUsers �Ի���

class CdlgManageUsers : public CDialogEx
{
	DECLARE_DYNAMIC(CdlgManageUsers)

public:
	CdlgManageUsers(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CdlgManageUsers();

// �Ի�������
	enum { IDD = IDD_DIALOG_MANAGE_USERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_Groups;
	CListCtrl m_Users;

public:
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
	afx_msg void OnTvnSelchangedTreeGroups(NMHDR *pNMHDR,LRESULT *pResult);
};
