#pragma once
#include <afxdb.h>  //MFC���ݿ�֧��


struct GROUP_INFO;
struct TABLE_GROUP_INFO;//��֯�ṹ��
struct TABLE_USER_INFO;//�û���
struct TABLE_LOGIN;//��½��
struct TABLE_MESSAGE_INFO;//�����



// CDataModule �Ի���

class CDataModule : public CDialogEx
{
	DECLARE_DYNAMIC(CDataModule)

public:
	CDataModule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataModule();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CDatabase m_dbCorpIm;//��ҵͨ�Ŷ����ݿ�����
	CRecordset m_rsLogin;//��¼
	CRecordset m_rsGroup;//��֯�ṹ
	CRecordset m_rsUserInfo;//�û���Ϣ
	CRecordset m_rsServerInfo;//��������Ϣ
	CRecordset m_rsMessageInfo;//��Ϣ����
public:
	//�ر����ݿ�����
	void CloseDB(void);
	
	//�������ݿ�
	BOOL ConnectDB(void);

	//��֤�û���������
	BOOL CheckLoginUser(CString UserName,CString Password);

	//��ȡϵͳ��Ϣ
	BOOL GetSystemInfo(DWORD &ServiceIp,UINT &ServicePort,CString &ServiceName);

	//����ϵͳ��Ϣ
	BOOL SetSystemInfo(LONG ServiceIp,LONG ServicePort,CString ServiceName);

	//��ȡ��֯��Ϣ
	BOOL GetGroups(CTreeCtrl &Groups);

	//��ȡ�Ӽ���֯��Ϣ
	BOOL GetSubGroups(int GroupId,HTREEITEM GroupItem,CTreeCtrl &Groups);

	//��ȡ�û���Ϣ
	BOOL GetUsers(int GroupId,CListCtrl &Users);

	//�����֯��Ϣ
	BOOL InsertGroup(TABLE_GROUP_INFO &GroupInfo);

	//�޸���֯��Ϣ
	BOOL EditGroup(TABLE_GROUP_INFO &GroupInfo,int OldGroupId);

	//ɾ����֯��Ϣ
	BOOL DeleteGroup(int GroupId);

	//����û���Ϣ
	BOOL InsertUser(TABLE_USER_INFO &UserInfo);

	//�޸��û���Ϣ
	BOOL EditUser(TABLE_USER_INFO &UserInfo,CString &OldUserId);

	//ɾ���û���Ϣ
	BOOL DeleteUser(CString &UserId);

	//��ȡ������Ϣ
	BOOL GetMessages(CListCtrl &Messages);
	
	//��ӹ�����Ϣ
	BOOL InsertMessage(TABLE_MESSAGE_INFO &MessageInfo);

	//�޸Ĺ�����Ϣ
	BOOL EditMessage(TABLE_MESSAGE_INFO &MessageInfo,int OldMessageId);

	//ɾ��������Ϣ
	BOOL DeleteMessage(int MessageId);
};


const int FIND_SIGNALE_RECORD =1;//����һ����������������

struct GROUP_INFO
{
	int GroupId;// ��֯���
	int ParentGroupId;//�ϼ���֯���
	CString GroupName;//��֯����
};

struct TABLE_GROUP_INFO
{
	int GroupId;
	int ParentId;
	CString GroupName;
	CString GroupMemo;
};

struct TABLE_USER_INFO
{
	CString UserId;
	CString UserName;
	int GroupId;
	CString Job;
	CString JobPhone;
	CString HandPhone;
	CString Fax;
	CString Email;
	CString JobAddress;
	CString PostCode;
	CString Sex;
	CString Birthday;
	CString Other;
};

struct TABLE_LOGIN
{
	CString LoginUserId;
	CString Password;
	BOOL IsAdmin;
};

struct TABLE_MESSAGE_INFO
{
	int MessageId;
	CString MessageTitle;
	CString MessageWriter;
	CString MessageTime;
	CString MessageContent;
	BOOL MessageIsPublished;
};
