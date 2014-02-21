#pragma once


// DlgLogin 对话框

class DlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLogin)

public:
	DlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_UserId;
	CString m_Password;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);//初始显示时候清除用户名及密码

};
