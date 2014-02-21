#pragma once
#include "afxcmn.h"


// CDlgManageMessages 对话框

class CDlgManageMessages : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgManageMessages)

public:
	CDlgManageMessages(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgManageMessages();

// 对话框数据
	enum { IDD = IDD_DIALOG_MANAGE_MESSAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Messages;
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
};
