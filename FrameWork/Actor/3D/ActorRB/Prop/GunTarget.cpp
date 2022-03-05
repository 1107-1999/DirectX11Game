//=============================================================================
//
// 銃のターゲットクラス [GunTarget.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "GunTarget.h"
#include "../../Billboard/Explosion.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Manager/Manager_Game.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Level/Base/Level.h"
#include "../../../../Actor/3D/ActorRB/Prop/BreakWall.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float TARGET_LIMIT = 2.75f;//ターゲットの限界座標

//=============================================================================
// 初期化関数
//=============================================================================
void  GunTarget::Init()
{
	//初期化
	ActorRB::Init();

	//静的メッシュコンポーネント追加
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	if (m_Component_StaticMesh != nullptr)
	{//nullチェック

		//モデルロード
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Target.fbx");

		//回転オフセット X軸　Y軸 Z軸
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(-90.0f),DegToRad(0.0f) });

		//スケールオフセット
		m_Component_StaticMesh->SetScaleRate(0.5f);

	}

	//静的ボックス剛体追加
	AddBoxRB(m_Scale, m_Position, 1000000);

	//リジッドボディコンポーネントが存在する場合
	if (m_Component_Rigidbody != nullptr)
	{

		//重力無効化
		m_Component_Rigidbody->SetGravity(Vector3{0.0f,0.0f,0.0f});
		//スケールオフセット調整
		m_Component_Rigidbody->SetScale(Vector3{ 0.5f,0.125f,0.75f });

	}

	//OBBコンポーネントが存在する場合
	if (m_Component_OBB != nullptr)
	{
		//リジッドボディと同スケールに調整
		m_Component_OBB->SetScale(Vector3{ 0.5f,0.63f,0.1f });
		m_Component_OBB->SetPositionOffset(Vector3{ 0.0f,0.925f,0.0f });
	}

	//初期速度
	m_Velocity = 2000000.0f;

	//進行方向
	m_Vector = true;

	//爆発エフェクトキャッシュ
	m_Explosion = Manager_Game::Instance()->GetLevel()->AddActor<Explosion>();

}

//=============================================================================
// 更新関数
//=============================================================================
void GunTarget::Update()
{
	if (m_Component_OBB->GetOverlap())
	{//弾とぶつかった場合

		if (m_Explosion != nullptr)
		{//爆発エフェクト設定

		    //爆発アニメ再生
			m_Explosion->Play();

			//座標設定
			m_Explosion->SetPosition(m_Position + HalfSize(GetUp()));
		}

		//無効範囲にワープ
		m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });

		if (BreakWall* wall = Manager_Game::Instance()->GetLevel()->GetActor<BreakWall>())
		{//取得&キャッシュ
			wall->AddBreakCount();
		}

	}

	//目標座標を通リ過ぎていた場合に方向転換
	if (m_Position.x >= TARGET_LIMIT && !m_Vector)
	{
		m_Position.x = TARGET_LIMIT;
		m_Vector = true;
	}
	else if (m_Position.x <= -TARGET_LIMIT && m_Vector)
	{
		m_Position.x = -TARGET_LIMIT;
		m_Vector = false;
	}

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		if (m_Vector)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetRight()* m_Velocity);
		}
		else 
		{
			m_Component_Rigidbody->SetMoveXYZ(GetRight()* m_Velocity);
		}
	
		//親クラス更新
		ActorRB::Update();
	}
}
