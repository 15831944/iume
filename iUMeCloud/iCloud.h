#ifndef __I_CLOUD_H__
#define __I_CLOUD_H__

typedef struct tag_WeatherInfo
{
	CDuiString strProvince;		// ʡ��
	CDuiString strCity;			// ����
	CDuiString strCounty;		// �س�
	CDuiString strAreaId;		// ���� id
	int nTemp;		// �¶�
	CDuiString strWD;	// ����
}WEATHER_INFO;

class CCloud : public WindowImplBase
{
public:
	CCloud();
	~CCloud();

public:
	virtual LPCTSTR GetWindowClassName() const;
	virtual void OnFinalMessage(HWND hWnd);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder(); 
	void Notify(TNotifyUI& msg);

public:


private:
	int m_nIndex;
	bool m_bAcSwitch;
	void SwitchDialog(int nIndex);

};

#endif // ifndef __I_CLOUD_H__