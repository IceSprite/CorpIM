#pragma once


// DlgLogin �Ի���

class DlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLogin)

public:
	DlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgLogin();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_UserId;
	CString m_Password;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);//��ʼ��ʾʱ������û���������

};
