#pragma once


// CDlgMessageInfo �Ի���

class CDlgMessageInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMessageInfo)

public:
	CDlgMessageInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMessageInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_MessageId;
	CString m_MessageWriter;
	CString m_MessageTitle;
	CString m_MessageContent;
	BOOL m_IsPublished;
	CString m_MessageTime;
};
