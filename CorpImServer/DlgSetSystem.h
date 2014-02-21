#pragma once


// CDlgSetSystem 对话框

class CDlgSetSystem : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetSystem)

public:
	CDlgSetSystem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetSystem();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	UINT m_ServicePort;
	CString m_ServiceName;
	DWORD m_ServiceIp;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
