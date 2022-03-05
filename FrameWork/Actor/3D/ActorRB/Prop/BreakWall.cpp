//=============================================================================
//
//  壊れる壁クラス [BreakWall.cpp]
//  Date   : 2021/1/24
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "BreakWall.h"
#include "../../Billboard/Explosion.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Component/Component_Billboard.h"
#include "../../../../Manager/Manager_Audio.h"
#include "../../../../Manager/Manager_Game.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Level/Base/Level.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr int   MAX_BREAK_COUNT  = 7;//最大耐久値

//=============================================================================
// 初期化関数
//=============================================================================
void  BreakWall::Init()//初期化
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
		m_Component_Rigidbody->SetGravity(Vector3{0.0f,0.0f,0.0f});
	}

	//剛体のスケール設定
	SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });

	//耐久値初期化
	int m_BreakCount = 0;


}
//=============================================================================
// 耐久値加算関数
//=============================================================================
void BreakWall::AddBreakCount()
{
	//耐久値加算
	m_BreakCount++;

	//耐久値最大に到達
	if (m_BreakCount == MAX_BREAK_COUNT)
	{
		//剛体コンポーネントnullチェック
		if (m_Component_Rigidbody != nullptr)
		{
			//爆発ビルボードエフェクト
			Explosion* explosion = Manager_Game::Instance()->GetLevel()->AddActor<Explosion>();

			//座標設定
			explosion->SetPosition(m_Position);

			//スケール設定
			explosion->SetScale(Vector3{25.0f,25.0f,25.0f });

			//アニメ再生
			explosion->Play();

			//無効範囲にワープ
			m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });
		}
	}
}

