#pragma once
#include "Component.h"


BEGIN(Engine)

class CAnimation2;
class CGameObject;


class ENGINE_DLL CAnimator2 :public CComponent
{
private:
	explicit CAnimator2();
	explicit CAnimator2(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimator2(const CAnimator2& rhs);
	virtual  ~CAnimator2();

private:
	map<wstring, CAnimation2*>		m_mapAnim;  //��� �ִϸ��̼� ���� ����
	CAnimation2* m_pCurAnim; // ���� ������� Animation
	CGameObject* m_pOwner;   //Animator ���� ������Ʈ
	bool							m_bRepeat;  // �ݺ���� ���� 

	CAnimation2* m_pAnim;    // �ִϸ��̼�


public:
	CAnimation2* GetAnimation() { return m_pCurAnim; }
	CGameObject* GetGameObj() { return m_pOwner; }
	static CAnimator2* Create(LPDIRECT3DDEVICE9 pGraphicDev);

public:

	void CreateAnimation(const wstring& _strName,
		IDirect3DTexture9* _pTex,
		_vec2 _vLT,
		_vec2 _vSliceSize,
		_vec2 _vStep,
		float _fDuration,
		UINT  _iFrameCount);

	CAnimation2* FindAnimation(const wstring& _strName);
	void		  Play(const wstring& _strName, bool _bRepeat);

public:
	virtual void  LateReady_Component();
	virtual _int  Update_Component(const _float& fTimeDelta);
	virtual void  LateUpdate_Component(const _float& fTimeDelta);
	void   render();


public:
	void SetAnimationFrame(const wstring& _strName, int _idx);


public:
	virtual CComponent* Clone();

protected:
	virtual void  Free();
};

END