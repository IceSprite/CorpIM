#pragma once
#include "afxcmn.h"


// CDlgManageMessages �Ի���

class CDlgManageMessages : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgManageMessages)

public:
	CDlgManageMessages(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgManageMessages();

// �Ի�������
	enum { IDD = IDD_DIALOG_MANAGE_MESSAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Messages;
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
};
