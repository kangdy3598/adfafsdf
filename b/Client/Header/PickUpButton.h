#pragma once
#include "GameObject.h"
#include "Export_System.h"
#include "Export_Utility.h"

class CPickUpButton : public Engine::CGameObject
{
private:
	explicit CPickUpButton(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPickUpButton();

public:
	virtual   HRESULT   Ready_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void	    LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

	void	CallButton(_bool _bCall) { m_bCall = _bCall; }
private:
	HRESULT    Add_Component();

private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;

	_bool m_bCall;

public:
	static CPickUpButton* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();

};

