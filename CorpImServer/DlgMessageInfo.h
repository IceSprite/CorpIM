#pragma once


// CDlgMessageInfo 对话框

class CDlgMessageInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMessageInfo)

public:
	CDlgMessageInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMessageInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_MessageId;
	CString m_MessageWriter;
	CString m_MessageTitle;
	CString m_MessageContent;
	BOOL m_IsPublished;
	CString m_MessageTime;
};
