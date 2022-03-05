//=============================================================================
//
//  爆発ビルボードエフェクトクラス [Explosion.cpp]
//  Date   : 2022/1/26
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Explosion.h"
#include "../../../Component/Component_Billboard.h"
#include "../../../Manager/Manager_Texture.h"
#include "../../../Manager/Manager_Audio.h"

//=============================================================================
// リソース読み込み・削除関数
//=============================================================================
void  Explosion::Load()
{
	//テクスチャーマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//テクスチャ読み込み
		manager_Texture->LoadTexture("Explosion", "ROM\\2D\\Effect\\T_Explosion.png");
	}

	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE読み込み
		manager_audio->Load_Resource("Explosion", "ROM\\Sound\\SE\\Effect\\Explosion.wav");
	}
}
void  Explosion::Unload()
{
	//テクスチャーマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//テクスチャ解放
		manager_Texture->UnloadTexture("Explosion");
	}

	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE解放
		manager_audio->Unload_Resource("Explosion");
	}

}

//=============================================================================
// 初期化関数
//=============================================================================
void  Explosion::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//スケール設定
	m_Scale = Vector3{ 2.0f,2.0f,2.0f };

	//ビルボードコンポーネント追加
	m_Component_Billboard = AddComponent<Component_Billboard>(0);//追加

	//ビルボードコンポーネントnullチェック
	if (m_Component_Billboard != nullptr)
	{
		m_Component_Billboard->SetTexture("Explosion");       //テクスチャー設定
		m_Component_Billboard->CalculationOneFrameSize(5, 4); //5*4のアニメーションとして設定
		m_Component_Billboard->SetMaxAnimCount(3);            //6フレームに1度アニメーション更新
		m_Component_Billboard->SetLoop(false);                //ループ再生なし
		m_Component_Billboard->SetActive(false);              //初期設定は非アクティブ
	}


}

//=============================================================================
// 再生関数
//=============================================================================
void Explosion::Play()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE再生
		manager_audio->Play("Explosion", 0);
	}
	//ビルボードコンポーネントnullチェック
	if (m_Component_Billboard != nullptr)
	{
		//アニメ再生
		m_Component_Billboard->Replay();
	}

}