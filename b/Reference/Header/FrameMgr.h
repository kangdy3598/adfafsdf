#pragma once

#include "Base.h"
#include "Frame.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CFrameMgr : public CBase
{
	DECLARE_SINGLETON(CFrameMgr)

private:
	explicit CFrameMgr();
	virtual  ~CFrameMgr();

public:
	HRESULT  Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);
	_bool			IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);

private:
	CFrame* Find_Frame(const _tchar* pFrameTag);

private:
	map<const _tchar*, CFrame*>			m_mapFrame;

private:
	virtual void		Free();
	
};

END
