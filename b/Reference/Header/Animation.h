#pragma once

// �̹��� : Ư�� �ִϸ��̼� ����� ��� �ִ� png���� �� �� (Sprite_BabyOgu_Idle.png)
// ������ : �̹��� �ȿ� �ִ� �ִϸ��̼� �� ���� (Idle�̹����� 7x4 ������)

#include "VIBuffer.h"
#include "Export_Utility.h"
BEGIN(Engine)

class ENGINE_DLL CAnimation : public CVIBuffer//CComponent
{

private:
	explicit CAnimation();
	explicit CAnimation(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimation(const CAnimation& rhs);
	virtual ~CAnimation();

public:
	HRESULT					Ready_Animation(const vector<_vec2> _vecFrameCount,
		const vector<vector<int>*> _vecFramePlay);

	virtual  _int			Update_Component(const _float& fTimeDelta);
	virtual  void			LateUpdate_Component(const _float& fTimeDelta);
	virtual	 void   		Render_Buffer();

public:
	void SetAnimFrame(PLAYERSTATE _ePlayerState, bool _bDiagonal);
	void SetAnimDir(PLAYERSTATE _ePlayerState, _vec3 _dir, bool& _bDiagonal)
	{
		if (_dir.x == 1)
		{
			if (_dir.z == -1)
			{
				_bDiagonal = true;
				m_iCurrentDir = 3;
			}
			else if (_dir.z == 0)
			{
				_bDiagonal = false;
				m_iCurrentDir = 3;

			}
			else
			{
				_bDiagonal = true;
				m_iCurrentDir = 2;
			}
		}
		else if (_dir.x == 0)
		{

			if (_dir.z == 1)
			{
				_bDiagonal = false;
				m_iCurrentDir = 0;
			}
			else if (_dir.z == 0)
			{
			}
			else
			{
				_bDiagonal = false;
				m_iCurrentDir = 1;
			}
		}
		else
		{
			if (_dir.z == -1)
			{
				_bDiagonal = true;
				m_iCurrentDir = 1;
			}
			else if (_dir.z == 0)
			{
				_bDiagonal = false;
				m_iCurrentDir = 2;
			}
			else
			{
				_bDiagonal = true;
				m_iCurrentDir = 0;
			}
		}
		SetAnimFrame(_ePlayerState, _bDiagonal);
	}

	void UpdateUV();
	int  GetCurrentFrame() { return currentFrame; }
	bool IsAnimationEnd() { return m_bAnimationEnd; }
	void SetAnimationPlaying() { m_bAnimationEnd = false; }
	void SetAnimationPause(bool _value) { m_bAniamtionPause = _value; }
private:

	// Loading���� Animation.dat ������ �޾ƿͼ�
	// �ش� ������Ʈ�� ��� �ൿ �ִϸ��̼��� ��� ����
	vector<_vec2>		 m_vecFrameCount;
	vector<vector<int>*> m_vecFramePlay;

	// ���� �������� ���¿� ���� �ִϸ��̼� ����
	_vec2				 m_currentFrameCount; // ������ ����
	_vec2				 m_vecCurrentFrameUV; // ���� �������� ����ϱ� ���� UV ����
	vector<int>			 m_currentFramePlay[OBJ_DIRECTION::OBJDIR_END]; // ������ ��� ����


	PLAYERSTATE			m_eCurrentState;
	//int					m_eCurrentDir;
	int					m_iCurrentDir;

	int					currentFrame;
	float				m_fAccTime;

	bool				m_bAnimationEnd;
	bool				m_bAniamtionPause;
public:
	static CAnimation* Create(LPDIRECT3DDEVICE9	      pGraphicDev,
		const vector<_vec2>		  _vecFrameCount,
		const vector<vector<int>*> _vecFramePlay);

	virtual CComponent* Clone();

private:
	virtual void			Free();


};

END