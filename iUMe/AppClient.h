#pragma once

#ifndef __APP_CLIENT_H__
#define __APP_CLIENT_H__

namespace DuiLib
{

typedef struct tag_AppInfo
{
	CDuiString strName;			// Ӧ������
	CDuiString strExe;			// Exe����(��.exe)
	int nImage;					// Ӧ��ͼ������
	bool bIsLocal;				// �Ƿ񱾵�Ӧ�ã��Դ�Ӧ����Ϊ����Ӧ�ã��û����Ӧ����Ϊ������Ӧ�ã�
	bool bIsNew;				// �Ƿ���Ӧ�ã�����Ӧ�����ԣ�
	bool bIsHot;				// �Ƿ�����Ӧ�ã�����Ӧ�����ԣ�
}APP_INFO;

class CAppClient : public CTileLayoutUI
{
public:
	CAppClient(CPaintManagerUI& paint_manager);
	virtual ~CAppClient(void);

public:
	bool AddNode(APP_INFO *item);
	void InEdit();
	bool RemoveAt(int nIndex);
	bool GetEdit() const;

private:
	CPaintManagerUI& m_pm;
	CDialogBuilder m_dlgBuilder;
	bool m_bEdit;
};

}	// namespace DuiLib

#endif