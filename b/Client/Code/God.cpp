#include "pch.h"
#include "God.h"

CGod::CGod(LPDIRECT3DDEVICE9 pGraphicDev)
    :CQuestNPC(pGraphicDev), m_bCall(false)
{
}

CGod::~CGod()
{
}

HRESULT CGod::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/GodIn.png", &m_pComeTex); // ����
    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/GodIdle.png", &m_pNPCTex); // �⺻

    m_pAnimatorCom->CreateAnimation(L"GodIn1", m_pComeTex, _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 3);
    m_pAnimatorCom->CreateAnimation(L"GodIn2", m_pComeTex, _vec2(0.f, 512.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 3);
    m_pAnimatorCom->CreateAnimation(L"GodIn3", m_pComeTex, _vec2(0.f, 1024.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 3);

    m_pAnimatorCom->CreateAnimation(L"GodIdle1", m_pNPCTex, _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 3);
    m_pAnimatorCom->CreateAnimation(L"GodIdle2", m_pNPCTex, _vec2(0.f, 512.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 3);
    m_pAnimatorCom->CreateAnimation(L"GodIdle3", m_pNPCTex, _vec2(0.f, 1024.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.12f, 1);

    m_eState = GOD_IN1;

    m_tInfo.pName = L"��";
    m_tInfo.pContent = L"�̰� ���� ������̴�!!!!! ������ ���ư��� �ʹٸ� �ٽ� ���� �ɵ��� ��..!";

    m_tQuestInfo.pQuestTitle = L"�ٽ� ������...";
    m_tQuestInfo.pQuestContent = L"������ ���ư� �غ� �Ǿ��� �� �ٽ� ���� �ɶ�� �Ѵ�.";

    _vec3 vMarkPos = m_pTransformCom->m_vInfo[INFO_POS];
    vMarkPos.y += 50.f;
    m_pMarkTransformCom->m_vInfo[INFO_POS] = vMarkPos;
    m_pMarkTransformCom->m_vScale = { 15.f, 17.f, 20.f };

    return S_OK;
}

void CGod::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();
}

_int CGod::Update_GameObject(const _float& fTimeDelta)
{
    if (!m_bCall)
        return 0;

    CQuestNPC::Update_GameObject(fTimeDelta);

  

    if (!m_bQuestClear && m_bQuestAccept)
    {
        m_bQuestSucess = true;
    }
    Add_RenderGroup(RENDER_ALPHA, this);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    return iExit;
}

void CGod::LateUpdate_GameObject(const _float& fTimeDelta)
{
    if (!m_bCall)
        return;

    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CGod::Render_GameObject()
{
    if (!m_bCall)
        return;

    switch (m_eState)
    {
    case GOD_IN1:

        m_pGraphicDev->SetTexture(0, m_pComeTex);
        m_pAnimatorCom->Play(L"GodIn1", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IN2;
            m_pAnimatorCom->Play(L"GodIn2", false);
        }
        break;
    case GOD_IN2:
        m_pGraphicDev->SetTexture(0, m_pComeTex);
        m_pAnimatorCom->Play(L"GodIn2", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IN3;
            m_pAnimatorCom->Play(L"GodIn3", false);
        }
        break;
    case GOD_IN3:
        m_pGraphicDev->SetTexture(0, m_pComeTex);
        //SFX_830_Blink.wav
        m_pAnimatorCom->Play(L"GodIn3", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IDLE1;
            m_pGraphicDev->SetTexture(0, m_pNPCTex);
            m_pAnimatorCom->Play(L"GodIdle1", false);
        }
        break;

    case GOD_IDLE1:
        m_pGraphicDev->SetTexture(0, m_pNPCTex);
        m_pAnimatorCom->Play(L"GodIdle1", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IDLE2;
            m_pAnimatorCom->GetAnimation()->SetFrame(0);
            m_pAnimatorCom->Play(L"GodIdle2", false);
        }
        break;
    case GOD_IDLE2:
        m_pGraphicDev->SetTexture(0, m_pNPCTex);
        m_pAnimatorCom->Play(L"GodIdle2", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IDLE3;
            m_pAnimatorCom->GetAnimation()->SetFrame(0);
            m_pAnimatorCom->Play(L"GodIdle3", false);
        }
        break;
    case GOD_IDLE3:
        m_pGraphicDev->SetTexture(0, m_pNPCTex);
        m_pAnimatorCom->Play(L"GodIdle3", false);
        if (m_pAnimatorCom->GetAnimation()->IsFinish())
        {
            m_eState = GOD_IDLE1;
            m_pAnimatorCom->GetAnimation()->SetFrame(0);
            m_pAnimatorCom->Play(L"GodIdle1", false);
        }
        break;
    }

        m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
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

void CGod::OnCollision(CGameObject* _pOther)
{
    if (!m_bCall)
        return;

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
            if (m_bQuestSucess)
            {
                Engine::Play_Sound(L"SFX_446_QuestClear.wav", SOUND_EFFECT, 1.5f);

                m_bQuestClear = true;
                m_tInfo.pContent = L"������ ���� �غ� �Ȱų�...!! �׵��� ������...!! ����Ѵ�....!";
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

void CGod::OnCollisionEnter(CGameObject* _pOther)
{
}

void CGod::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false);
}

HRESULT CGod::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 100.f, 100.f, 40.f };
    m_pTransformCom->Set_Pos(1170.f, 80.f, 1050.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;

}

CGod* CGod::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CGod* pNPC = new CGod(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CGod Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CGod::Free()
{
    Engine::CGameObject::Free();
}
