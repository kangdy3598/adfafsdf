#include "pch.h"
#include "TextBox.h"

CTextBox::CTextBox(LPDIRECT3DDEVICE9 pGraphicDev)
    :Engine::CGameObject(pGraphicDev)
    , m_bCall(false)
    , m_iCurStrIndex(1)
{
    ZeroMemory(&m_tCopyInfo, 0, sizeof(m_tCopyInfo));
}

CTextBox::~CTextBox()
{
}

HRESULT CTextBox::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    return S_OK;
}

_int CTextBox::Update_GameObject(const _float& fTimeDelta)
{
    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    if (m_bCall)
    {
        Engine::Add_RenderGroup(RENDER_UI, this);
        Key_Input(fTimeDelta);
    }

    return iExit;
}

void CTextBox::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CTextBox::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pTextureCom->Set_Texture();
    m_pBufferCom->Render_Buffer();



    if (m_bCall)
        Render_Text();
}

void CTextBox::Key_Input(const _float& fTimeDelta)
{
    if (m_bCall)
    {
        if (Engine::GetKeyDown(DIK_S))
        {
            //��ȭ���� ����
            Engine::Play_Sound(L"SFX_70_UISlotMediumMove.wav", SOUND_EFFECT, 0.3);
            ZeroMemory(&m_tCopyInfo, 0, sizeof(m_tCopyInfo));
            m_bCall = false; // ��ȭâ �θ�������
            m_iCurStrIndex = 1; // �ʱ�ȭ
        }
    }
}

void CTextBox::Render_Text()
{
    // �̸� �ؽ�Ʈ ������ >> NPC �̸� 
    _vec2 vNPCNamePos(221, 494);
    _vec2 vNameRCSize(266, 74);

    Engine::Render_Font(L"Font_Ogu24", m_tCopyInfo.pName, &vNPCNamePos, D3DXCOLOR(1.f, 1.f, 1.f, 1.f), TEXT_CENTER, vNameRCSize);


    _int iTextLength = wcslen(m_tCopyInfo.pContent);  // ��ü ���ڿ� ����

    if (m_iCurStrIndex > iTextLength)
        m_iCurStrIndex = iTextLength;

    wstring strPartialText(m_tCopyInfo.pContent, m_iCurStrIndex);

    _vec2 vNPCConverPos = { 405, 570 };  // ���ڴ��� ��Ʈ LT!!!
    _vec2 vConverRCSize(500, 100); // RB^^����

    Engine::Render_Font(L"Font_Ogu24", strPartialText.c_str(), &vNPCConverPos, D3DXCOLOR(0.999f, 0.98f, 0.9f, 1.f), TEXT_CENTER, vConverRCSize);

    m_iCurStrIndex += 1;

}


HRESULT CTextBox::Add_Component()
{
    CComponent* pComponent = NULL;

    // ��Ʈ�ؽ���
    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

    //TextBox
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_TextBox"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vInfo[INFO_POS] = { 0.f, -245.f, 0.9f };
    m_pTransformCom->m_vScale = { 450.f, 115.f, 1.f };

    return S_OK;
}

CTextBox* CTextBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CTextBox* pUI = new CTextBox(pGraphicDev);

    if (FAILED(pUI->Ready_GameObject()))
    {
        Safe_Release(pUI);
        MSG_BOX("TextBox Create Failed");
        return nullptr;
    }
    return pUI;
}

void CTextBox::Free()
{
    Engine::CGameObject::Free();
}
