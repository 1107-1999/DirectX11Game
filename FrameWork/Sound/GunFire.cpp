//=============================================================================
//
//  銃声サウンドクラス [GunFire.cpp]
//  Date   : 2021/2/06
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "GunFire.h"
#include "../Manager/Manager_Audio.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr int MAX_SOUND = 4;//種類

//=============================================================================
// リソース読み込み関数
//=============================================================================
void GunFire::Load()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{

		//銃声
		manager_audio->Load_Resource("GunFire1", "ROM\\Sound\\SE\\Gun\\Fire1.WAV");
		manager_audio->Load_Resource("GunFire2", "ROM\\Sound\\SE\\Gun\\Fire2.WAV");
		manager_audio->Load_Resource("GunFire3", "ROM\\Sound\\SE\\Gun\\Fire3.WAV");
		manager_audio->Load_Resource("GunFire4", "ROM\\Sound\\SE\\Gun\\Fire4.WAV");

	}
}

//=============================================================================
// リソース解放関数
//=============================================================================
void GunFire::Unload()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//銃声
		manager_audio->Unload_Resource("GunFire1");
		manager_audio->Unload_Resource("GunFire2");
		manager_audio->Unload_Resource("GunFire3");
		manager_audio->Unload_Resource("GunFire4");

	}
}

//=============================================================================
// 初期化関数
//=============================================================================
void GunFire::Init()
{
	//リザーブ
	m_GunFireSounds.reserve(MAX_SOUND);
	
	//銃声
    m_GunFireSounds.push_back("GunFire1");
    m_GunFireSounds.push_back("GunFire2");
    m_GunFireSounds.push_back("GunFire3");
    m_GunFireSounds.push_back("GunFire4");

}

//=============================================================================
// 終了関数
//=============================================================================
void GunFire::Uninit()
{
	//クリア
	m_GunFireSounds.clear();
}

//=============================================================================
// 銃声再生関数
//=============================================================================
void GunFire::Play()
{
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{//キャッシュ

		//キューからランダムに再生
		int random = rand() % MAX_SOUND;
	
		manager_audio->Play(m_GunFireSounds[random], 0);

	}
}

