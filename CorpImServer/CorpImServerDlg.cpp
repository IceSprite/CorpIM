
// CorpImServerDlg.cpp : ʵ���ļ�
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


//���ݷַ��¼�
CEvent g_eventDispatch;
//���ݷ����߳�
CEvent g_eventSend;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCorpImServerDlg �Ի���




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


// CCorpImServerDlg ��Ϣ�������

BOOL CCorpImServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCorpImServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCorpImServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCorpImServerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CCorpImServerDlg::OnBnClickedButtonSetSystem()
{
	//ϵͳ�趨
	 CDlgSetSystem dlg;
	if(IDOK==dlg.DoModal())
	{
		//����ϵͳ�趨
	}
}

//���񿪹�״̬��ʾ
void CCorpImServerDlg::OnbnClickedButtonServer()
{
	//�������رշ���
	if (!m_bServiceOn)
	{
		//��������
		if (StartService())
		{
			m_bServiceOn=TRUE;
			SetDlgItemText(IDC_STATIC_SERVICE_STATUS,L"����������");
			SetDlgItemText(IDC_BUTTON_SERVER,L"�رշ���");
		}
		else
		{
			//�رշ���
			if (StopService())
			{
				m_bServiceOn=FALSE;
				SetDlgItemText(IDC_STATIC_SERVICE_STATUS,L"����δ����");
				SetDlgItemText(IDC_BUTTON_SERVER,L"��������");
			}
		}
	}
}

//��������˵ļ�������
BOOL CCorpImServerDlg::ServiceListen(void)
{
	BOOL ret=TRUE;
	//��ȡ��������
	in_addr ServiceIp;
	UINT ServicePort;
	CString ServiceName;
	g_dmCorpIm.GetSystemInfo(ServiceIp.S_un.S_addr,ServicePort,ServiceName);
	CString strIp(inet_ntoa(ServiceIp));
	if(m_ListendSocket.Create(ServicePort,SOCK_STREAM,strIp))
	{
		//����
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


//��������˵����ݷַ�����
DWORD WINAPI ThreadProcServiceDispatchData(LPVOID lpParam)
{
	CAnalyser g_Analyser;
	//�ַ�����
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

//��ӷ���˵����ݷ����̵߳Ĵ���
DWORD WINAPI ThreadProcServiceSendData(LPVOID lpParam)
{
	CAnalyser g_Analyser;
	//��������
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

//��ӷ�����������з���Ĵ���
BOOL CCorpImServerDlg::StartService(void)
{
	DWORD dwThreadId;
	//��������
	if (!ServiceListen())
	{
		return FALSE;
	}

	//�������ݷַ��߳�
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

//��ӷ���ر����з���Ĵ���
BOOL CCorpImServerDlg::StopService(void)
{
	BOOL bStoped=TRUE;
	//��ֹ���ݷַ��߳�
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
