#pragma once

#include <vector>
using namespace std;
#include "afxsock.h"// CDataTransfer 命令目标

//数据分发事件
extern CEvent g_eventDispatch;
//数据发送线程
extern CEvent g_eventSend;

class CDataTransfer : public CSocket
{
public:
	CDataTransfer();
	virtual ~CDataTransfer();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

private:
	char *m_ReceiveBuf;//接收数据缓冲区
};

extern vector<CDataTransfer*> Clients;//记录连接的客户端

const int BUFF_SIZE=1024*1;//1K字节的缓冲

//收发数据信息结构
struct DATA_INFO
{
	int m_BuffSize;
	SOCKET m_Socket;
	BYTE *m_Buff;//数据存储的位置
	DATA_INFO():m_BuffSize(0),m_Socket(0),m_Buff(NULL){}
	~DATA_INFO(){if (NULL!=m_Buff){delete[] m_Buff;}}
};
extern vector<DATA_INFO*> g_RecieveDatas;//数据接收缓冲

extern vector<DATA_INFO*> g_SendDatas;//数据发送缓冲


//协议解析模块
struct TRANSFER_DATA
{
	UINT m_Size;//传输数据整体大小
	int m_Protocol;//协议内容
	BYTE *m_Data;//协议数据
	DATA_INFO *m_pDataInfo;//数据信息的指针
};

