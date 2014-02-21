#pragma  once
#include "StdAfx.h"
#include "Analyser.h"


CAnalyser::CAnalyser(void)
{
}


CAnalyser::~CAnalyser(void)
{
}

void CAnalyser::Dispatch(void)
{
	TRANSFER_DATA *pData=new TRANSFER_DATA;
	while (TRUE)
	{
		//读取数据，获取数据
		if (ReadData(pData))
		{
			switch(pData->m_Protocol)
			{
			default:
				break;
			}
		}
	}
}

//数据的读取
BOOL CAnalyser::ReadData(TRANSFER_DATA *&pData)
{
	BOOL ret=TRUE;
	if (!g_RecieveDatas.empty())
	{
		//获取有效数据
		memcpy(pData,g_RecieveDatas[0]->m_Buff,TRANSFER_DATA_HEAD_SIZE);
		//因为后面会POPUP，再次可以直接使用，减少COPY
		//回收时应按照DATA_INFO进行删除，否则会造成内存的慢泄露
		pData->m_Data=g_RecieveDatas[0]->m_Buff+TRANSFER_DATA_HEAD_SIZE;
		pData->m_pDataInfo=g_RecieveDatas[0];
		g_RecieveDatas.pop_back();
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

//协议封装
void CAnalyser::Encapsulate(SOCKET s,int Protocol,BYTE *Data,int BuffSize)
{
	DATA_INFO *pDataInfo=new DATA_INFO;
	
	//复制socket
	pDataInfo->m_Socket=s;
	//计算总数据大小
	pDataInfo->m_BuffSize=TRANSFER_DATA_HEAD_SIZE + BuffSize;
	//传输数据存储空间
	pDataInfo->m_Buff=new BYTE[pDataInfo->m_BuffSize];
	//复制总数据大小
	int nSize=BuffSize + TRANSFER_DATA_HEAD_SIZE;
	memcpy(pDataInfo->m_Buff,&nSize,sizeof(int));
	//复制协议内容
	memcpy(pDataInfo->m_Buff + sizeof(int),&Protocol,sizeof(int));
	//复制协议数据
	if (NULL!=Data)
	{
		memcpy(pDataInfo->m_Buff + TRANSFER_DATA_HEAD_SIZE,Data,BuffSize);
	}
	g_SendDatas.push_back(pDataInfo);
}

//数据发送
void CAnalyser::SendDate(void)
{
	if(!g_SendDatas.empty())
	{
		g_SendDatas.pop_back();
	}
}
