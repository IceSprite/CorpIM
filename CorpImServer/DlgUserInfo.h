#pragma once


// CDlgUserInfo �Ի���

class CDlgUserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserInfo)

public:
	CDlgUserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserId;
	CString m_UserName;
	CString m_Job;
	CString m_JobPhone;
	CString m_HandPhone;
	CString m_Fax;
	CString m_Email;
	CString m_JobAddress;
	CString m_PostCode;
	CString m_Other;
	CString m_Sex;
};
