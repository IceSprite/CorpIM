#pragma once
#include <afxdb.h>  //MFC数据库支持


struct GROUP_INFO;
struct TABLE_GROUP_INFO;//组织结构表
struct TABLE_USER_INFO;//用户表
struct TABLE_LOGIN;//登陆表
struct TABLE_MESSAGE_INFO;//公告表



// CDataModule 对话框

class CDataModule : public CDialogEx
{
	DECLARE_DYNAMIC(CDataModule)

public:
	CDataModule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataModule();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CDatabase m_dbCorpIm;//企业通信端数据库连接
	CRecordset m_rsLogin;//登录
	CRecordset m_rsGroup;//组织结构
	CRecordset m_rsUserInfo;//用户信息
	CRecordset m_rsServerInfo;//服务器信息
	CRecordset m_rsMessageInfo;//信息管理
public:
	//关闭数据库连接
	void CloseDB(void);
	
	//连接数据库
	BOOL ConnectDB(void);

	//验证用户名与密码
	BOOL CheckLoginUser(CString UserName,CString Password);

	//获取系统信息
	BOOL GetSystemInfo(DWORD &ServiceIp,UINT &ServicePort,CString &ServiceName);

	//设置系统信息
	BOOL SetSystemInfo(LONG ServiceIp,LONG ServicePort,CString ServiceName);

	//获取组织信息
	BOOL GetGroups(CTreeCtrl &Groups);

	//获取子级组织信息
	BOOL GetSubGroups(int GroupId,HTREEITEM GroupItem,CTreeCtrl &Groups);

	//获取用户信息
	BOOL GetUsers(int GroupId,CListCtrl &Users);

	//添加组织信息
	BOOL InsertGroup(TABLE_GROUP_INFO &GroupInfo);

	//修改组织信息
	BOOL EditGroup(TABLE_GROUP_INFO &GroupInfo,int OldGroupId);

	//删除组织信息
	BOOL DeleteGroup(int GroupId);

	//添加用户信息
	BOOL InsertUser(TABLE_USER_INFO &UserInfo);

	//修改用户信息
	BOOL EditUser(TABLE_USER_INFO &UserInfo,CString &OldUserId);

	//删除用户信息
	BOOL DeleteUser(CString &UserId);

	//获取公告信息
	BOOL GetMessages(CListCtrl &Messages);
	
	//添加公告信息
	BOOL InsertMessage(TABLE_MESSAGE_INFO &MessageInfo);

	//修改公告信息
	BOOL EditMessage(TABLE_MESSAGE_INFO &MessageInfo,int OldMessageId);

	//删除公告信息
	BOOL DeleteMessage(int MessageId);
};


const int FIND_SIGNALE_RECORD =1;//仅有一条符合条件的数据

struct GROUP_INFO
{
	int GroupId;// 组织编号
	int ParentGroupId;//上级组织编号
	CString GroupName;//组织名称
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
