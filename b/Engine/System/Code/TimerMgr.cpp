#include "TimerMgr.h"

IMPLEMENT_SINGLETON(CTimerMgr)

CTimerMgr::CTimerMgr()
{

}

CTimerMgr::~CTimerMgr()
{
	Free();
}

_float CTimerMgr::Get_TimeDelta(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	NULL_CHECK_RETURN(pTimer, 0.f);

	return pTimer->Get_TimeDelta();
}

void CTimerMgr::Set_TimeDelta(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	NULL_CHECK(pTimer);

	pTimer->Update_Timer();
}

HRESULT CTimerMgr::Ready_Timer(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);

	if (nullptr != pTimer)
		return E_FAIL; 

	pTimer = CTimer::Create();
	NULL_CHECK_RETURN(pTimer, E_FAIL);

	m_mapTimer.insert({ pTimerTag, pTimer });


	return S_OK;
}

CTimer* CTimerMgr::Find_Timer(const _tchar* pTimerTag)
{
	auto iter = find_if(m_mapTimer.begin(), m_mapTimer.end(), CTag_Finder(pTimerTag));

	if (iter == m_mapTimer.end())
		return nullptr;


	return iter->second;
}

void CTimerMgr::Free()
{

	for_each(m_mapTimer.begin(), m_mapTimer.end(), CDeleteMap());
	m_mapTimer.clear();

}
