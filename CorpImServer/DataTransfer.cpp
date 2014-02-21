// DataTransfer.cpp : ʵ���ļ�
//
#pragma  once
#include "stdafx.h"
#include "CorpImServer.h"
#include "DataTransfer.h"
#include "common.h"

vector<CDataTransfer*> Clients;//��¼���ӵĿͻ���

// CDataTransfer
CDataTransfer::CDataTransfer()
{
	//���������շ�������
	m_ReceiveBuf=new char[BUFF_SIZE];
}

CDataTransfer::~CDataTransfer()
{
	//���������շ�������
	delete[] m_ReceiveBuf;
}


// CDataTransfer ��Ա����

vector<DATA_INFO*> g_RecieveDatas;//���ݽ��ջ���
vector<DATA_INFO*> g_SendData;//���ݷ��ͻ���

void CDataTransfer::OnAccept(int nErrorCode)
{
	//�����ͻ������ӵļ���
	CDataTransfer *pClient=new CDataTransfer;
	SOCKADDR addr;
	int size=sizeof(SOCKADDR);
	if (Accept(*pClient,&addr,&size))
	{
		Clients.push_back(pClient);
	}
	CSocket::OnAccept(nErrorCode);
}

void CDataTransfer::OnClose(int nErrorCode)
{
	//�����ӹرպ�ӿͻ����б���ɾ��������
	for (vector<CDataTransfer*>::iterator i=Clients.begin();i!=Clients.end();i++)
	{
		if ((*i)->m_hSocket==m_hSocket)
		{
			delete *i;
			Clients.erase(i);
			break;
		}
	}
	CSocket::OnClose(nErrorCode);
}

//���մ���
void CDataTransfer::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	//��ȡ���ݣ��������ݷ����ڻ�������
	int nReceivedSize=Receive(m_ReceiveBuf,BUFF_SIZE);
	if (nReceivedSize>0)
	{
		DATA_INFO *ReceiveData=new DATA_INFO;
		ReceiveData->m_Buff=new BYTE[nReceivedSize];
		memcpy(ReceiveData->m_Buff,m_ReceiveBuf,nReceivedSize);
		ReceiveData->m_Socket=m_hSocket;
		ReceiveData->m_BuffSize=nReceivedSize;
		g_RecieveDatas.push_back(ReceiveData);
		g_eventDispatch.SetEvent();
	}
}

//���ʹ���
void CDataTransfer::OnSend(int nErrorCode)
{
	//��CSocket�и÷������κ�Ч������Ҫ������ṩ���ͽӿ�
	CSocket::OnSend(nErrorCode);
}
