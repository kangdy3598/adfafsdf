#include "pch.h"
#include "BardCat.h"

CBardCat::CBardCat(LPDIRECT3DDEVICE9 pGraphicDev)
    :CQuestNPC(pGraphicDev)
{
}

CBardCat::~CBardCat()
{
}

HRESULT CBardCat::Ready_GameObject()
{
    CQuestNPC::Ready_GameObject();

    SetObjectType(OBJ_TYPE::TALK_ABLE);

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/BardCat.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"BardCatIdle", m_pNPCTex, _vec2(0.f, 0.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.12f, 5);
    m_pAnimatorCom->CreateAnimation(L"BardCatSong", m_pNPCTex, _vec2(0.f, 128.f), _vec2(128.f, 128.f), _vec2(128.f, 0.f), 0.12f, 7);

    m_tInfo.pName = L"��������";
    m_tInfo.pContent = L"�� ���� ���� �����ٴ�..! ����� �����̽ñ���!!!!!!! ������ ���� ���� �뷡�� �־��! ���� ����� ������ ����ּ���!!";

    m_eState = CAT_IDLE;

    return S_OK;

}

void CBardCat::LateReady_GameObject()
{
    CQuestNPC::LateReady_GameObject();
}

_int CBardCat::Update_GameObject(const _float& fTimeDelta)
{
    CQuestNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;

}

void CBardCat::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CBardCat::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

    switch (m_eState)
    {
    case CAT_IDLE:
        m_pAnimatorCom->Play(L"BardCatIdle", true);
        break;

    case CAT_SONG:
        m_pAnimatorCom->Play(L"BardCatSong", true);
        break;
    }
    m_pGraphicDev->SetTexture(0, m_pNPCTex);
    m_pAnimatorCom->render();
    m_pColliderCom->Render_Buffer();

}

void CBardCat::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetObjectKey() != L"Player")
        return;

    // [S]��ư ���.
    // [S]��ư Ŭ�� �� �ؽ�Ʈ�ڽ� ��� + �ؽ�Ʈ ���
    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;
        // ��ȭ���϶� S�� ������ ��ȭ����
        // ��ȭ���� �ƴҶ� S�� ������ ��ȭ����

        if (m_bConversation)
        {
            m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!

            m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
            m_pTextBox->CallTextBox(true); //��ȭâ ȣ��
            //if (m_eState == CAT_SONG)
            //{

            //}
        }
        if (!m_bConversation)
        {
            m_eState = CAT_SONG;
            Engine::StopSound(SOUND_BGM);
            Engine::PlayBGM(L"BGM_79_BardSongNoVocal.wav", 0.8f);
            return;
        }
    }

    if (!m_bConversation)
    {
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
        // ��ȭ�ϱ�[S]
    }
}

void CBardCat::OnCollisionEnter(CGameObject* _pOther)
{
}

void CBardCat::OnCollisionExit(CGameObject* _pOther)
{
    if (m_eState == CAT_SONG)
    {
        m_eState = CAT_IDLE;
        Engine::StopSound(SOUND_BGM);
        Engine::PlayBGM(L"BGM_3_JungleAreaField1.wav", 0.8f);
    }
    m_pInterButton->CallButton(false);
}

HRESULT CBardCat::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 25.f, 25.f, 30.f };
    m_pTransformCom->Set_Pos(880.f, 30.f, 1880.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;
}

CBardCat* CBardCat::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CBardCat* pNPC = new CBardCat(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("CBardCat Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CBardCat::Free()
{
    Engine::CGameObject::Free();
}
