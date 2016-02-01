
#ifndef __MULTI_MENU_H__
#define __MULTI_MENU_H__

const TCHAR* const MenuBkImage = _T("file='menu\\menu_bk.png' corner='30,8,8,8'");
const TCHAR* const ExplandIcon = _T("menu\\right.png");
const TCHAR* const MenuDefaultList = _T("inset=\"2,2,2,2\" bkcolor=\"0xFFE9FFFF\" bordersize=\"0\" header=\"hidden\"");
const TCHAR* const MenuHightLight = _T("file='menu\\menu_hot_bk.png' corner='2,2,2,2'");

struct ContextMenuParam
{
	HWND hWnd;
	WPARAM wParam; // ȡֵΪ1ʱ����ʾ���������˵��� ȡֵΪ2ʱ����ʾֻ��hwnd�������и�������ʾ
};

class MenuElementUI;
class CMultiMenuUI : public CWindowWnd
{
public:
	enum menuLayout: unsigned long
	{
		TEXT_ALIGN_LEFT_DEFAULT = 0,  //�ı�Ĭ�������
		TEXT_ALIGN_CENTER,     //�ı�������ʾ
		TEXT_ALIGN_RIGHT,     //�ı��Ҷ���

		DEFAULT_LINE_HEIGHT = 6,   //Ĭ�Ϸָ�����ռ�߶�
		ITEM_DEFAULT_HEIGHT = 20,   //ÿһ��item��Ĭ�ϸ߶ȣ�ֻ����״����ʱ�Զ��壩
		ITEM_DEFAULT_ICON_WIDTH = 28,  //Ĭ��ͼ����ռ���
		HEADER_DEFAULT_HEIGHT = 40,   //Ĭ�ϵı�ͷ�߶�
		ITEM_DEFAULT_WIDTH = 150,   //���ڵ�Ĭ�Ͽ��
		DEFAULT_TEXT_COLOR = 0xFF000000, //Ĭ��������ɫ
		DEFAULT_LINE_COLOR = 0xFF85E4FF,    //Ĭ�Ϸָ�����ɫ
	};

public:
	CMultiMenuUI(menuLayout textalign = TEXT_ALIGN_LEFT_DEFAULT);

	virtual ~CMultiMenuUI(void);

	LPCTSTR GetWindowClassName() const { return _T("MenuUI"); };

	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };

	LPVOID GetInterface(LPCTSTR pstrName);

	void OnFinalMessage(HWND /*hWnd*/) ;

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/*****
	* ��    �ܣ����ܺ��� ��Ӳ˵�ѡ��
	* ��    ����contentѡ����ı���Ϣ��itemIDѡ���ӦID��iconImageNameѡ�����ͼ�꣬textcol�ı�������ɫ��heightѡ����ռ�߶ȣ�extend�Ƿ�֧����չ
	* �� �� ֵ��֧����չʱ������չ����ָ�룬���򷵻�NULL
	******/
	CMultiMenuUI* Add(LPCTSTR content, UINT itemID = 0, LPCTSTR iconImageName = L"", DWORD textcol = 0xFF000000, int height = 0, bool extend = false);//֧��html�ı�

	CMultiMenuUI* Add(MenuElementUI *pctrl, int height = 0, bool extend = false);//����Զ���ؼ���

	/*****
	* ��    �ܣ����Ʒָ���
	* ��    ����color �ָ�����ʾ����ɫ
	******/
	void AddLine(DWORD color = DEFAULT_LINE_COLOR);

	void SetItemHeight(int height = ITEM_DEFAULT_HEIGHT);//����ѡ���ͳһ�߶�

	void SetItemWidth(int width = ITEM_DEFAULT_WIDTH);//����ѡ��Ŀ�ȣ����˵����ڿ�ȣ�

	/*****
	* ��    �ܣ��������ź�
	* ��    ����param �ź�����

	******/
	void ReceiveCloseMsg(ContextMenuParam &param);

	/*****
	* ��    �ܣ����ڳ�ʼ������ɻ�����������
	* ��    ����pt������ʾ�Ļ��㣬hParent�����ھ����
	*   pOwner����ѡ�nLeftPos���Ԥ��ͼ����
	******/
	void InitWnd(POINT &pt, HWND hParent = NULL, MenuElementUI* pOwner = NULL, int nLeftPos = ITEM_DEFAULT_ICON_WIDTH);

	void UpdateWnd();//���ڸ���

	POINT GetPos();

	void SetPos();
	void AddMenuHeader(int height = HEADER_DEFAULT_HEIGHT, LPCTSTR text = L"", LPCTSTR bkimagename=L"TrayMenu.png");

