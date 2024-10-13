#include "pch.h"
#include "Ray.h"
#include "Export_Utility.h"
#include "Define.h"

CRay::CRay(LPDIRECT3DDEVICE9 pGraphicDev)
    :Engine::CGameObject(pGraphicDev)
{

}

CRay::~CRay()
{
}

HRESULT CRay::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CRay::Update_GameObject(const _float& fTimeDelta)
{
    return Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CRay::LateUpdate_GameObject(const _float& fTimeDelta)
{
    return Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CRay::Render_GameObject()
{
}

HRESULT CRay::Add_Component()
{
    return S_OK;
}

void CRay::Key_Input(const _float& fTimeDelta)
{
}

CRay* CRay::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    return nullptr;
}

void CRay::Free()
{
}

CRay::LPRAY   CRay::initRay(D3DXMATRIXA16* matProj, _D3DXMATRIXA16* matView)
{
    if(m_pRay == NULL)
    {
        m_pRay = new RAY; 
    }

    POINT ptCusror;
    GetCursorPos(&ptCusror);
    ScreenToClient(g_hWnd, &ptCusror);


    _float fX = 0.f;
    _float fY = 0.f;

    D3DVIEWPORT9 vp; 
    m_pGraphicDev->GetViewport(&vp);

    fX = ((( 2.0f * ptCusror.x) / vp.Width) - 1.0f);
    fY = (((-2.0f * ptCusror.y) / vp.Height) + 1.0f);

    fX = fX / matProj->_11;
    fY = fY / matProj->_22;

    m_pRay->Orign = D3DXVECTOR3(0.f, 0.f, 0.f); // ������ ���� 
    m_pRay->direction = D3DXVECTOR3(fX, fY, 1.0f);

    D3DXMATRIXA16 matViewInverse;
    D3DXMatrixInverse(&matViewInverse, NULL, matView);

    //������ ����
    transformRay(m_pRay, &matViewInverse);


    //���⼭ �ٽ� �ڵ��ۼ�
    return m_pRay;
}

BOOL CRay::destoryRay(VOID)
{
    return 0;
}

VOID CRay::transformRay(LPRAY pRay, D3DXMATRIXA16* pMatrix)
{
    if(pRay != NULL && pMatrix != NULL)
    {
        //������ ������ ��ȯ
        D3DXVec3TransformCoord(&(pRay->Orign), &(pRay->Orign), pMatrix);

        //������ ������ ��ȯ 
        D3DXVec3TransformNormal(&(pRay->direction), &(pRay->direction), pMatrix);

        //���� ���� ����ȭ 

        D3DXVec3Normalize(&(pRay->direction), &(pRay->direction));

    }
}


// ���� 2.
// ���콺 Ŭ���� ���� ���� �̵��� �����ض�
//D3DXIntersectTri();