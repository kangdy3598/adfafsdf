#include "pch.h"
#include "CMouse.h"

_bool CMouse::g_bQuestClear(false);

CMouse::CMouse(LPDIRECT3DDEVICE9 pGraphicDev)
    :CQuestNPC(pGraphicDev)
{
}

CMouse::~CMouse()
{
}

HRESULT CMouse::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/Mouse.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"Mouse", m_pNPCTex, _vec2(0.f, 0.f), _vec2(256.f, 256.f), _vec2(256.f, 0.f), 0.12f, 1);

    m_tInfo.pName = L"�� �ڻ�";
    m_tInfo.pContent = L"�ڳ�! ���ص� �ʹ� ���غ��̴µ�? ��ħ ����ü�� �ʿ������� ���� ������ �ű���� ���� ���� ������ �ֳ�?";

    m_tQuestInfo.pQuestTitle = L"�� �ڻ��� �ű��";
    m_tQuestInfo.pQuestContent = L"���� ���غ��δٸ� �ű���� �������� �Ѵ�. ���� �� ������ ����ü���! ";

    _vec3 vMarkPos = m_pTransformCom->m_vInfo[INFO_POS];
    vMarkPos.y += 30.f;
    m_pMarkTransformCom->m_vInfo[INFO_POS] = vMarkPos;
    m_pMarkTransformCom->m_vScale = { 15.f, 17.f, 20.f };

    return S_OK;
}

void CMouse::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();
}

_int CMouse::Update_GameObject(const _float& fTimeDelta)
{
    CQuestNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    if (!g_bQuestClear && m_bQuestAccept)
    {
         m_bQuestSucess = true;
    }
    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;

}

void CMouse::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CMouse::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());


    m_pGraphicDev->SetTexture(0, m_pNPCTex);
    m_pAnimatorCom->Play(L"Mouse", true);
    m_pAnimatorCom->render();
    m_pColliderCom->Render_Buffer();

    if (!g_bQuestClear)
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

void CMouse::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetObjectKey() != L"Player")
        return;

    //m_bEnter = true;

    // [S]��ư ���.
    // [S]��ư Ŭ�� �� �ؽ�Ʈ�ڽ� ��� + �ؽ�Ʈ ���
    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;
        // ��ȭ���϶� S�� ������ ��ȭ����
        // ��ȭ���� �ƴҶ� S�� ������ ��ȭ����
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

            if (g_bQuestClear)
            {
                m_tInfo.pContent = L"���� �������� �ű���� �����?";
                m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
                return;
            }

            if (m_bQuestSucess)
            {
                Engine::Play_Sound(L"SFX_446_QuestClear.wav", SOUND_EFFECT, 1.f);

                g_bQuestClear = true;
                m_tInfo.pContent = L"���� ���Ѱ� ������ ����. ??Ű�� ���� ��ų�� ����غ���!";
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

void CMouse::OnCollisionEnter(CGameObject* _pOther)
{
}

void CMouse::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
}

HRESULT CMouse::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 10.f, 10.f, 15.f };
    m_pTransformCom->Set_Pos(1163.f, 25.f, 1350.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;

}

CMouse* CMouse::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CMouse* pNPC = new CMouse(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CMouse Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CMouse::Free()
{
    Engine::CGameObject::Free();
}
