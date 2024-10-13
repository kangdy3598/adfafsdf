#pragma once

#include "Engine_Define.h"

class CGameObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim; // ��� Animation
	CAnimation*  m_pCurAnim; // ���� ������� Animation
	CGameObject* m_pOwner;  // Animator ���� ������Ʈ
	bool         m_bRepeat; // �ݺ� ��� ����

	CAnimation* m_pAnim; // �ִϸ��̼�

public:

	CGameObject* GetObj() { return m_pOwner; }


public:

	void CreateAnimation(const wstring& _strName, 
							CTexture* _pTex, 
							_vec2 _vLT, 
							_vec2 _vSliceSize,
							_vec2 _vStep,
							float _fDuration,
							UINT _iFrameCount);

	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	void update();
	void finalupdate();
	void render();


};

