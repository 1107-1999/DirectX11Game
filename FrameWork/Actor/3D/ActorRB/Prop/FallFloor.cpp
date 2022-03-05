//=============================================================================
//
//  落ちる床クラス [FallFloor.cpp]
//  Date   : 2021/1/24
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "FallFloor.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Manager/Manager_Audio.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float START_POSTION  = 285.0f;
constexpr float END_POSTION    = 87.5f;
constexpr int   PUSHER_PATTERN = 4;
constexpr int   FALL_COOLTIME  = 300;

//=============================================================================
// リソース読み込み・削除関数
//=============================================================================
void  FallFloor::Load()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//ガラス音読み込み
		manager_audio->Load_Resource("Glass_Destoroy", "ROM\\Sound\\SE\\FootStep\\Glass\\Glass_Destoroy.wav");
	}
}
void  FallFloor::Unload()
{
	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//ガラス音削除
		manager_audio->Unload_Resource("Glass_Destoroy");
	}
}

//=============================================================================
// 初期化関数
//=============================================================================
void  FallFloor::Init()
{
	//親クラス初期化
	ActorRB::Init();

	//キューブコンポーネント追加
	m_Component_Cube = AddComponent<Component_Cube>(0);

	//キューブコンポーネントnullチェック
	if (m_Component_Cube != nullptr)
	{

		//テクスチャ設定
		m_Component_Cube->SetTexture("LD");

	}

	//静的ボックス剛体追加
	AddBoxRB(m_Scale, m_Position, 1000000);

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//重力無効化
		m_Component_Rigidbody->SetGravity(Vector3_Zero);
	}

	//剛体のスケールオフセット設定
	SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });

	//プレイヤー検知用OBB追加
	m_ON_Judge = AddComponent<Component_OBB>(0);

	//プレイヤー検知用OBB追加nullチェック
	if (m_ON_Judge != nullptr)
	{
		//スケール調整
		m_ON_Judge->SetScale(Vector3{ 8.5f,1.0f,3.0f});

	}

	//キャッシュ用座標初期化
	m_Positioncache = Vector3_Zero;
}

//=============================================================================
// 更新関数
//=============================================================================
void FallFloor::Update()
{

	//プレイヤー検知用OBB追加nullチェック
	if (m_ON_Judge != nullptr)
	{

		//プレイヤーが乗っている場合
		if (m_ON_Judge->GetOverlap())
		{

		    //現在の座標保存
			m_Positioncache = m_Position;

			//落下クールタイム発生
			m_CoolTime = FALL_COOLTIME;

			if (m_Component_Rigidbody != nullptr)
			{//nullチェック

				//無効範囲にワープ
				m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });
			}

			//オーディオマネージャーキャッシュ
			if (Manager_Audio* manager_audio = Manager_Audio::Instance())
			{
				//ガラス音再生
				manager_audio->Play("Glass_Destoroy",0);
			}
		}
	}

	//落下クールタイムがある場合
	if (m_CoolTime > 0)
	{
		//クールタイム減算
		m_CoolTime--;

		//クールタイム終了時
		if (m_CoolTime == 0)
		{
			//剛体コンポーネントnullチェック
			if (m_Component_Rigidbody != nullptr)
			{
				//既定位置にワープ
				m_Component_Rigidbody->SetWarp(m_Positioncache);
			}
		}
	}

	//親クラス更新
	ActorRB::Update();
	
}

