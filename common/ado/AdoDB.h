
/********************************************************************
** Copyright (c) 2012,���ڹ���ͨ����Ƶ�з���ҵ�� All rights reserved. 
** ժ    Ҫ����Ҫ��װ�����ݿ�����ĺ���
** ��    �ߣ�fansujun
** �������ڣ�20121001
** ��    ע��������Ҫ��ʼ��
*********************************************************************/

#pragma once

#ifndef __ADO_DB_H__
#define __ADO_DB_H__

// ���ADO�����ӿ�
#import "c:\Program Files\Common Files\system\ado\msadox.dll"				// ���ڴ���Access���ݿ�
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

typedef struct _stDatabaseTableStruct
{
	LPCTSTR lpTbName;
	int nType;
	int nLen;
}DB_TB_STRUCT;

class CAdoDB  
{
public:
	CAdoDB();
	virtual ~CAdoDB(void);

public:	
	bool AdoConnect(const char *user, const char *pwd, const char *srvip, const char *dbname);
	bool AdoOpen(const char *sql, _RecordsetPtr &recPtr);
	bool AdoExecute(const char *sql, _RecordsetPtr &recPtr, long lOptions = adCmdText);
	void AdoClose();
	bool IsConnect() const;
	bool AddTable(const char *tablename, DB_TB_STRUCT stTbStruct[], int nCount);	
	bool AddDatabase(const char *dbname);	// ����Access���ݿ�ʱ��dbname����Ϊ���ݿ��ļ�����·��
	bool AddAccessPwd(const char *password, const char *mdb);	// ��������Access���ݿ��ļ���ӷ�������

protected:
	_ConnectionPtr	m_pConnect;															// ���ݿ����Ӷ���
	_RecordsetPtr	m_pRecordSet;														// ���ݿ��¼������
	_CommandPtr		m_pCommand;															// �������

public:

private:
	bool m_bConnect;
	char m_user[100];
	char m_password[100];
	char m_databasesrc[MAX_PATH];
};


#endif	// __ADO_DB_H__