// DataModule.cpp : 实现文件
//

#include "stdafx.h"
#include "CorpImServer.h"
#include "DataModule.h"
#include "afxdialogex.h"
#include<vector>
using namespace std;
#include "common.h"



// CDataModule 对话框

IMPLEMENT_DYNAMIC(CDataModule, CDialogEx)

CDataModule::CDataModule(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataModule::IDD, pParent),
	m_rsLogin(&m_dbCorpIm),
	m_rsGroup(&m_dbCorpIm),
	m_rsUserInfo(&m_dbCorpIm),
	m_rsServerInfo(&m_dbCorpIm),
	m_rsMessageInfo(&m_dbCorpIm)
{

}

CDataModule::~CDataModule()
{
	CloseDB();
}

void CDataModule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataModule, CDialogEx)
END_MESSAGE_MAP()


// CDataModule 消息处理程序

void CDataModule::CloseDB(void)
{
	//关闭数据表
	if(m_rsLogin.IsOpen())
	{
		m_rsLogin.Close();
	}

	if(m_rsGroup.IsOpen())
	{
		m_rsGroup.Close();
	}

	if(m_rsUserInfo.IsOpen())
	{
		m_rsUserInfo.Close();
	}

	if(m_rsMessageInfo.IsOpen())
	{
		m_rsMessageInfo.Close();
	}

	if(m_dbCorpIm.IsOpen())
	{
		m_dbCorpIm.Close();
	}
}

BOOL CDataModule::ConnectDB(void)
{
	BOOL ret = TRUE;
	//连接数据库
	m_dbCorpIm.Open(L"CorpIm");
	if(!m_dbCorpIm.IsOpen())
	{
		ret = FALSE;
	}
	return ret;
}

