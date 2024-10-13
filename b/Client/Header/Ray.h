#pragma once
#include "GameObject.h"

class CRay : public CGameObject
{
	explicit CRay(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRay();

public:
	virtual			HRESULT			Ready_GameObject();
	virtual			_int			Update_GameObject(const _float& fTimeDelta);
	virtual			void			LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void			Render_GameObject();

private:
	HRESULT			Add_Component();
	void			Key_Input(const _float& fTimeDelta);

public:
	static CRay* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();



//�߰� �ڵ�
public:
	// ���� ����ü 
	typedef struct tagRay
	{
		D3DXVECTOR3 Orign;  // ������ ����
		D3DXVECTOR3 direction; // ������ ���⺤��
	}RAY,*LPRAY;

private:
	LPRAY m_pRay; // ���� ����

public:
	LPRAY initRay(D3DXMATRIXA16* matProj, _D3DXMATRIXA16* matView);

	BOOL  destoryRay(VOID);

public:
	LPRAY  getRay(VOID) { return m_pRay; }


private:
	VOID   transformRay(LPRAY pRay, D3DXMATRIXA16* pMatrix);

};

