#include "InputDev.h"

IMPLEMENT_SINGLETON(CInputDev)

CInputDev::CInputDev(void)
{
	ZeroMemory(m_byPrevKeyState, sizeof(m_byPrevKeyState));
	ZeroMemory(m_byCurrKeyState, sizeof(m_byCurrKeyState));
}

CInputDev::~CInputDev(void)
{
	Free();
}

_bool CInputDev::GetAnyActionKeyDown()
{
	_bool returnValue = false;
	int keyArray[] = { PLY_LEFTKEY, PLY_RIGHTKEY, PLY_UPKEY, PLY_DOWNKEY,
					   PLY_DASHKEY, PLY_SWINGKEY, PLY_LIFTKEY, PLY_ROLLKEY,
					   PLY_DANCEKEY, PLY_SMASHKEY };

	for (int i = 0; i < CONTROLKEY::PLY_ENDKEY; i++)
	{
		returnValue |= GetKeyDown(keyArray[i]);
	}

	return returnValue;
}

HRESULT CInputDev::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{
	//DInput �İ�ü�� �����ϴ� �Լ� 
	FAILED_CHECK_RETURN(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL), E_FAIL);


	//Ű���� ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);



	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� �� �ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();




	// ���콺 ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ� 
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� �� �ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pMouse->Acquire();


	return S_OK;
}

void CInputDev::Update_InputDev(void)
{
	memcpy(m_byPrevKeyState, m_byCurrKeyState, sizeof(m_byCurrKeyState));

	m_pKeyBoard->GetDeviceState(256, m_byCurrKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void CInputDev::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}
