#include "pch.h"
#include "QuestLion.h"

CQuestLion::CQuestLion(LPDIRECT3DDEVICE9 pGraphicDev)
	:CQuestNPC(pGraphicDev)
{
}

CQuestLion::~CQuestLion()
{
}

HRESULT CQuestLion::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/Lion.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"Lion", m_pNPCTex, _vec2(0.f, 0.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.15f, 3);

    m_tInfo.pName = L"���ù���";
    m_tInfo.pContent = L"<����� ��ǥ>�� ������� �ñ��ϴٰ�....? �������� ���� �ȴٸ� ���� �´� ���� ��ġ�� �˷�����.........";

    m_tQuestInfo.pQuestTitle = L"�������� �� �Ǳ�";
    m_tQuestInfo.pQuestContent = L"������ ���� ��� ���ڴ�..! �������� ���� �Ǹ� <���� �´� ���>�� <��ǥ�� ��ġ>�� �˷��شٰ� �Ѵ�. �������� ���� �Ǿ��.";

    _vec3 vMarkPos = m_pTransformCom->m_vInfo[INFO_POS];
    vMarkPos.y += 35.f;
    m_pMarkTransformCom->m_vInfo[INFO_POS] = vMarkPos;
    m_pMarkTransformCom->m_vScale = { 15.f, 17.f, 20.f };

    return S_OK;

}

void CQuestLion::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();
}

_int CQuestLion::Update_GameObject(const _float& fTimeDelta)
{
    CQuestNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

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

void CQuestLion::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CQuestLion::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetTexture(0, m_pNPCTex);
    m_pAnimatorCom->Play(L"Lion", true);
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

void CQuestLion::OnCollision(CGameObject* _pOther)
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
            if (m_bQuestClear)
            {
                m_tInfo.pContent = L"�ֱ�....<���� ��ǥ>�� ���� �� �ִ� <õ�� �����>�� ������ �ִٴ� �ҹ��� ������ϴٿ�..!!!";
                m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
                return;
            }

            if (m_bQuestSucess)
            {
                Engine::Play_Sound(L"SFX_446_QuestClear.wav", SOUND_EFFECT, 1.5f);

                m_bQuestClear = true;
                m_tInfo.pContent = L"���� �������� ž�� �Ǽ̱���...!!!! ���� �ֱ��� �Ǽ̽��ϴ�..!!!!!";
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

void CQuestLion::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false);
}

HRESULT CQuestLion::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 20.f, 20.f, 20.f };
    m_pTransformCom->Set_Pos(500.f, 20.f, 900.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;

}

CQuestLion* CQuestLion::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CQuestLion* pNPC = new CQuestLion(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CQuestLion Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CQuestLion::Free()
{
    Engine::CGameObject::Free();
}