BOOL CDataModule::CheckLoginUser(CString UserName,CString Password)
{
	//关闭原有数据集
	if(m_rsLogin.IsOpen())
	{
		m_rsLogin.Close();
	}
	//合成sql语句
	BOOL ret = TRUE;
	CString strSql;
	strSql.Format(L"SELECT * FROM login WHERE IsAdmin =%d AND LoginUserId= '%s' AND LoginPassword='%s'",TRUE,UserName,Password);

	//验证登录数据
	m_rsLogin.Open(AFX_DB_USE_DEFAULT_TYPE,strSql);
	if(m_rsLogin.IsOpen())
	{
		//仅返回一条记录说明用户名，密码验证通过
		if (FIND_SIGNALE_RECORD == m_rsLogin.GetRecordCount())
		{
			ret = TRUE;
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		ret = FALSE;
	}
	return ret;
}

BOOL CDataModule::GetSystemInfo(DWORD &ServiceIp,UINT &ServicePort,CString &ServiceName)
{
	//关闭原数据库
	if (m_rsServerInfo.IsOpen())
	{
		m_rsServerInfo.Close();
	}
	BOOL ret=TRUE;
	//合成SQL语句
	CString strSql(L"select *from ServerInfo");
	//打开数据库
	m_rsServerInfo.Open(AFX_DB_USE_DEFAULT_TYPE,strSql);
	if (m_rsServerInfo.IsOpen())
	{
		m_rsServerInfo.MoveFirst();
		CDBVariant RetValue;
		//服务地址
		RetValue.Clear();
		m_rsServerInfo.GetFieldValue(L"ServiceIP",RetValue);
		ServicePort=RetValue.m_lVal;
		//服务名称
		RetValue.Clear();
		m_rsServerInfo.GetFieldValue(L"ServiceName",RetValue);
		ServiceName=*RetValue.m_pstring;
		//关闭数据库
		m_rsServerInfo.Close();
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::SetSystemInfo(LONG ServiceIp,LONG ServicePort,CString ServiceName)
{
	BOOL ret=TRUE;
	//合成SQL语句
	CString strSql;
	strSql.Format(L"update ServerInfo set ServiceIp=%u,ServicePort=%u,ServiceName='%s'",ServiceIp,ServicePort,ServiceName);
	//执行脚本
	m_dbCorpIm.ExecuteSQL(strSql);

	return ret;
}

const int ROOT_ID=0;//在此规定根的ID为
BOOL CDataModule::GetGroups(CTreeCtrl &Groups)
{
	//初始化数据集
	if (m_rsGroup.IsOpen())
	{
		m_rsGroup.Close();
	}
	BOOL ret=TRUE;
	//获取根
	//合成脚本
	CString strSql;
	strSql.Format(L"select * from GroupInfo where GroupId=%d",ROOT_ID);
	if (m_rsGroup.GetRecordCount()>0)
	{
		m_rsGroup.MoveFirst();
		CDBVariant RetValue;
		//GroupID
		RetValue.Clear();
		m_rsGroup.GetFieldValue(L"GroupID",RetValue);
		int nGroupsId=RetValue.m_lVal;
		//GroupName
		RetValue.Clear();
		m_rsGroup.GetFieldValue(L"GroupName",RetValue);
		//由于不是有那个图形，因此在此使用image和selectedimage分别记录各GroupI和ParentGroupId
		HTREEITEM hTreeItem =Groups.InsertItem(*RetValue.m_pstring,nGroupsId,ROOT_ID);
		GetSubGroups(ROOT_ID,hTreeItem,Groups);
	} 
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::GetSubGroups(int GroupId,HTREEITEM GroupItem,CTreeCtrl &Groups)
{
	//初始化数据库
	if (m_rsGroup.IsOpen())
	{
		m_rsGroup.Close();
	}
	BOOL ret=TRUE;
	//合成子组织
	//合成脚本
	CString strSql;
	strSql.Format(L"select * from GroupInfo where ParentGroupID=%d",GroupId);
	m_rsGroup.Open(AFX_DB_USE_DEFAULT_TYPE,strSql);
	//获取数据
	if (m_rsGroup.GetRecordCount()>0)
	{
		m_rsGroup.MoveFirst();
		//using std::vector;
		vector<GROUP_INFO*> SubGroups;
		do 
		{
			GROUP_INFO *pGroup=new GROUP_INFO;

			CDBVariant RetValue;
			RetValue.Clear();
			m_rsGroup.GetFieldValue(L"GroupId",RetValue);
			pGroup->GroupId=RetValue.m_lVal;
			RetValue.Clear();
			m_rsGroup.GetFieldValue(L"ParentgroupId",RetValue);
			pGroup->ParentGroupId=RetValue.m_lVal;
			RetValue.Clear();
			m_rsGroup.GetFieldValue(L"GroupName",RetValue);
			pGroup->GroupName=*RetValue.m_pstring;

			SubGroups.push_back(pGroup);

			m_rsGroup.MoveNext();
		} while (!m_rsGroup.IsEOF());

		//插入树形控件
		for (int i=0;i<SubGroups.size();i++)
		{
			HTREEITEM hTreeItem=Groups.InsertItem(SubGroups[i]->GroupName,SubGroups[i]->GroupId,SubGroups[i]->ParentGroupId,GroupItem);
			GetSubGroups(SubGroups[i]->GroupId,hTreeItem,Groups);
		}

		//回收资源
		for (int i=0;i<SubGroups.size();i++)
		{
			delete SubGroups[i];
		}
		SubGroups.clear();
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

const int USER_NAME_COL_ID=1;//"用户名"的列序号
BOOL CDataModule::GetUsers(int GroupId,CListCtrl &Users)
{
	BOOL ret=TRUE;
	//清空用户集原有内容
	Users.DeleteAllItems();
	//初始化数据集
	if(m_rsUserInfo.IsOpen())
	{
		m_rsUserInfo.Close();
	}

	//获取子组织
	//合成脚本
	CString strSql;
	strSql.Format(L"select * from UserInfo where GroupID=%d",GroupId);
	m_rsUserInfo.Open(AFX_DB_USE_DEFAULT_TYPE,strSql);
	//获取数据
	if (m_rsUserInfo.GetRecordCount()>0)
	{
		m_rsUserInfo.MoveFirst();
		CDBVariant RetValue;
		CString UserId;
		CString UserName;
		do 
		{
			RetValue.Clear();
			m_rsGroup.GetFieldValue(L"UserId",RetValue);
			UserId=*RetValue.m_pstring;
			RetValue.Clear();
			m_rsGroup.GetFieldValue(L"UserName",RetValue);
			UserName=*RetValue.m_pstring;
			//插入数据
			Users.InsertItem(Users.GetItemCount(),UserId);
			Users.SetItemText(Users.GetItemCount()-1,USER_NAME_COL_ID,UserName);
		} while (m_rsUserInfo.IsEOF());
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::InsertGroup(TABLE_GROUP_INFO &GroupInfo)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"insert into GroupInfo (GroupID,ParentGroupID,GroupName,GroupMemo) values (%d,%d,'%s','%s')",GroupInfo.GroupId,GroupInfo.ParentId,GroupInfo.GroupName,GroupInfo.GroupMemo);
	try
	{
		//执行添加动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::EditGroup(TABLE_GROUP_INFO &GroupInfo,int OldGroupId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"UPDATE GroupInfo SET GroupID=%d,ParentGroupID=%d,GroupName='%s',GroupMemo='%s' WHERE GroupId=%d",GroupInfo.GroupId,GroupInfo.ParentId,GroupInfo.GroupName,GroupInfo.GroupMemo,OldGroupId);
	try
	{
		//执行添加动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::DeleteGroup(int GroupId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"DELETE FROM GroupInfo WHERE GroupId=%d",GroupId);
	try
	{
		//执行添加动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::InsertUser(TABLE_USER_INFO &UserInfo)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"insert into GroupInfo(UserId,UserName,groupId,Job,JobPhone,HandPhone,Fax,Email,JobAddress,PostCode,Sex,Birthday,Other) values('%s','%s',%d,'%s','%s','%s','%s','%s','%s','%s',%d,'%s','%s')",UserInfo.UserId,UserInfo.UserName,UserInfo.GroupId,UserInfo.Job,UserInfo.JobPhone,UserInfo.HandPhone,UserInfo.Fax,UserInfo.Email,UserInfo.JobAddress,UserInfo.PostCode,UserInfo.Sex,UserInfo.Birthday,UserInfo.Other);
	try
	{
		//执行添加动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::EditUser(TABLE_USER_INFO &UserInfo,CString &OldUserId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"UPDATE GroupInfo SET UserId='%s',UserName='%s',GroupId=%d,Job='%s',JobPhone='%s',HandPhone='%s',Fax='%s',Email='%s',JobAddress='%s',PostCode='%s',Sex=%d,Birthday='%s',Other='%s' WHERE UserID='%s'",UserInfo.UserId,UserInfo.UserName,UserInfo.GroupId,UserInfo.Job,UserInfo.JobPhone,UserInfo.HandPhone,UserInfo.Fax,UserInfo.Email,UserInfo.JobAddress,UserInfo.PostCode,UserInfo.Sex,UserInfo.Birthday,UserInfo.Other,OldUserId);
	try
	{
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::DeleteUser(CString &UserId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"DELETE FROM UserInfo WHERE UserID='%s'",UserId);
	try
	{
		//执行删除动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;	
	}
	return ret;
}

BOOL CDataModule::GetMessages(CListCtrl &Messages)
{
	Messages.DeleteAllItems();
	BOOL ret=TRUE;
	if (m_rsMessageInfo.IsOpen())
	{
		m_rsMessageInfo.Close();
	}
	//合成SQL
	CString strSql;
	strSql.Format(L"SELECT * FROM MessageInfo");
	if (m_rsMessageInfo.Open(AFX_DB_USE_DEFAULT_TYPE,strSql))
	{
		//获取数据
		if (m_rsMessageInfo.GetRecordCount()>0)
		{
			m_rsMessageInfo.MoveFirst();
			CDBVariant RetValue;
			TABLE_MESSAGE_INFO message;
			do 
			{
				RetValue.Clear();
				m_rsMessageInfo.GetFieldValue(L"MessageId",RetValue);
				message.MessageId=RetValue.m_lVal;
				RetValue.Clear();
				m_rsMessageInfo.GetFieldValue(L"MessageIsPublished",RetValue);
				message.MessageIsPublished=RetValue.m_boolVal;
				RetValue.Clear();
				m_rsMessageInfo.GetFieldValue(L"MessageTitle",RetValue);
				message.MessageTitle=*RetValue.m_pstring;
				RetValue.Clear();
				m_rsMessageInfo.GetFieldValue(L"MessageTime",RetValue);
				message.MessageTime=*RetValue.m_pstring;
				//插入数据
				CString str;
				str.Format(L"%d",message.MessageId);
				Messages.InsertItem(0,str);
				if (message.MessageIsPublished)
				{
					str=L"√";
				}
				else
				{
					str=L" ";
				}
				Messages.SetItemText(0,COL_MESSAGE_IS_PUBLISHED,str);
				Messages.SetItemText(0,COL_MESSAGE_TITLE,message.MessageTitle);
				Messages.SetItemText(0,COL_MESSAGE_TIME,message.MessageTime);
				m_rsMessageInfo.MoveNext();
			} while (!m_rsMessageInfo.IsEOF());
		}
		else
		{
			ret=FALSE;
		}
	}
	return ret;
}

BOOL CDataModule::InsertMessage(TABLE_MESSAGE_INFO &MessageInfo)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"insert into MessageInfo (MessageId,MessageTitle,MessageWriter,MessageTime,MessageContent,MessageIsPublished) values(%d,'%s','%s','%s','%s',%d)",MessageInfo.MessageId,MessageInfo.MessageTitle,MessageInfo.MessageWriter,MessageInfo.MessageTime,MessageInfo.MessageContent,MessageInfo.MessageIsPublished);
	try
	{
		//执行添加动作
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CDataModule::EditMessage(TABLE_MESSAGE_INFO &MessageInfo,int OldMessageId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString StrSql;
	StrSql.Format(L"UPDATE MessageInfo SET MessageId =%d,MessageTitle='%s',MessageWriter='%s',MessageTime='%s',MessageContent='%s',MessageIsPublished=%d WHERE MessageId=%d",MessageInfo.MessageId,MessageInfo.MessageTitle,MessageInfo.MessageWriter,MessageInfo.MessageTime,MessageInfo.MessageContent,MessageInfo.MessageIsPublished,OldMessageId);
	try
	{
		//执行修改动作
		m_dbCorpIm.ExecuteSQL(StrSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;	
	}
	return ret;
}

BOOL CDataModule::DeleteMessage(int MessageId)
{
	BOOL ret=TRUE;
	//合成SQL文本
	CString strSql;
	strSql.Format(L"DELETE FROM MessageInfo WHERE MessageId =%d",MessageId);
	try
	{
		m_dbCorpIm.ExecuteSQL(strSql);
	}
	catch (CMemoryException* e)
	{
		ret=FALSE;
	}
	return ret;
}