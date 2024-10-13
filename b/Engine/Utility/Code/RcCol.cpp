#include "RcCol.h"

CRcCol::CRcCol()
{
}

CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
    :CVIBuffer(pGraphicDev)
{
}

CRcCol::CRcCol(const CRcCol& rhs)
    :CVIBuffer(rhs)
{
}

CRcCol::~CRcCol()
{
}

HRESULT CRcCol::Ready_Buffer()
{
#pragma region 버텍스 버퍼만 이용 했을때
    //m_dwTriCnt = 2; 
    //m_dwVtxCnt = 6;
    //m_dwVtxSize = sizeof(VTXCOL);
    //m_dwFVF = FVF_COL;
    //
    //
    //FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);
    //
    //VTXCOL* pVertex = nullptr; 
    //
    //m_pVB->Lock(0, 0, (void**)&pVertex, 0);
    //
    //pVertex[0].vPosition = { -1.f,1.f,0.f };
    //pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
    //
    //pVertex[1].vPosition = { 1.f, 1.f, 0.f };
    //pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
    //
    //pVertex[2].vPosition = { 1.f, -1.f, 0.f };
    //pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
    //
    //pVertex[3].vPosition = { -1.f, 1.f, 0.f };
    //pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
    //
    //pVertex[4].vPosition = { 1.f, -1.f, 0.f };
    //pVertex[4].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
    //
    //pVertex[5].vPosition = { -1.f, -1.f, 0.f };
    //pVertex[5].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
    //
#pragma region 버텍스 버퍼만 이용 했을때


    m_dwTriCnt = 2; 
    m_dwVtxCnt = 4; 
    m_dwVtxSize = sizeof(VTXCOL);
    m_dwFVF = FVF_COL;

    m_dwIdxSize = sizeof(INDEX32);
    m_IdxFmt = D3DFMT_INDEX32;

    FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

    VTXCOL* pVertex = NULL;     

    m_pVB->Lock(0, 0, (void**)&pVertex, 0); // 여기서 pVertex에 주소값이 안들어감 문제
    
    pVertex[0].vPosition = { -1.f, 1.f, 0.f };
    pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

    pVertex[1].vPosition = { 1.f, 1.f, 0.f };
    pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

    pVertex[2].vPosition = { 1.f, -1.f, 0.f };
    pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

    pVertex[3].vPosition = { -1.f, -1.f, 0.f };
    pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

    m_pVB->Unlock();

    INDEX32* pIndex = nullptr;

    m_pIB->Lock(0, 0, (void**)&pIndex, 0);

    //오른쪽 위 
    pIndex[0]._0 = 0;
    pIndex[0]._1 = 1;
    pIndex[0]._2 = 2; 

    //왼쪽 아래 
    pIndex[1]._0 = 0; 
    pIndex[1]._1 = 2;
    pIndex[1]._2 = 3; 

    m_pIB->Unlock();

    return S_OK;
}

void CRcCol::Render_Buffer()
{
    CVIBuffer::Render_Buffer();
}

CRcCol* CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CRcCol* pRcCol = new CRcCol(pGraphicDev);

    if(FAILED(pRcCol->Ready_Buffer()))
    {
        Safe_Release(pRcCol);
        MSG_BOX("RcCol Create Failed");
        return nullptr; 
    }

    return pRcCol;
}

CComponent* CRcCol::Clone()
{
    return new CRcCol(*this);
}

void CRcCol::Free()
{
    CVIBuffer::Free();
}
