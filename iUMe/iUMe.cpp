
// iUMe.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Resource.h"
#include "iUMe.h"
#include "Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiUMeApp

BEGIN_MESSAGE_MAP(CiUMeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CiUMeApp 构造

CiUMeApp::CiUMeApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CiUMeApp 对象

CiUMeApp theApp;


// CiUMeApp 初始化

BOOL CiUMeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	m_strApp = GetApp();

	CPaintManagerUI::SetInstance(m_hInstance);

	if (!CheckInstance())		// 检查是否有另一个实例运行
		return FALSE;
#if 0
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\iUMe"));
#else	
	CPaintManagerUI::SetResourceZip(_T("iUMe.zip"));
#endif

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	CClient* pFrame = new CClient();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("iUMe"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);	
	pFrame->SetIcon(IDR_Client);		// 设置任务栏中的图标
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	pFrame->SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

void CiUMeApp::SetActiveWindow(HWND hWndActive)
{
	iUMe_Instance_Data *pInstance = (iUMe_Instance_Data *)m_mapping;

	if (pInstance)
		pInstance->hActiveWnd = hWndActive;
}

BOOL CiUMeApp::CheckInstance()
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
