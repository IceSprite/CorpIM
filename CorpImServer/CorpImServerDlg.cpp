
// CorpImServerDlg.cpp : 实现文件
//
#pragma  once
#include "stdafx.h"
#include "CorpImServer.h"
#include "CorpImServerDlg.h"
#include "afxdialogex.h"
#include "DlgSetSystem.h"
#include "DataTransfer.h"
#include "Analyser.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//数据分发事件
CEvent g_eventDispatch;
//数据发送线程
CEvent g_eventSend;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCorpImServerDlg 对话框




CCorpImServerDlg::CCorpImServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCorpImServerDlg::IDD, pParent)
	,m_bServiceOn(FALSE)
	,m_hThreadServiceDispatchData(NULL)
	,m_hTreadServiceSendData(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCorpImServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCorpImServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCorpImServerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SET_SYSTEM,&CCorpImServerDlg::OnBnClickedButtonSetSystem)
END_MESSAGE_MAP()


// CCorpImServerDlg 消息处理程序

BOOL CCorpImServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCorpImServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCorpImServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCorpImServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCorpImServerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CCorpImServerDlg::OnBnClickedButtonSetSystem()
{
	//系统设定
	 CDlgSetSystem dlg;
	if(IDOK==dlg.DoModal())
	{
		//保存系统设定
	}
}

//服务开关状态显示
void CCorpImServerDlg::OnbnClickedButtonServer()
{
	//启动，关闭服务
	if (!m_bServiceOn)
	{
		//启动服务
		if (StartService())
		{
			m_bServiceOn=TRUE;
			SetDlgItemText(IDC_STATIC_SERVICE_STATUS,L"服务已启动");
			SetDlgItemText(IDC_BUTTON_SERVER,L"关闭服务");
		}
		else
		{
			//关闭服务
			if (StopService())
			{
				m_bServiceOn=FALSE;
				SetDlgItemText(IDC_STATIC_SERVICE_STATUS,L"服务未启动");
				SetDlgItemText(IDC_BUTTON_SERVER,L"启动服务");
			}
		}
	}
}

//启动服务端的监听处理
BOOL CCorpImServerDlg::ServiceListen(void)
{
	BOOL ret=TRUE;
	//获取监听参数
	in_addr ServiceIp;
	UINT ServicePort;
	CString ServiceName;
	g_dmCorpIm.GetSystemInfo(ServiceIp.S_un.S_addr,ServicePort,ServiceName);
	CString strIp(inet_ntoa(ServiceIp));
	if(m_ListendSocket.Create(ServicePort,SOCK_STREAM,strIp))
	{
		//监听
		if(!m_ListendSocket.Listen())
		{
			ret=FALSE;
		}
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}


//启动服务端的数据分发处理
DWORD WINAPI ThreadProcServiceDispatchData(LPVOID lpParam)
{
	CAnalyser g_Analyser;
	//分发数据
	while(TRUE)
	{
		WaitForSingleObject(g_eventDispatch.m_hObject,INFINITE);
		if (g_RecieveDatas.size()>0)
		{
			g_Analyser.Dispatch();
		} 
		else
		{
			g_eventDispatch.ResetEvent();
		}
	}
	return 0;
}

//添加服务端的数据发送线程的处理
DWORD WINAPI ThreadProcServiceSendData(LPVOID lpParam)
{
	CAnalyser g_Analyser;
	//发送数据
	while(TRUE)
	{
		WaitForSingleObject(g_eventSend.m_hObject,INFINITE);
		if (!g_SendDatas.empty())
		{
			g_Analyser.SendDate();
		} 
		else
		{
			g_eventSend.ResetEvent();
		}
	}
}

//添加服务端启动所有服务的处理
BOOL CCorpImServerDlg::StartService(void)
{
	DWORD dwThreadId;
	//启动监听
	if (!ServiceListen())
	{
		return FALSE;
	}

	//启动数据分发线程
	m_hThreadServiceDispatchData=CreateThread(NULL,0,ThreadProcServiceDispatchData,NULL,0,&dwThreadId);
	if (NULL==m_hThreadServiceDispatchData)
	{
		return FALSE;
	}
	m_hTreadServiceSendData=CreateThread(NULL,0,ThreadProcServiceSendData,NULL,0,&dwThreadId);
	if (NULL==m_hTreadServiceSendData)
	{
		return FALSE;
	}
	return TRUE;
}

//添加服务关闭所有服务的处理
BOOL CCorpImServerDlg::StopService(void)
{
	BOOL bStoped=TRUE;
	//终止数据分发线程
	if(NULL!=m_hThreadServiceDispatchData)
	{
		bStoped=(TerminateThread(m_hThreadServiceDispatchData,0))&&(TerminateThread(m_hTreadServiceSendData,0));
		if (bStoped)
		{
			m_hThreadServiceDispatchData=NULL;
			m_hTreadServiceSendData=NULL;
		}
		else
		{
			return bStoped;
		}
	}
	return bStoped;
}
