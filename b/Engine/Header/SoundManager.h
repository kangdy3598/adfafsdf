#pragma once
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CSoundManager
{
    DECLARE_SINGLETON(CSoundManager)

private:    
    // ���� ���ҽ� ������ ���� ��ü 
    map<const _tchar*, FMOD::Sound*> m_mapSound;

    // FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
    FMOD::Channel* m_pChannelArr[MAXCHANNEL];
    // ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
    FMOD::System* m_pSystem;
    _tchar* m_CurBGM;

private:
    explicit CSoundManager();
    virtual ~CSoundManager();

public:
    void Initialize();
    void Release();

public:
    void Play_Sound(const _tchar* pSoundKey, CHANNELID eID, float fVolume);
    void PlayBGM(const _tchar* pSoundKey, float fVolume);
    void StopSound(CHANNELID eID);
    void StopAll();
    void SetChannelVolume(CHANNELID eID, float fVolume);
    _tchar* Get_CurBGM() { return m_CurBGM; };

private:
    void LoadSoundFile();        
};

END