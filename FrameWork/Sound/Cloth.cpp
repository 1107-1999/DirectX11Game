//=============================================================================
//
//  服サウンドクラス [Cloth.cpp]
//  Date   : 2021/1/23
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Cloth.h"
#include "../Manager/Manager_Audio.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr int MAX_SOUND = 7;//種類

//=============================================================================
// リソース読み込み関数
//=============================================================================
void Cloth::Load()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{

		//服音
		manager_audio->Load_Resource("Cloth1", "ROM\\Sound\\SE\\Cloth\\Cloth1.WAV");
		manager_audio->Load_Resource("Cloth2", "ROM\\Sound\\SE\\Cloth\\Cloth2.WAV");
		manager_audio->Load_Resource("Cloth3", "ROM\\Sound\\SE\\Cloth\\Cloth3.WAV");
		manager_audio->Load_Resource("Cloth4", "ROM\\Sound\\SE\\Cloth\\Cloth4.WAV");
		manager_audio->Load_Resource("Cloth5", "ROM\\Sound\\SE\\Cloth\\Cloth5.WAV");
		manager_audio->Load_Resource("Cloth6", "ROM\\Sound\\SE\\Cloth\\Cloth6.WAV");
		manager_audio->Load_Resource("Cloth7", "ROM\\Sound\\SE\\Cloth\\Cloth7.WAV");
		manager_audio->Load_Resource("Cloth8", "ROM\\Sound\\SE\\Cloth\\Cloth8.WAV");

		//アクセサリ音
		manager_audio->Load_Resource("Cloth21", "ROM\\Sound\\SE\\Cloth\\Cloth21.WAV");
		manager_audio->Load_Resource("Cloth22", "ROM\\Sound\\SE\\Cloth\\Cloth22.WAV");
		manager_audio->Load_Resource("Cloth23", "ROM\\Sound\\SE\\Cloth\\Cloth23.WAV");
		manager_audio->Load_Resource("Cloth24", "ROM\\Sound\\SE\\Cloth\\Cloth24.WAV");
		manager_audio->Load_Resource("Cloth25", "ROM\\Sound\\SE\\Cloth\\Cloth25.WAV");
		manager_audio->Load_Resource("Cloth26", "ROM\\Sound\\SE\\Cloth\\Cloth26.WAV");
		manager_audio->Load_Resource("Cloth27", "ROM\\Sound\\SE\\Cloth\\Cloth27.WAV");
		manager_audio->Load_Resource("Cloth28", "ROM\\Sound\\SE\\Cloth\\Cloth28.WAV");
	}


}

//=============================================================================
// リソース解放関数
//=============================================================================
void Cloth::Unload()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//服音
		manager_audio->Unload_Resource("Cloth1");
		manager_audio->Unload_Resource("Cloth2");
		manager_audio->Unload_Resource("Cloth3");
		manager_audio->Unload_Resource("Cloth4");
		manager_audio->Unload_Resource("Cloth5");
		manager_audio->Unload_Resource("Cloth6");
		manager_audio->Unload_Resource("Cloth7");
		manager_audio->Unload_Resource("Cloth8");

		//アクセサリ音
		manager_audio->Unload_Resource("Cloth21");
		manager_audio->Unload_Resource("Cloth22");
		manager_audio->Unload_Resource("Cloth23");
		manager_audio->Unload_Resource("Cloth24");
		manager_audio->Unload_Resource("Cloth25");
		manager_audio->Unload_Resource("Cloth26");
		manager_audio->Unload_Resource("Cloth27");
		manager_audio->Unload_Resource("Cloth28");

	}
}

//=============================================================================
// 初期化関数
//=============================================================================
void Cloth::Init()
{
	//服音
	m_ClothSounds.push_back("Cloth1");
	m_ClothSounds.push_back("Cloth2");
	m_ClothSounds.push_back("Cloth3");
	m_ClothSounds.push_back("Cloth4");
	m_ClothSounds.push_back("Cloth5");
	m_ClothSounds.push_back("Cloth6");
	m_ClothSounds.push_back("Cloth7");
	m_ClothSounds.push_back("Cloth8");

	//アクセサリ音
	m_ClothSoundsMetal.push_back("Cloth21");
	m_ClothSoundsMetal.push_back("Cloth22");
	m_ClothSoundsMetal.push_back("Cloth23");
	m_ClothSoundsMetal.push_back("Cloth24");
	m_ClothSoundsMetal.push_back("Cloth25");
	m_ClothSoundsMetal.push_back("Cloth26");
	m_ClothSoundsMetal.push_back("Cloth27");
	m_ClothSoundsMetal.push_back("Cloth28");

}

//=============================================================================
// 終了関数
//=============================================================================
void Cloth::Uninit()
{

	m_ClothSounds.clear();
	m_ClothSoundsMetal.clear();
}

//=============================================================================
// 服の音再生関数
//=============================================================================
void Cloth::PlayClothSound()
{
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{//キャッシュ

		//キューからランダムに再生
		int random = rand() % MAX_SOUND;

		manager_audio->Play(m_ClothSounds[random], 0);

	}
}

//=============================================================================
// アクセサリ音の音再生関数
//=============================================================================
void Cloth::PlaySoundsMetal()
{
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{//キャッシュ

		//キューからランダムに再生
		int random = rand() % MAX_SOUND;

		manager_audio->Play(m_ClothSoundsMetal[random], 0);

	}
}