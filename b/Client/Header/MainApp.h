#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include "Define.h"
#include "Export_System.h"
#include "Export_Utility.h"
#include "Logo.h"
#include "StartScene.h"





class CMainApp : public CBase
{
private:
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT Ready_MainApp();
	int     Update_MainApp(const float& fTimeDelta);
	void	LateUpdate_MainApp(const float& fTimeDelta);
	void	Render_MainApp();

protected:

private:
	HRESULT  Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement);
	HRESULT  SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);

private:
	CGraphicDev*			m_pDeviceClass;	// �̱��� �ּ� ����� ������
	CManagement*			m_pManagementClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;	// ���� �׸��� ��ü �ּ�

public: // ��ü ���� �Լ�
	static CMainApp* Create();

private:
	virtual void	Free();

};

