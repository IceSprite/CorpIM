
// CorpImServerDlg.h : 头文件
//

#pragma once
#include "DataTransfer.h"


// CCorpImServerDlg 对话框
class CCorpImServerDlg : public CDialogEx
{
// 构造
public:
	CCorpImServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIALOG_CORPIMSERVER };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSetSystem();
	afx_msg void OnbnClickedButtonServer();

public:
	BOOL m_bServiceOn;//服务是否已经启动
	HANDLE m_hThreadServiceDispatchData;//数据分发服务
	HANDLE m_hTreadServiceSendData;//数据发送服务
	
public:
	BOOL StartService(void);//启动服务
	BOOL StopService(void);//关闭服务

private:
	CDataTransfer m_ListendSocket;//监听服务的Socket
	BOOL ServiceListen(void);//启动监听服务
};
