#include "pch.h"
#include "Panda.h"

CPanda::CPanda(LPDIRECT3DDEVICE9 pGraphicDev)
    :CStoreNPC(pGraphicDev)
{
}

CPanda::~CPanda()
{
}

HRESULT CPanda::Ready_GameObject()
{
    CStoreNPC::Ready_GameObject();

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/Panda.png", &m_pTex);
    m_pAnimatorCom->CreateAnimation(L"Panda", m_pTex, _vec2(0.f, 0.f), _vec2(256.f, 256.f), _vec2(256.f, 0.f), 0.12f, 3);

    m_tInfo.pName = L"�Ǵ�";
    m_tInfo.pContent = L"�ػ����� ��� ����� ������ ���� �����̾����. �ػ������� ������ ���� ��긦 �˴ϴ�. ���� �ʾƿ�.";

    return S_OK;
}

void CPanda::LateReady_GameObject()
{
    CStoreNPC::LateReady_GameObject();
}

_int CPanda::Update_GameObject(const _float& fTimeDelta)
{
    CStoreNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    for (size_t i = 0; i < m_ItemArray.size(); i++)
    {

        m_ItemArray[i]->Update_GameObject(fTimeDelta);
    }

    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;
}

void CPanda::LateUpdate_GameObject(const _float& fTimeDelta)
{
    for (size_t i = 0; i < m_ItemArray.size(); i++)
    {
        m_ItemArray[i]->LateUpdate_GameObject(fTimeDelta);
    }
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);

}

void CPanda::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

    m_pGraphicDev->SetTexture(0, m_pTex);
    m_pAnimatorCom->Play(L"Panda", true);
    m_pAnimatorCom->render();
    m_pColliderCom->Render_Buffer();

    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pShopTransformCom->Get_WorldMatrix());
    m_pTextureCom->Set_Texture();
    m_pBufferCom->Render_Buffer();

}

void CPanda::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetObjectKey() != L"Player")
        return;

    if (Engine::GetKeyDown(DIK_D))
    {
        m_ItemArray.clear();
        m_bStoreOn = false;
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
    }
    else if (m_bStoreOn)
    {
        return;
    }

    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;
        // ��ȭ���϶� S�� ������ ��ȭ����
        // ��ȭ���� �ƴҶ� S�� ������ ��ȭ����
        if (!m_bConversation)
        {
            // ���⿡ UIbool true + ������ ����
            m_bStoreOn = true;

            CItem* pItem = dynamic_cast<CSmallHerb*>(CSmallHerb::Create(m_pGraphicDev));
            NULL_CHECK_RETURN(pItem);
            pItem->LateReady_GameObject();
            m_ItemArray.push_back(pItem);

            pItem = dynamic_cast<CMiddleHerb*>(CMiddleHerb::Create(m_pGraphicDev));
            NULL_CHECK_RETURN(pItem);
            pItem->LateReady_GameObject();
            m_ItemArray.push_back(pItem);

            pItem = dynamic_cast<CBigHerb*>(CBigHerb::Create(m_pGraphicDev));
            NULL_CHECK_RETURN(pItem);
            pItem->LateReady_GameObject();
            m_ItemArray.push_back(pItem);

            for (size_t i = 0; i < m_ItemArray.size(); i++)
            {
                m_pStoreUI->Add_Item(m_ItemArray[i]);
            }
            m_pStoreUI->CallStoreUI(true);

            return;
        }

        if (m_bConversation)
        {
            m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!

            m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
            m_pTextBox->CallTextBox(true); //��ȭâ ȣ��
        }

    }
    if (!m_bConversation)
    {
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
        // ��ȭ�ϱ�[S]
    }

}

void CPanda::OnCollisionEnter(CGameObject* _pOther)
{
}

void CPanda::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!
}

HRESULT CPanda::Add_Component()
{
    CComponent* pComponent = NULL;

    // ��Ʈ�ؽ���
    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CottonCandyCart"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

    pComponent = m_pShopTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_TransformHatShop", pComponent });
    m_pShopTransformCom->m_vScale = { 30.f, 30.f, 30.f };
    m_pShopTransformCom->Set_Pos(645.f, 30.f, 550.f);

    //-������� �ؽ���-

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 30.f, 30.f, 30.f };
    m_pTransformCom->Set_Pos(600.f, 20.f, 551.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

    return S_OK;

}

CPanda* CPanda::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CPanda* pNPC = new CPanda(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CPanda Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CPanda::Free()
{
    Engine::CGameObject::Free();
}
