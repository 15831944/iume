
// iUMeCalendar.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "iUMeCalendar.h"
//#include "iUMeCalendarDlg.h"
#include "Calendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiUMeCalendarApp

BEGIN_MESSAGE_MAP(CiUMeCalendarApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CiUMeCalendarApp ����

CiUMeCalendarApp::CiUMeCalendarApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiUMeCalendarApp ����

CiUMeCalendarApp theApp;


// CiUMeCalendarApp ��ʼ��

BOOL CiUMeCalendarApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	m_strApp = GetApp();

	CPaintManagerUI::SetInstance(m_hInstance);

	if (!CheckInstance())		// ����Ƿ�����һ��ʵ������
		return FALSE;

	CPaintManagerUI::SetResourceZip(_T("calendar.zip"));

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	CCalendar* pFrame = new CCalendar();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("С����"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);	
	pFrame->SetIcon(IDR_MAINFRAME);		// �����������е�ͼ��
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	//pFrame->SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	//CiUMeCalendarDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void CiUMeCalendarApp::SetActiveWindow(HWND hWndActive)
{
	iUMe_Instance_Data *pInstance = (iUMe_Instance_Data *)m_mapping;

	if (pInstance)
		pInstance->hActiveWnd = hWndActive;
}

BOOL CiUMeCalendarApp::CheckInstance()
{
	BOOL bRet = FALSE;
	HRESULT hRet = E_FAIL;
	BOOL bAlreadyExisted = FALSE;

	if (NULL != m_mapping.GetHandle())
		return TRUE;

	hRet = m_mapping.MapSharedMem(sizeof(iUMe_Instance_Data), IUME_INSTANCE_OBJECT_NAME, &bAlreadyExisted);
	if (FAILED(hRet))
		return bRet;

	if (bAlreadyExisted)
	{
		HWND hWndActive = ((iUMe_Instance_Data *)m_mapping)->hActiveWnd;

		if (IsWindowRunBackGround(hWndActive))
		{
			SetWindowRunBackGround(hWndActive, FALSE);
		}

		if (::IsIconic(hWndActive))
			::SendMessage(hWndActive, WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);

		::SetWindowPos(hWndActive, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		::SetForegroundWindow(hWndActive);
		::SetFocus(hWndActive);

		goto Exit0;
	}

	bRet = TRUE;

Exit0:

	return bRet;
}