//=============================================================================
//
//  足音サウンドクラス [FootStep.cpp]
//  Date   : 2021/1/21
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "FootStep.h"
#include "../Manager/Manager_Audio.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr int MAX_SOUND = 6;//種類

//=============================================================================
// リソース読み込み関数
//=============================================================================
void FootStep::Load()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{

		//コンクリート
		manager_audio->Load_Resource("Concrete1", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete1.WAV");
		manager_audio->Load_Resource("Concrete2", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete2.WAV");
		manager_audio->Load_Resource("Concrete3", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete3.WAV");
		manager_audio->Load_Resource("Concrete4", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete4.WAV");
		manager_audio->Load_Resource("Concrete5", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete5.WAV");
		manager_audio->Load_Resource("Concrete6", "ROM\\Sound\\SE\\FootStep\\Concrete\\Concrete6.WAV");

		//金属
		manager_audio->Load_Resource("Metal1", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal1.WAV");
		manager_audio->Load_Resource("Metal2", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal2.WAV");
		manager_audio->Load_Resource("Metal3", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal3.WAV");
		manager_audio->Load_Resource("Metal4", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal4.WAV");
		manager_audio->Load_Resource("Metal5", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal5.WAV");
		manager_audio->Load_Resource("Metal6", "ROM\\Sound\\SE\\FootStep\\Metal\\Metal6.WAV");

		//砂
		manager_audio->Load_Resource("Sand1", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand1.WAV");
		manager_audio->Load_Resource("Sand2", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand2.WAV");
		manager_audio->Load_Resource("Sand3", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand3.WAV");
		manager_audio->Load_Resource("Sand4", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand4.WAV");
		manager_audio->Load_Resource("Sand5", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand5.WAV");
		manager_audio->Load_Resource("Sand6", "ROM\\Sound\\SE\\FootStep\\Sand\\Sand6.WAV");

		//ガラス
		manager_audio->Load_Resource("Glass1","ROM\\Sound\\SE\\FootStep\\Glass\\Glass1.wav");
		manager_audio->Load_Resource("Glass2","ROM\\Sound\\SE\\FootStep\\Glass\\Glass2.wav");
		manager_audio->Load_Resource("Glass3","ROM\\Sound\\SE\\FootStep\\Glass\\Glass3.wav");

		//木
		manager_audio->Load_Resource("Wood1", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood1.WAV");
		manager_audio->Load_Resource("Wood2", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood2.WAV");
		manager_audio->Load_Resource("Wood3", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood3.WAV");
		manager_audio->Load_Resource("Wood4", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood4.WAV");
		manager_audio->Load_Resource("Wood5", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood5.WAV");
		manager_audio->Load_Resource("Wood6", "ROM\\Sound\\SE\\FootStep\\Wood\\Wood6.WAV");

	}
}

//=============================================================================
// リソース解放関数
//=============================================================================
void FootStep::Unload()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		manager_audio->Unload_Resource("Concrete1");
		manager_audio->Unload_Resource("Concrete2");
		manager_audio->Unload_Resource("Concrete3");
		manager_audio->Unload_Resource("Concrete4");
		manager_audio->Unload_Resource("Concrete5");
		manager_audio->Unload_Resource("Concrete6");

		manager_audio->Unload_Resource("Metal1");
		manager_audio->Unload_Resource("Metal2");
		manager_audio->Unload_Resource("Metal3");
		manager_audio->Unload_Resource("Metal4");
		manager_audio->Unload_Resource("Metal5");
		manager_audio->Unload_Resource("Metal6");

		manager_audio->Unload_Resource("Sand1");
		manager_audio->Unload_Resource("Sand2");
		manager_audio->Unload_Resource("Sand3");
		manager_audio->Unload_Resource("Sand4");
		manager_audio->Unload_Resource("Sand5");
		manager_audio->Unload_Resource("Sand6");

		manager_audio->Unload_Resource("Glass1");
		manager_audio->Unload_Resource("Glass2");
		manager_audio->Unload_Resource("Glass3");

		manager_audio->Unload_Resource("Wood1");
		manager_audio->Unload_Resource("Wood2");
		manager_audio->Unload_Resource("Wood3");
		manager_audio->Unload_Resource("Wood4");
		manager_audio->Unload_Resource("Wood5");
		manager_audio->Unload_Resource("Wood6");

	}
}

//=============================================================================
// 初期化関数
//=============================================================================
void FootStep::Init()
{
	//リザーブ
	for (int i = 0; i < MAX_PM_TYPE; i++)
	{
		m_FootStepes[i].reserve(MAX_SOUND);
	}

	//コンクリート
	m_FootStepes[PM_CONCRETE].push_back("Concrete1");
	m_FootStepes[PM_CONCRETE].push_back("Concrete2");
	m_FootStepes[PM_CONCRETE].push_back("Concrete3");
	m_FootStepes[PM_CONCRETE].push_back("Concrete4");
	m_FootStepes[PM_CONCRETE].push_back("Concrete5");
	m_FootStepes[PM_CONCRETE].push_back("Concrete6");

	//金属
	m_FootStepes[PM_METAL].push_back("Metal1");
	m_FootStepes[PM_METAL].push_back("Metal2");
	m_FootStepes[PM_METAL].push_back("Metal3");
	m_FootStepes[PM_METAL].push_back("Metal4");
	m_FootStepes[PM_METAL].push_back("Metal5");
	m_FootStepes[PM_METAL].push_back("Metal6");

	//砂
	m_FootStepes[PM_SAND].push_back("Sand1");
	m_FootStepes[PM_SAND].push_back("Sand2");
	m_FootStepes[PM_SAND].push_back("Sand3");
	m_FootStepes[PM_SAND].push_back("Sand4");
	m_FootStepes[PM_SAND].push_back("Sand5");
	m_FootStepes[PM_SAND].push_back("Sand6");

	//ガラス
	m_FootStepes[PM_GLASS].push_back("Glass1");
	m_FootStepes[PM_GLASS].push_back("Glass2");
	m_FootStepes[PM_GLASS].push_back("Glass3");
	m_FootStepes[PM_GLASS].push_back("Glass1");
	m_FootStepes[PM_GLASS].push_back("Glass2");
	m_FootStepes[PM_GLASS].push_back("Glass3");

	//木
	m_FootStepes[PM_WOOD].push_back("Wood1");
	m_FootStepes[PM_WOOD].push_back("Wood2");
	m_FootStepes[PM_WOOD].push_back("Wood3");
	m_FootStepes[PM_WOOD].push_back("Wood4");
	m_FootStepes[PM_WOOD].push_back("Wood5");
	m_FootStepes[PM_WOOD].push_back("Wood6");


}

//=============================================================================
// 終了関数
//=============================================================================
void FootStep::Uninit()
{
	for (int i = 0; i < MAX_PM_TYPE; i++)
	{//クリア
		m_FootStepes[i].clear();
	}
}

//=============================================================================
// 足音再生関数(引数は床の材質)
//=============================================================================
void FootStep::Play(int _physicsMaterial)
{
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{//キャッシュ

		if (_physicsMaterial != INVALID_ID && _physicsMaterial < MAX_PM_TYPE)
		{
			//キューからランダムに再生
			int random = rand() % MAX_SOUND;
	
			manager_audio->Play(m_FootStepes[_physicsMaterial][random], 0);
		}

	}
}

