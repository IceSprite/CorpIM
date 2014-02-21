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
		//��ȡ���ݣ���ȡ����
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

//���ݵĶ�ȡ
BOOL CAnalyser::ReadData(TRANSFER_DATA *&pData)
{
	BOOL ret=TRUE;
	if (!g_RecieveDatas.empty())
	{
		//��ȡ��Ч����
		memcpy(pData,g_RecieveDatas[0]->m_Buff,TRANSFER_DATA_HEAD_SIZE);
		//��Ϊ�����POPUP���ٴο���ֱ��ʹ�ã�����COPY
		//����ʱӦ����DATA_INFO����ɾ�������������ڴ����й¶
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

//Э���װ
void CAnalyser::Encapsulate(SOCKET s,int Protocol,BYTE *Data,int BuffSize)
{
	DATA_INFO *pDataInfo=new DATA_INFO;
	
	//����socket
	pDataInfo->m_Socket=s;
	//���������ݴ�С
	pDataInfo->m_BuffSize=TRANSFER_DATA_HEAD_SIZE + BuffSize;
	//�������ݴ洢�ռ�
	pDataInfo->m_Buff=new BYTE[pDataInfo->m_BuffSize];
	//���������ݴ�С
	int nSize=BuffSize + TRANSFER_DATA_HEAD_SIZE;
	memcpy(pDataInfo->m_Buff,&nSize,sizeof(int));
	//����Э������
	memcpy(pDataInfo->m_Buff + sizeof(int),&Protocol,sizeof(int));
	//����Э������
	if (NULL!=Data)
	{
		memcpy(pDataInfo->m_Buff + TRANSFER_DATA_HEAD_SIZE,Data,BuffSize);
	}
	g_SendDatas.push_back(pDataInfo);
}

//���ݷ���
void CAnalyser::SendDate(void)
{
	if(!g_SendDatas.empty())
	{
		g_SendDatas.pop_back();
	}
}
