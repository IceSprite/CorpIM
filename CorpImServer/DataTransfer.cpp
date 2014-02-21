// DataTransfer.cpp : 实现文件
//
#pragma  once
#include "stdafx.h"
#include "CorpImServer.h"
#include "DataTransfer.h"
#include "common.h"

vector<CDataTransfer*> Clients;//记录连接的客户端

// CDataTransfer
CDataTransfer::CDataTransfer()
{
	//申明数据收发缓冲区
	m_ReceiveBuf=new char[BUFF_SIZE];
}

CDataTransfer::~CDataTransfer()
{
	//回收数据收发缓冲区
	delete[] m_ReceiveBuf;
}


// CDataTransfer 成员函数

vector<DATA_INFO*> g_RecieveDatas;//数据接收缓冲
vector<DATA_INFO*> g_SendData;//数据发送缓冲

void CDataTransfer::OnAccept(int nErrorCode)
{
	//建立客户端连接的集合
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
	//当连接关闭后从客户端列表中删除该连接
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

//接收处理
void CDataTransfer::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	//获取数据，并将数据放置在缓冲区中
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

//发送处理
void CDataTransfer::OnSend(int nErrorCode)
{
	//在CSocket中该方法无任何效果，需要向外界提供发送接口
	CSocket::OnSend(nErrorCode);
}
