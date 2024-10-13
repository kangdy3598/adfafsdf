#include "pch.h"
#include "../Header/MainApp.h"
#include "ImGuiManger.h"



CMainApp::CMainApp()
{

}

CMainApp::~CMainApp()
{

}

HRESULT CMainApp::Ready_MainApp()
{
	//���Ⱑ init �Լ� ������
	// 
	// 
	// ��ġ �ʱ�ȭ �� �ּҰ� ������ -> ���۷��� ī��Ʈ ������ 
	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);


	// ���⼭ ���� �� �ŵ��� �� �ױ׸� �����ְ� �ſ� ���õ� ���̾ �׸��� ���̾ ���� ��ü�� ���� ���� ����
	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);


	return S_OK;
}

int CMainApp::Update_MainApp(const float& fTimeDelta)
{

	Engine::Update_InputDev();
	
	m_pManagementClass->Update_Scene(fTimeDelta);



	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
	//_ulong	Mousemove(0);
	//
	//if (Mousemove = Engine::Get_DIMouseMove(DIMS_Z))
	//{
	//	int	a = 0;
	//}

	

	m_pManagementClass->LateUpdate_Scene(fTimeDelta);
}

void CMainApp::Render_MainApp()
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 0.f, 1.f));


	// imgui ui �ɼǰ��� ���� ����
	//if(CImGuiManger::GetInstance()->GetTerrainOnOFF())
	//{
		m_pManagementClass->Render_Scene(m_pGraphicDev);
	//}
	
	//if(CImGuiManger::GetInstance()->GetWireFrameOnOFF())
	//{
		//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//}

	//if(!CImGuiManger::GetInstance()->GetWireFrameOnOFF())
	//{
		//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}


	// ImGui ������
	//CImGuiManger::GetInstance()->Render();
	
	

	Engine::Render_End();	
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagement)
{
	Engine::CScene* pScene = nullptr; 
	//�� �� �ŵ� ���� �ϴ� init �κ� 
	pScene = CStartScene::Create(pGraphicDev);	
	NULL_CHECK_RETURN(pScene, E_FAIL);	

	// �� �Ŵ��� �����ε� 
	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagement), E_FAIL);	
	(*ppManagement)->AddRef(); //�Ŵ��� �̱��� �ּ� ���������� ��������.	

	//Engine::Set_Scene(pScene) // �̷��� �ص��� ���� 2�� ���� 
	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL); // �̰� ���� �� �����ִ°� �� ���� �����ְ�	

	
	
	// ================================================================================
	//pScene = CLogo::Create(pGraphicDev);
	//NULL_CHECK_RETURN(pScene, E_FAIL);

	//// �� �Ŵ��� �����ε� 
	//FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagement), E_FAIL);
	//(*ppManagement)->AddRef(); //�Ŵ��� �̱��� �ּ� ���������� ��������.

	////Engine::Set_Scene(pScene) // �̷��� �ص��� ���� 2�� ���� 
	//FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL); // �̰� ���� �� �����ִ°� �� ���� �����ְ�

	return S_OK;
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//  Default�� true ������ �Ǿ� �ִ� �͵� 
	(*ppGraphicDev)->SetRenderState(D3DRS_ZENABLE, TRUE);		// Z���ۿ� ���� ���� ����� �ϵ� ������ �������� ���� ���θ� ���� �ɼ�
	(*ppGraphicDev)->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z���ۿ� ���� ���� ����� �� �� �� ����

	// ��Ʈ �߰� 

	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Default", L"�ü�", 20, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Myungjo", L"����", 20, 20, FW_NORMAL), E_FAIL);
	
	//0922
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_OguBold14", L"ī��24 �����", 14, 14, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_OguBold22", L"ī��24 �����", 22, 22, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_OguBold24", L"ī��24 �����", 24, 24, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_OguBold36", L"ī��24 �����", 36, 36, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_OguBold48", L"ī��24 �����", 48, 48, FW_NORMAL), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Ogu10", L"ī��24 ����� ����", 10, 12, FW_THIN), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Ogu14", L"ī��24 ����� ����", 14, 18, FW_LIGHT), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Ogu22", L"ī��24 ����� ����", 18, 24, FW_LIGHT), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Ogu24", L"ī��24 ����� ����", 20, 26, FW_THIN), E_FAIL);



	// dinput �߰�
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);		


	(*ppGraphicDev)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	(*ppGraphicDev)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if(FAILED(pMainApp->Ready_MainApp()))
	{
		Safe_Release(pMainApp);
		return nullptr;
	}


	return pMainApp;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pManagementClass);


	//m_pDeviceClass->DestroyInstance();
	Engine::Release_Utility();
	Engine::Release_System();
}



// �ΰ� �۾��ϱ� �ͼ� 