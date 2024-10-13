#include "pch.h"
#include "Logo.h"
#include "Export_Utility.h"
#include "Export_System.h"
#include "Stage.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CScene(pGraphicDev)
	,m_pLoading(nullptr)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);
	
	m_pLoading = CLoading::Create(m_pGraphicDev, CLoading::LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Layer_Environment"), E_FAIL);


	//사운드 정지 및 동영상 재생 
	StopAll();

	PlayVideo(g_hWnd, L"../Bin/Resource/Video/CutScene_0_BabyOguWakeUp.wmv");	

	return S_OK;
}

_int CLogo::Update_Scene(const _float& fTimeDelta)
{
	_int  iExit = Engine::CScene::Update_Scene(fTimeDelta);
	
	
	if(true == m_pLoading->Get_Finish())
	{
		//if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		//{
			Engine::CScene* pStage = CStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pStage, -1);

			FAILED_CHECK_RETURN(Engine::Set_Scene(pStage), E_FAIL);

			return 0;
		//}
	}

	return iExit;
}

void CLogo::LateUpdate_Scene(const _float& fTimeDelta)
{
	Engine::CScene::LateUpdate_Scene(fTimeDelta);
}

void CLogo::Render_Scene()
{
	//Engine::CScene::Render_Scene();
	//DEBUG 용 출력 

	_vec2 position(100, 100);

	Engine::Render_Font(L"Font_Default", m_pLoading->Get_String(), &position, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CLogo::Ready_Prototype()
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Sprite_BabyOgu_Movement.png", TEX_NORMAL)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoTex", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player0.jpg", TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTex", Engine::CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_AnimationTex", Engine::CAnimationTex::Create(m_pGraphicDev)), E_FAIL);
	
	return S_OK;
}

HRESULT CLogo::Ready_Layer_Environment(const _tchar* pLayerTag)
{
	//Engine::CLayer* pLayer = CLayer::Create();
	//NULL_CHECK_RETURN(pLayer, E_FAIL);
	//
	//Engine::CGameObject* pGameObject = nullptr; 
	//
	//pGameObject = CBackGround::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);

	//m_mapLayer.insert({ pLayerTag,pLayer });
	return S_OK;
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo* pLogo = new CLogo(pGraphicDev);

	//if(FAILED(pLogo->Ready_Scene()))
	//{
	//	Safe_Release(pLogo);
	//	MSG_BOX("Logo Create Failed");
	//	return nullptr;
	//}

	return pLogo;
}

void CLogo::Free()
{
	Safe_Release(m_pLoading);

	Engine::CScene::Free();
}
