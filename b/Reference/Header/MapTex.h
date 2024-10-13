#pragma once
#include "VIBuffer.h"


BEGIN(Engine)	

class ENGINE_DLL CMapTex : public  CVIBuffer
{

private:
	explicit CMapTex();
	explicit CMapTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMapTex(const CMapTex& rhs);
	virtual ~CMapTex();

public:
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const float& dwVtxItv, const float& dwVtxItY);
	virtual void Render_Buffer();
	const _vec3* Get_VtxPos() const { return m_pPos; }	
	_vec3 Get_TestVtxPos() { return m_Vec3; }	

	//���⼭ pVertex �������� �����ҷ��� �ɹ����� �ؼ� �������ֱ�.




public:
	static  CMapTex* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const float& dwVtxItvX, const float& dwVtxItvY);
	virtual CComponent* Clone();


private:
	virtual void Free(); 

private:
	_vec3* m_pPos; 

	//test �� 
	_vec3  m_Vec3; 


	//test ���� �����ͺ��� 
	VTXTEX2* m_pVertex;		


};

END