public:
	CPaintManagerUI m_pm;
	HWND m_hParent;   //������
	CListUI *m_list;  //Ĭ������"inset=\"2,2,2,2\" bkcolor=\"0xFFE9FFFF\" bordersize=\"0\" itemtextpadding=\"30,0,0,0\" header=\"hidden\" itemshowhtml=\"true\""

private:
	MenuElementUI* m_pOwner;//����������ѡ��
	POINT m_basePoint;     //�������ϽǶ���λ��
	int m_itemHeight;       //ÿһ��ĸ߶�
	int m_itemWidth;  //���ڵĿ��
	int m_wndHeight;  //���ڵĸ߶�
	int m_leftWidth;  //���ͼ����ռ���
	menuLayout m_textAlign; //�ı����뷽ʽ Ĭ�������
};

class MenuElementUI : public CListContainerElementUI
{

public:
	MenuElementUI(UINT ID = 0);

	~MenuElementUI(){}

	LPCTSTR GetClass() const {return _T("MenuElementUI");}

	LPVOID  GetInterface(LPCTSTR pstrName);

	void DoEvent(TEventUI& event);

	void DoPaint(HDC hDC, const RECT& rcPaint);


	void SetText(LPCTSTR pstrText, DWORD textColor, CMultiMenuUI::menuLayout textalign =  CMultiMenuUI::TEXT_ALIGN_LEFT_DEFAULT);

	void SetIcon(int width, LPCTSTR iconName = L"");//16*16BMPͼƬ

	void SetExplandIcon(LPCTSTR iconName = ExplandIcon);//16*16BMPͼƬ

	void SetLine(bool isline, DWORD col, int width);

	bool AddCtrl(CControlUI* pControl);//����Զ���ؼ�

	CMultiMenuUI* CreateWnd(POINT &pt, HWND hParent, int nLeftPos );

	void DrawItemBk(HDC hDC, const RECT& rcItem);

public:
	UINT   uID;    //�˵�ID
	enum
	{
		ICON_LEFT_WIDTH = 4, //ͼ�����߾�
		EXPLAND_ICON_WIDTH = 20,
	};

private:
	CMultiMenuUI   *m_pWnd;   //��������
	CHorizontalLayoutUI *m_Layout; 
	CLabelUI *m_Text;   //��ʾ�ı�
	CLabelUI *m_Icon;   //ͼ��
	bool m_bDrawLine;   //�Ƿ���
	bool m_bextend;
	DWORD m_lineColor;          //�ָ�����ɫ
	int m_iconWidth;
};

class WndsVector
{
private:
	typedef std::vector<CMultiMenuUI*> ReceiversVector;
	static ReceiversVector receiverWnd;
public:
	static HWND rootHwnd;

	/*****
	* ��    �ܣ�������ָ��ѹ�봰�ڶ���

	******/
	static inline void AddWnd(CMultiMenuUI* ptr)
	{
		receiverWnd.push_back(ptr);
	}

	/*****
	* ��    �ܣ��������źŷ��͸������е�ÿһ������

	******/
	static void BroadCast(ContextMenuParam &param)
	{
		if (receiverWnd.empty())
			return;
		ReceiversVector::reverse_iterator it = receiverWnd.rbegin();
		for (; it != receiverWnd.rend(); it ++)
		{
			if ( *it != NULL )
				(*it)->ReceiveCloseMsg(param);
		}
	}

	/*****
	* ��    �ܣ����Ҵ��ڶ����а����þ���Ĵ�����ָ��

	******/
	static CMultiMenuUI* FindWndClass(HWND hwnd)
	{
		if (receiverWnd.empty())
			return NULL;
		ReceiversVector::iterator it = receiverWnd.begin();
		for (; it != receiverWnd.end(); it ++)
		{
			if (*it != NULL && (*it)->GetHWND() == hwnd)
				return *it;
		}
		return NULL;
	}
	static inline void RemoveAll()
	{
		receiverWnd.clear();
	}
}; 

#endif // ifndef __MULTI_MENU_H__