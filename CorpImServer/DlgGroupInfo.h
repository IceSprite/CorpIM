#pragma once


// CDlgGroupInfo 对话框

class CDlgGroupInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGroupInfo)

public:
	CDlgGroupInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGroupInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_GROUPINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_GroupId;
	CString m_GroupName;
	CString m_GroupMemo;
};
