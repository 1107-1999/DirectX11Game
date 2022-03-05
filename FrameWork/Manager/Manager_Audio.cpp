//=============================================================================
//
//  オーディオマネージャー [Manager_Audio.cpp]
//  Date   : 2021/12/19
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Manager_Audio.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Manager_Audio::Init()
{
	// COMの初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	XAudio2Create(&m_XAudio2);
	m_XAudio2->CreateMasteringVoice(&m_MasterVoice);

	m_Player.resize(MAX_AUDIO);
}

//=============================================================================
// 更新関数
//=============================================================================
void Manager_Audio::Update()
{
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		if (!m_Player[i])continue;
		// ソースボイスがnullだったらWavePlalyerを削除
		if (m_Player[i]->GetIsDestroy())
		{
			m_Player[i]->UnInit();
			delete m_Player[i];
			m_Player[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_AUDIO; i++)
	{		
		if (!m_Player[i])continue;
		m_Player[i]->Update();
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void Manager_Audio::Uninit()
{
	// コンテナの要素の破棄
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		if (m_Player[i] != nullptr)
		{
			m_Player[i]->UnInit();
		}

		delete m_Player[i];
		m_Player[i] = nullptr;
	}

	// マスターボイスの破棄
	m_MasterVoice->DestroyVoice();
	m_MasterVoice = nullptr;

	// XAudio2本体の破棄
	m_XAudio2->Release();
	m_XAudio2 = nullptr;

	CoUninitialize();
}

//=============================================================================
// 使用していない要素を検索する関数
//=============================================================================
int Manager_Audio::IsUsePlayer()
{
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		if (!IsInElement(i))
		{
			return i;
		}
	}

	return ALL_USE_AUDIO;
}

//=============================================================================
// 引数の要素が使われているかの確認する関数
//=============================================================================
bool Manager_Audio::IsInElement(int _num)
{
	if (m_Player[_num])return true;

	return false;
}

//=============================================================================
// サウンド再生関数
//=============================================================================
int Manager_Audio::Play(const char* _key,int loop)
{
	int num = IsUsePlayer();

	if (num != ALL_USE_AUDIO)
	{
		m_Player[num] = new WavePlayer;
		bool IsSucceed = m_Player[num]->Play(m_XAudio2, GetResource(_key), loop);

		// 再生失敗した時の処理
		if (IsSucceed == false)
		{
			delete m_Player[num];
			m_Player[num] = nullptr;

			num = ALL_USE_AUDIO;
		}

		return num;
	}

	return ALL_USE_AUDIO;
}

//=============================================================================
// サウンドフェード設定関数
//=============================================================================
void Manager_Audio::Fade(int _num, float _time, float _volume)
{
	m_Player[_num]->SetFade(_time, _volume);
}

//=============================================================================
// リソース読み込み関数
//=============================================================================
void Manager_Audio::Load_Resource(const char* _key, LPCSTR _fileName)
{
	if (!m_Resource[_key])
	{
		m_Resource[_key] = _fileName;
	}
}

//=============================================================================
// 指定要素のリソース解放関数
//=============================================================================
void Manager_Audio::Unload_Resource(const char* _key)
{
	m_Resource.erase(_key);
}

//=============================================================================
// 全リソース解放関数
//=============================================================================
void Manager_Audio:: Unload_Resource_All()
{
	m_Resource.clear();
}