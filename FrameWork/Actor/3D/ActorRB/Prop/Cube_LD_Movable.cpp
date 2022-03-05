//=============================================================================
//
// 動的レベルデザイン用キューブクラス [Cube_LD_Movable.cpp]
//  Date   : 2021/1/23
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Cube_LD_Movable.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Component/Component_Cube.h"

//=============================================================================
// 初期化関数
//=============================================================================
void  Cube_LD_Movable::Init()
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
		//摩擦強
		m_Component_Rigidbody->SetFriction(0.75f);
	}

	//速度初期化
	m_Velocity = Vector3_Zero;
}

//=============================================================================
// 更新関数
//=============================================================================
void Cube_LD_Movable::Update()
{

	//目標X座標を通リ過ぎていた場合に方向転換
	if (m_Position.x >= m_Target.x && m_OldPosition.x < m_Target.x
		|| m_Position.x <= m_Target.x && m_OldPosition.x > m_Target.x)
	{
		//現在のX座標を目的X座標にする
		m_Position.x = m_Target.x;
		//目的X座標を移動開始座標に設定
		m_Target.x = m_Start.x;
		//移動開始座標を現在の座標に設定
		m_Start.x = m_Position.x;
	}
	//目標Y座標を通リ過ぎていた場合に方向転換
	if (m_Position.y >= m_Target.y && m_OldPosition.y < m_Target.y
		|| m_Position.y <= m_Target.y && m_OldPosition.y > m_Target.y)
	{
		//現在のY座標を目的Y座標にする
		m_Position.y = m_Target.y;
		//目的Y座標を移動開始座標に設定
		m_Target.y = m_Start.y;
		//移動開始座標を現在の座標に設定
		m_Start.y = m_Position.y;
	}
	//目標Z座標を通リ過ぎていた場合に方向転換
	if (m_Position.z >= m_Target.z && m_OldPosition.z < m_Target.z
		|| m_Position.z <= m_Target.z && m_OldPosition.z > m_Target.z)
	{
		//現在のZ座標を目的Z座標にする
		m_Position.z = m_Target.z;
		//目的Z座標を移動開始座標に設定
		m_Target.z = m_Start.z;
		//移動開始座標を現在の座標に設定
		m_Start.z = m_Position.z;
	}

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//目標座標に近づく
		if (m_Position.x > m_Target.x)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetRight()* m_Velocity.x);
		}
		else if (m_Position.x < m_Target.x)
		{
			m_Component_Rigidbody->SetMoveXYZ(GetRight()* m_Velocity.x);
		}
		if (m_Position.y > m_Target.y)
		{	
			m_Component_Rigidbody->SetMoveXYZ(-GetUp()* m_Velocity.y);
		}
		else if (m_Position.y < m_Target.y)
		{
		
			m_Component_Rigidbody->SetMoveXYZ(GetUp()* m_Velocity.y);
		}
		if (m_Position.z > m_Target.z)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetForward()* m_Velocity.z);
		}
		else if (m_Position.z < m_Target.z)
		{
			m_Component_Rigidbody->SetMoveXYZ(GetForward()* m_Velocity.z);
			
		}

		//1フレーム前の座標として保存
		m_OldPosition = m_Position;

		//親クラス更新
		ActorRB::Update();
	}
}
