#include "pch.h"
#include "PlayerDash.h"
#include "Player.h"

PlayerDash* PlayerDash::m_instance = nullptr;

void PlayerDash::Enter()
{
    if (!m_pStateController)
        SetComponent();

    (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerState(PLAYERSTATE::PLY_DASH);

    m_fMoveSpeed = 100.f;
    (dynamic_cast<CPlayer*>(m_CGameObject))->SetMoveSpeed(m_fMoveSpeed);
    m_fMoveDuration = 0.f;
    m_fDuration = 0.4f;
    m_bZoomOutTrigger = false;
}

void PlayerDash::Update(const _float& fTimeDelta)
{
    m_fDuration += fTimeDelta;
    if (m_fDuration > 0.7f)
    {
        m_fDuration = 0.f;
        Engine::Play_Sound(L"SFX_7_Run_Ground_1.wav", SOUND_EFFECT, 0.3);
    }

    if (!Engine::GetKeyPress(CONTROLKEY::PLY_UPKEY) &&
        !Engine::GetKeyPress(CONTROLKEY::PLY_DOWNKEY) &&
        !Engine::GetKeyPress(CONTROLKEY::PLY_LEFTKEY) &&
        !Engine::GetKeyPress(CONTROLKEY::PLY_RIGHTKEY))
    {
        m_pStateController->ChangeState(PlayerIdle::GetInstance(), m_CGameObject);
    }

    else if (Engine::GetKeyUp(CONTROLKEY::PLY_DASHKEY))
    {
        m_pStateController->ChangeState(PlayerMove::GetInstance(), m_CGameObject);
    }

    if (Engine::GetKeyPress(CONTROLKEY::PLY_SMASHKEY))
    {
        m_pStateController->ChangeState(PlayerSmash::GetInstance(), m_CGameObject);
    }

    Key_Input(fTimeDelta);
    //CameraZoomOut(fTimeDelta);

}


void PlayerDash::Exit()
{
    m_fMoveDuration = 0.f;
    m_bZoomOutTrigger = false;
}

void PlayerDash::Key_Input(const _float& fTimeDelta)
{
    _vec3  vLook;
    _vec3  vRight;
    m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
    m_pTransformCom->Get_Info(INFO_RIGHT, &vRight);

    _vec3 colPos = (dynamic_cast<CPlayer*>(m_CGameObject))->GetColliderPos();
    _vec3 colPlayerPos = (dynamic_cast<CPlayer*>(m_CGameObject))->GetColPlayerPos();
    _vec3 colDir = colPos - colPlayerPos; // �÷��̾�� �浹ü�� ���� ����
    D3DXVec3Normalize(&colDir, &colDir);  // �浹 ���� �� �浹ü ����

    if (Engine::GetKeyPress(CONTROLKEY::PLY_UPKEY))
    {
        if ((dynamic_cast<CPlayer*>(m_CGameObject))->GetPassAble() ||
            (abs(colDir.x) > 0.71 || colDir.z < 0.69))
        {
            m_pTransformCom->Move_Pos(D3DXVec3Normalize(
                &vLook, &vLook), fTimeDelta, m_fMoveSpeed);
        }
    }

    if (Engine::GetKeyPress(CONTROLKEY::PLY_DOWNKEY))
    {
        if ((dynamic_cast<CPlayer*>(m_CGameObject))->GetPassAble() ||
            (abs(colDir.x) > 0.71 || colDir.z > -0.69))
        {
            m_pTransformCom->Move_Pos(D3DXVec3Normalize(
                &vLook, &vLook), fTimeDelta, -m_fMoveSpeed);
        }
    }

    if (Engine::GetKeyPress(CONTROLKEY::PLY_LEFTKEY))
    {
        if ((dynamic_cast<CPlayer*>(m_CGameObject))->GetPassAble() ||
            (abs(colDir.z) > 0.71 || colDir.x > -0.69))
        {
            m_pTransformCom->Move_Pos(D3DXVec3Normalize(
                &vRight, &vRight), fTimeDelta, -m_fMoveSpeed);
        }

    }

    if (Engine::GetKeyPress(CONTROLKEY::PLY_RIGHTKEY))
    {
        if ((dynamic_cast<CPlayer*>(m_CGameObject))->GetPassAble() ||
            (abs(colDir.z) > 0.71 || colDir.x < 0.69))
        {
            m_pTransformCom->Move_Pos(D3DXVec3Normalize(
                &vRight, &vRight), fTimeDelta, m_fMoveSpeed);
        }
    }
}

void PlayerDash::CameraZoomOut(const _float& fTimeDelta)
{
    // �뽬 �������� 3�ʰ� �����ٸ� ī�޶� �ܾƿ��� �����մϴ�.
    if (m_fMoveDuration > 3.f && !m_bZoomOutTrigger)
    {
        // 2�� ���� ������� 60%��ŭ �ܾƿ�
        dynamic_cast<CDynamicCamera*>(
            dynamic_cast<CPlayer*>(m_CGameObject)->GetCamera()
            )->ZoomTo(60.f, 2);

        m_bZoomOutTrigger = true;
    }


    else
        m_fMoveDuration += fTimeDelta;
}
