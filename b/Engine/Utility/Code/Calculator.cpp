#include "Calculator.h"
#include "Export_Utility.h"

CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev)
    :CComponent(pGraphicDev)
{
}

CCalculator::~CCalculator()
{
}

HRESULT CCalculator::Ready_Calculator()
{
    return S_OK;
}

_float CCalculator::Compute_HeightOnTerrain(const _vec3* pPos, const _vec3* pTerrainVtxPos, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
    // Ư�� ���� ��ġ (x , y, z )
    // ����� ���� ���� ���� ( a,b,c,d )

    _ulong dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);

    _float fRatioX = (pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
    _float fRatioZ = (pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;

    D3DXPLANE Plane;


    // ����
    if (fRatioX > fRatioZ)
    {
        D3DXPlaneFromPoints(&Plane,
            &pTerrainVtxPos[dwIndex + dwCntX],
            &pTerrainVtxPos[dwIndex + dwCntX + 1],
            &pTerrainVtxPos[dwIndex + 1]);
    }

    else
    {
        D3DXPlaneFromPoints(&Plane,
            &pTerrainVtxPos[dwIndex + dwCntX],
            &pTerrainVtxPos[dwIndex + 1],
            &pTerrainVtxPos[dwIndex]);
    }
 
    // ax + by + cz + d
    // 
    // -by = ax + cz + d 

    //y = (-ax - cz - d) / b

    return  (-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b; 
}

_vec3 CCalculator::Picking_OnTerrian(HWND hWnd, CTerrainTex* pTerrainBufferCom, CTransform* pTerrainTransCom)
{
    POINT ptMouse{};
    GetCursorPos(&ptMouse);
    ScreenToClient(hWnd, &ptMouse);

    _vec3 vMousePos;

    D3DVIEWPORT9 ViewPort;
    ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
    m_pGraphicDev->GetViewport(&ViewPort);

    // �� ��Ʈ -> ����
    vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f; // ������� (nds ��ǥ���� -1,1�� ȭ�鿡���� 0,0�� �ش�  ���� �־��� (0 / 800 *0.5) -1.f = -1.f �̷���
    vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f; // ���� ��������. 
    vMousePos.z = 0.f; // �׳� ���Ƿ� ��Ƶа� ����Ҷ� �ʿ��ϹǷ� 


    // ���� -> �� �����̽�

    _matrix matProj;
    m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
    D3DXMatrixInverse(&matProj, NULL, &matProj);
    D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

    _vec3  vRayPos, vRayDir;

    vRayPos = { 0.f, 0.f, 0.f };
    vRayDir = vMousePos - vRayPos;


    // �� �����̽� -> ���� 

    _matrix matView;
    m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
    D3DXMatrixInverse(&matView, NULL, &matView);
    D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView); //��ġ���� �̵�
    D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);


    // ���� ������ �ڵ�� 
   
    // ���� ��ǥ���� �ҰŴϱ� �ͷ����� ������ǥ �� �������� �����;���
    const _vec3* pTerrainTexPos = pTerrainBufferCom->Get_VtxPos();
    _vec3* pWorldTerrainTexPos = new _vec3[VTXCNTX * VTXCNTZ];  
    
    
    
    // �ͷ����� ���� ��Ʈ������ �����;��ϴµ�
    _matrix matWorld;
    //Engine::CTransform* pTerrainTransform = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Terrain", L"Com_Transform"));
    pTerrainTransCom->Get_WorldMatrix(&matWorld);   
    
    
    for(int i =0 ; i<VTXCNTX * VTXCNTZ ; i++)
    {
        D3DXVec3TransformCoord(&pWorldTerrainTexPos[i], &pTerrainTexPos[i], &matWorld);
    }
    
    //����� ���Ǵ��� ( ���� �׵������ ��������̹Ƿ� �״���� ���� ���;���)
    // if(*pWorldTerrainTexPos[1] == *pTerrainTexPos[1])
    //{
    //    int a = 4; 
    //}
    
    _ulong dwVtxId[3]{};
    _float fU, fV, fDist;
   
    for(_ulong i=0; i< VTXCNTZ -1; ++i)
    {
        for (_ulong j = 0; j < VTXCNTX - 1; ++j)
        {
            _ulong	dwIndex = i * VTXCNTX + j;
    
            // ������ ��
            dwVtxId[0] = dwIndex + VTXCNTX;
            dwVtxId[1] = dwIndex + VTXCNTX + 1;
            dwVtxId[2] = dwIndex + 1;
    
            if (D3DXIntersectTri(&pWorldTerrainTexPos[dwVtxId[1]],
                &pWorldTerrainTexPos[dwVtxId[2]],
                &pWorldTerrainTexPos[dwVtxId[0]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                return _vec3(pWorldTerrainTexPos[dwVtxId[1]].x + fU * (pWorldTerrainTexPos[dwVtxId[2]].x - pWorldTerrainTexPos[dwVtxId[1]].x),
                    0.f,
                    pWorldTerrainTexPos[dwVtxId[1]].z + fV * (pWorldTerrainTexPos[dwVtxId[0]].z - pWorldTerrainTexPos[dwVtxId[1]].z));
            }
    
            // ���� �Ʒ�
            dwVtxId[0] = dwIndex + VTXCNTX;
            dwVtxId[1] = dwIndex + 1;
            dwVtxId[2] = dwIndex;
    
            if (D3DXIntersectTri(&pWorldTerrainTexPos[dwVtxId[2]],
                &pWorldTerrainTexPos[dwVtxId[0]],
                &pWorldTerrainTexPos[dwVtxId[1]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                // V1 + U(V2 - V1) + V(V3 - V1)
    
                return _vec3(pWorldTerrainTexPos[dwVtxId[2]].x + fU * (pWorldTerrainTexPos[dwVtxId[0]].x - pWorldTerrainTexPos[dwVtxId[2]].x),
                    0.f,
                    pWorldTerrainTexPos[dwVtxId[2]].z + fV * (pWorldTerrainTexPos[dwVtxId[1]].z - pWorldTerrainTexPos[dwVtxId[2]].z));
            }
        }
    }
    
    return _vec3(0.f, 0.f, 0.f);
}

CCalculator* CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CCalculator* pCalculator = new CCalculator(pGraphicDev);

    if(FAILED(pCalculator->Ready_Calculator()))
    {
        Safe_Release(pCalculator);
        return nullptr; 
    }

    return pCalculator;
}

CCalculator* CCalculator::Clone()
{
    return new CCalculator(*this);
}

void CCalculator::Free()
{
    CComponent::Free();
}
