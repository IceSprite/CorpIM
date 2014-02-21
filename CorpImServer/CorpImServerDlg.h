
// CorpImServerDlg.h : ͷ�ļ�
//

#pragma once
#include "DataTransfer.h"


// CCorpImServerDlg �Ի���
class CCorpImServerDlg : public CDialogEx
{
// ����
public:
	CCorpImServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIALOG_CORPIMSERVER };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	BOOL m_bServiceOn;//�����Ƿ��Ѿ�����
	HANDLE m_hThreadServiceDispatchData;//���ݷַ�����
	HANDLE m_hTreadServiceSendData;//���ݷ��ͷ���
	
public:
	BOOL StartService(void);//��������
	BOOL StopService(void);//�رշ���

private:
	CDataTransfer m_ListendSocket;//���������Socket
	BOOL ServiceListen(void);//������������
};
