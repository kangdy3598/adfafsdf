#include "pch.h"
#include "Nue.h"

CNue::CNue(LPDIRECT3DDEVICE9 pGraphicDev)
    :CQuestNPC(pGraphicDev)
{
}

CNue::~CNue()
{
}

HRESULT CNue::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/Nue.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"PrisonNue", m_pNPCTex, _vec2(0.f, 0.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.15f, 3);
    m_pAnimatorCom->CreateAnimation(L"Nue", m_pNPCTex, _vec2(0.f, 128.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.15f, 3);

    m_tInfo.pName = L"���� ���";
    m_tInfo.pContent = L"Ȥ�� ���� ��ǥ�� ã�� �ּ�? ������ �������� �׸� ������ ���Ҽ�!! ��ġ���� �ļ����ֽÿ�. �׷��ٸ� ������ ���� ������ �˷��ְڼ�...";

    m_tQuestInfo.pQuestTitle = L"����ģ ������ ���?";
    m_tQuestInfo.pQuestContent = L"��ġ���� ��� �����ϸ� ���� ��簡 Ǯ������ ������ ��ġ�� �˷��شٰ� �Ѵ�..! � �ذ��غ���.";

    _vec3 vMarkPos = m_pTransformCom->m_vInfo[INFO_POS];
    vMarkPos.y += 33.f;
    m_pMarkTransformCom->m_vInfo[INFO_POS] = vMarkPos;
    m_pMarkTransformCom->m_vScale = { 13.f, 11.f, 20.f };

    return S_OK;

}

void CNue::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();
}

_int CNue::Update_GameObject(const _float& fTimeDelta)
{
    CQuestNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    //����Ʈ Ŭ���� ���� �ֱ�
    if (!m_bQuestClear && m_bQuestAccept)
    {
        if (m_pPlayer->Get_HonorScore() >= 100)
        {
            m_bQuestSucess = true;
        }
    }
    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;
}

void CNue::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CNue::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetTexture(0, m_pNPCTex);

    if (!m_bQuestClear)
        m_pAnimatorCom->Play(L"PrisonNue", true);
    else if (m_bQuestClear)
        m_pAnimatorCom->Play(L"Nue", true);

    m_pAnimatorCom->render();
    m_pColliderCom->Render_Buffer();

    if (!m_bQuestClear)
    {
        m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pMarkTransformCom->Get_WorldMatrix());

        if (!m_bQuestAccept)
        {
            m_pGraphicDev->SetTexture(0, m_pTex[EXCLAMATION]);
            m_pMarkAnimatorCom->Play(L"ExclamMarkAnim", true);
            m_pMarkAnimatorCom->render();
            return;
        }
        if (m_bQuestSucess)
        {
            m_pGraphicDev->SetTexture(0, m_pTex[YELLOWQUEST]);
            m_pMarkAnimatorCom->Play(L"YellowQuestAnim", true);
            m_pMarkAnimatorCom->render();
            return;
        }

        m_pGraphicDev->SetTexture(0, m_pTex[GRAYQUEST]);
        m_pMarkAnimatorCom->Play(L"GrayQuestAnim", true);
        m_pMarkAnimatorCom->render();

    }
}

void CNue::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetObjectKey() != L"Player")
        return;

    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;

        if (!m_bConversation)
        {
            if (!m_bQuestAccept)
            {
                m_bConversation = m_bConversation ? false : true;
                // ���⿡ new����Ʈ UI ����
                m_bQuestAccept = true; // ���� �� �ڿ� true�� �ٲ���.
                m_pQuestUI->Add_Quest(m_tQuestInfo);

                m_pQuestAcceptUI->CallQuestAcceptUI(true);
                m_pQuestAcceptUI->Set_Text(m_tQuestInfo);
                //m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ

                return;
            }
        }

        if (m_bConversation)
        {
            m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!

            m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
            m_pTextBox->CallTextBox(true); //��ȭâ ȣ��

            // ���ʿ��� �⺻ ����Ʈ ��ǳ�� ��������ؼ� �������� ������ �ִ��� false ���·� ����ϱ� ����
            //if (!m_bQuestClear && m_bQuestAccept)
            if (m_bQuestSucess)
            {
                m_bQuestClear = true;
                m_tInfo.pContent = L"�����༭ ����....��ǥ�� ��� �� ������ ���ڿ�... �ױ��� ���ϴ� ���� �� �ȶ��� ���Ҽ�....";
                m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
                m_pQuestUI->Get_QuestArray()->pop_back();
            }

        }
    }

    if (!m_bConversation)
    {
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
        // ��ȭ�ϱ�[S]
    }

}

void CNue::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false);
}

HRESULT CNue::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 20.f, 20.f, 20.f };
    m_pTransformCom->Set_Pos(1000.f, 20.f, 1080.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;

}

CNue* CNue::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CNue* pNPC = new CNue(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CNue Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CNue::Free()
{
}
