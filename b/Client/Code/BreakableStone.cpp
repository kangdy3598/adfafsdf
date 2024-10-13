#include "pch.h"
#include "BreakableStone.h"
#include "Stone.h"
#include "Export_Utility.h"

CBreakableStone::CBreakableStone(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev), m_iImageID(0), m_fTime(0), m_iTargetID(0)
{
}

CBreakableStone::~CBreakableStone()
{
}

HRESULT CBreakableStone::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	SetObjectType(NOTPASS_ABLE);

	m_vecTexture.resize(8);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_00.png", &m_vecTexture[0]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_01.png", &m_vecTexture[1]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_02.png", &m_vecTexture[2]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_03.png", &m_vecTexture[3]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_04.png", &m_vecTexture[4]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_05.png", &m_vecTexture[5]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_06.png", &m_vecTexture[6]);
	LoadTextureFromFile(m_pGraphicDev, "../Bin/Resource/Texture/puzzle/BreakableStone_Anim/Sprite_StoneBreakable_Destroy_07.png", &m_vecTexture[7]);


	m_pTransformCom->m_vScale = { 16.f, 16.f, 16.f };
	return S_OK;
}

_int CBreakableStone::Update_GameObject(const _float& fTimeDelta)
{
	if (!m_bIsActive)
		return 0;

	Add_RenderGroup(RENDER_ALPHA, this);


	if (m_iImageID != m_iTargetID) {
		m_fTime += fTimeDelta;

		if (m_fTime >= 0.02f) {
			if (m_iTargetID > m_iImageID)
				m_iImageID++;

			if (m_iImageID == m_iTargetID)
				m_bIsActive = false;

			m_fTime = 0;
		}
	}

	_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CBreakableStone::LateUpdate_GameObject(const _float& fTimeDelta)
{
	if (!m_bIsActive)
		return;

	Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CBreakableStone::Render_GameObject()
{
	if (!m_bIsActive)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetTexture(0, m_vecTexture[m_iImageID]);
	m_pBufferCom->Render_Buffer();
	m_pBoundBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CBreakableStone::OnCollisionEnter(CGameObject* _pOther)
{
	if (_pOther->Get_Tag() == TAG_STONE) {
		if (static_cast<CStone*>(_pOther)->Is_Launched() == false)
			return;

		static_cast<CStone*>(_pOther)->Break();
		m_iTargetID = 7;
		Play_Sound(L"SFX_41_Catapult_StoneHit.wav", SOUND_EFFECT, 1.f);
		Play_Sound(L"SFX_681_StoneBreakableDestroy.wav", SOUND_SURROUNDING, 1.f);
	}
}

HRESULT CBreakableStone::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pBoundBox = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pBoundBox->SetGameObjectPtr(this);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	return S_OK;
}

CBreakableStone* CBreakableStone::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBreakableStone* pCrystal = new CBreakableStone(pGraphicDev);

	if (FAILED(pCrystal->Ready_GameObject()))
	{
		Safe_Release(pCrystal);
		MSG_BOX("pPipeBoard Create Failed");
		return nullptr;
	}
	CManagement::GetInstance()->GetCurScenePtr()->Add_ObjectGroup(GROUP_TYPE::OBJECT, pCrystal);
	CManagement::GetInstance()->GetCurScenePtr()->Add_ObjectGroup(GROUP_TYPE::PUZZLE, pCrystal);
	return pCrystal;
}

void CBreakableStone::Free()
{
	Engine::CGameObject::Free();
}