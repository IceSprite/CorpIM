#pragma once

#include "DataTransfer.h"

//传输数据头信息的大小
const int TRANSFER_DATA_HEAD_SIZE=sizeof(UINT) + sizeof(int);
const int DATA_INFO_HEAD_SIZE=sizeof(SOCKET) + sizeof(int);

class CAnalyser
{
public:
	CAnalyser(void);
	~CAnalyser(void);

public:
	void Dispatch(void);//分发数据
	void Encapsulate(SOCKET s,int Protocol,BYTE *Data,int BuffSize);//封装数据
	void SendDate(void);//发送数据

private:
	BOOL ReadData(TRANSFER_DATA *&pData);//读取数据
};


