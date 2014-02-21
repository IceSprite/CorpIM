#pragma once

#include <vector>
using namespace std;
#include "afxsock.h"// CDataTransfer ����Ŀ��

//���ݷַ��¼�
extern CEvent g_eventDispatch;
//���ݷ����߳�
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
	char *m_ReceiveBuf;//�������ݻ�����
};

extern vector<CDataTransfer*> Clients;//��¼���ӵĿͻ���

const int BUFF_SIZE=1024*1;//1K�ֽڵĻ���

//�շ�������Ϣ�ṹ
struct DATA_INFO
{
	int m_BuffSize;
	SOCKET m_Socket;
	BYTE *m_Buff;//���ݴ洢��λ��
	DATA_INFO():m_BuffSize(0),m_Socket(0),m_Buff(NULL){}
	~DATA_INFO(){if (NULL!=m_Buff){delete[] m_Buff;}}
};
extern vector<DATA_INFO*> g_RecieveDatas;//���ݽ��ջ���

extern vector<DATA_INFO*> g_SendDatas;//���ݷ��ͻ���


//Э�����ģ��
struct TRANSFER_DATA
{
	UINT m_Size;//�������������С
	int m_Protocol;//Э������
	BYTE *m_Data;//Э������
	DATA_INFO *m_pDataInfo;//������Ϣ��ָ��
};

