//=============================================================================
//
// 押すものクラス [Pusher.cpp]
//  Date   : 2021/1/23
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Pusher.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float START_POSTION  = 285.0f;//スポーン位置
constexpr float END_POSTION    = 87.5f; //目的地
constexpr int   PUSHER_PATTERN = 4;     //パターン数

//=============================================================================
// 初期化関数
//=============================================================================
void  Pusher::Init()
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

	//静的ボックスリジッドボディ追加
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
	m_Velocity = {0.0f,0.0f,3000000.0f};
}

//=============================================================================
// 更新関数
//=============================================================================
void Pusher::Update()
{
	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//Z座標下限を越えた場合
		if (m_Position.z <= END_POSTION)
		{
			//4択からランダムに座標とスケールを設定
			int random = rand() % PUSHER_PATTERN;

			switch (random)
			{
			case 0:
				SetRigidbodyPosition(Vector3{ 0.0f,5.75f,275.0f });
				SetRigidbodyScale(Vector3{ 10.0f,1.0f,1.0f });
				break;
			case 1:
				SetRigidbodyPosition(Vector3{ -1.75f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 6.5f,4.0f,1.0f });
				break;
			case 2:
				SetRigidbodyPosition(Vector3{ 1.75f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 6.5f,4.0f,1.0f });
				break;
			case 3:
				SetRigidbodyPosition(Vector3{ 0.0f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 7.0f,4.0f,1.0f });
				break;
			}
		}

		//移動処理
		m_Component_Rigidbody->SetMoveXYZ(-GetForward()* m_Velocity.z);

		//親クラス更新
		ActorRB::Update();
	}
}
