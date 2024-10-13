#include "pch.h"
#include "MCRabbit.h"
#include "FightUI.h"
CMCRabbit::CMCRabbit(LPDIRECT3DDEVICE9 pGraphicDev)
    :CQuestNPC(pGraphicDev), m_pRhino(nullptr)
{
}

CMCRabbit::~CMCRabbit()
{
}

HRESULT CMCRabbit::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_eMonster = NUM_END;

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/RabbitNPC.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"NPCRabbit", m_pNPCTex, _vec2(0.f, 0.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.15f, 1);

    m_tInfo.pName = L"�߰踦 ���� �䳢";
    m_tInfo.pContent = L"���� ���� ��븦 �����Ͻ��� �ʾұ���!!!                  ���� �Ŀ� �ٽ� ���ɾ��ּ���!!!!!!!!!!!";

    return S_OK;
}

void CMCRabbit::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();

    m_pRhino = dynamic_cast<CRhino*>(Engine::Get_GameObject(L"Layer_GameLogic", L"Rhino"));
    NULL_CHECK_RETURN(m_pRhino);

}

_int CMCRabbit::Update_GameObject(const _float& fTimeDelta)
{
    CQuestNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;
}

void CMCRabbit::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CMCRabbit::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetTexture(0, m_pNPCTex);
    m_pAnimatorCom->Play(L"NPCRabbit", true);
    m_pAnimatorCom->render();
    m_pColliderCom->Render_Buffer();
}

void CMCRabbit::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetObjectKey() != L"Player")
        return;

    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;

        if (m_bConversation)
        {
            m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!

            if (m_eMonster != NUM_END)
                m_tInfo.pContent = L"������ ���� ������ �����մϴ�!!!!!!!!!!!!!!!!        ������ �����Ѵ�!!!!";

            m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
            m_pTextBox->CallTextBox(true); //��ȭâ ȣ��
        }

        if (!m_bConversation)
        {
            if (m_eMonster != NUM_END)
            {
                Create_Monster();
                CFightUI* pFightUI = dynamic_cast<CFightUI*>(Engine::Get_GameObject(L"Layer_UI", L"Fight_UI"));
                NULL_CHECK_RETURN(pFightUI);
                pFightUI->CallFight();
            }
        }

    }

    if (!m_bConversation)
    {
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
        // ��ȭ�ϱ�[S]
    }

}

void CMCRabbit::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false);
}

HRESULT CMCRabbit::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 20.f, 20.f, 20.f };
    m_pTransformCom->Set_Pos(500.f, 20.f, 800.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;

}

void CMCRabbit::Create_Monster()
{
    _vec3 vPlayerPos = { 500.f, 30.f, 300.f };

    switch (m_eMonster)
    {
    case RHINO:
        m_pRhino->Set_Create();
        m_pRhino->LateReady_GameObject();

        m_pPlayer->SetPlayerPos(vPlayerPos);
    default:
        m_tInfo.pContent = L"���� ���� ��븦 ���� �ʾұ���?!?!?!!?!??! ���� �� �ٽ� �� �ɾ��ּ���!!!!!";
        break;
    }
}

CMCRabbit* CMCRabbit::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CMCRabbit* pNPC = new CMCRabbit(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("MCRabbit Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CMCRabbit::Free()
{
    Engine::CGameObject::Free();
}
