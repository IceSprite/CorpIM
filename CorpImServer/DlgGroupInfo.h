#pragma once


// CDlgGroupInfo �Ի���

class CDlgGroupInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGroupInfo)

public:
	CDlgGroupInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgGroupInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_GROUPINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_GroupId;
	CString m_GroupName;
	CString m_GroupMemo;
};
