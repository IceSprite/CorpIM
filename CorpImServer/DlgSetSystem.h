#pragma once


// CDlgSetSystem �Ի���

class CDlgSetSystem : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetSystem)

public:
	CDlgSetSystem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetSystem();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	UINT m_ServicePort;
	CString m_ServiceName;
	DWORD m_ServiceIp;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
