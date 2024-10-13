#pragma once

#include "Engine_Define.h"
#include "Export_Utility.h"
#include "Export_System.h"


class CImgui_ObjectTool
{
	DECLARE_SINGLETON(CImgui_ObjectTool)


private:
	explicit CImgui_ObjectTool();
	virtual ~CImgui_ObjectTool();

public:
	void				init();
	void				update();
	void				render();

public:
	void				ShowObjectWindow();
	void				ShowInstalledObjectWindow();
	_vec3				PickingOnTerrain();
	void				InstallObject(wstring _TextureKey, wstring _CurTextureData , wstring _forConvert);	

public: 
	void				Save();
	void                Read();

private:
	bool LoadTextureFromFile(LPDIRECT3DDEVICE9 d3dDevice, const char* filePath, IDirect3DTexture9** outTexture)
	{
		HRESULT hr = D3DXCreateTextureFromFileA(d3dDevice, filePath, outTexture);
		return SUCCEEDED(hr);
	}



private:

	bool m_bShowObjectWindow;
	bool m_bShowInstallObjectWindow;

	

	IDirect3DTexture9* m_pObjectTexture;	
	vector<IDirect3DTexture9*> m_vecObjectTexture;	


	Engine::CTransform* m_pCurObjectTransform;
	Engine::CTransform* m_pPreObjectTransform;

	wstring m_sCurTextureData;
	wstring m_sCurTextureKey;
	wstring m_strCurObjectName;

	_vec3  m_vecPickPos;

	vector<const _tchar*> m_vecObjectList;	

	int index;

	float	floatPosArrayTest[3];

	float	floatRotationArray[3];
	float	prevRotationArray[3];

	float   floatScaleArray[3];
	float   prevScaleArray[3];

	wstring m_wCurChoiceObject;

	//���Ϳ��� ���⸦ �Ѹ�ŭ ������ ������ϱ� �ε��� �̸����� �ٿ����͵� ��������ϹǷ�
	int deleteCount; 

	const _tchar* CurClickObject; 


public:
	//Imgui �� �б� ���� �ɹ� ���� 
	wstring  m_wCurReadTextureKey;
	D3DXMATRIX  m_CurReadmatrix;
	
};

