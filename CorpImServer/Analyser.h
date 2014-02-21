#pragma once

#include "DataTransfer.h"

//��������ͷ��Ϣ�Ĵ�С
const int TRANSFER_DATA_HEAD_SIZE=sizeof(UINT) + sizeof(int);
const int DATA_INFO_HEAD_SIZE=sizeof(SOCKET) + sizeof(int);

class CAnalyser
{
public:
	CAnalyser(void);
	~CAnalyser(void);

public:
	void Dispatch(void);//�ַ�����
	void Encapsulate(SOCKET s,int Protocol,BYTE *Data,int BuffSize);//��װ����
	void SendDate(void);//��������

private:
	BOOL ReadData(TRANSFER_DATA *&pData);//��ȡ����
};


