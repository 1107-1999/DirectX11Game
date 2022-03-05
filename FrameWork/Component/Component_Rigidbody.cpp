//=============================================================================
//
//  剛体コンポーネント [Component_Rigidbody.cpp]
//  Date   : 2021/11/22
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Component_Rigidbody.h"
#include "../Manager/Manager_Game.h"
#include "../Actor/3D/Base/Actor3D.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr int   JUMP_UP_TIME      = 6;     //ジャンプ上昇時間
constexpr int   HIGH_JUMP_UP_TIME = 8;     //ハイジャンプ上昇時間
constexpr float JUMP_POWER        = 500.0f;//ジャンプ力

//=============================================================================
// 初期化関数
//=============================================================================
void Component_Rigidbody::Init()
{
	//基底クラス更新
	Component::Init();

	//nullptr代入
	m_RigidBody = nullptr;

	//ジャンプ時間初期化
	m_JumpTime = 0;
}

//=============================================================================
// 更新関数
//=============================================================================
void Component_Rigidbody::Update()
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//アクター3Dにキャスト成功した場合
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//現在のトランスフォーム取得
			btTransform transform = m_RigidBody->body->getWorldTransform();

			//現在の剛体の位置取得
			btVector3 btPosition = transform.getOrigin();

			//オーナーの回転取得
			Vector3 rotation = actor3D->GetRotation();

			//オーナーの回転を剛体に設定(y,x,zの順)
			btVector3 btrotation = { rotation.y, rotation.x, rotation.z };

			//トランスフォームに代入
			transform.setRotation(btQuaternion{ btrotation.x(), btrotation.y(), btrotation.z() });

			//現在のトランスフォームをに設定
			m_RigidBody->body->setWorldTransform(transform);

			//座標を取得
			btPosition = transform.getOrigin();

			//ジャンプ上昇中の場合
			if (m_JumpTime > 0)
			{
				//上昇時間減少
				m_JumpTime--;

				//ジャンプ力計算
				Vector3 jumpImpulse = actor3D->GetUp() * JUMP_POWER;

				//ジャンプ力に応じたインパルスを与える
				m_RigidBody->body->applyImpulse(btVector3{ jumpImpulse.x,jumpImpulse.y ,jumpImpulse.z }, m_RigidBody->body->getWorldTransform().getOrigin());

			}

			//オーナーの座標を設定
			actor3D->SetPosition(Vector3{ btPosition.x(),btPosition.y(),btPosition.z() });
		}
	}
}

//=============================================================================
// 剛体座標取得関数
//=============================================================================
Vector3 Component_Rigidbody::GetPosition()
{
	//戻り値用変数
	Vector3 value = { 0.0f,0.0f,0.0f };

	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//剛体の座標取得
		btVector3 btPosition = m_RigidBody->body->getWorldTransform().getOrigin();

		//戻り値に剛体の座標を設定
		value = Vector3{ btPosition.x(),btPosition.y(),btPosition.z() };

	}

	return value;
}

//=============================================================================
// 剛体スケール設定関数
//=============================================================================
void Component_Rigidbody::SetScale(const Vector3& _scale)
{
	//引数を代入
	m_Scale = _scale;

	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//剛体のスケールを上書き
		m_RigidBody->body->getCollisionShape()->setLocalScaling(btVector3{ _scale.x,_scale.y,_scale.z });
	}

}

//=============================================================================
// 剛体XZ軸移動関数
//=============================================================================
void Component_Rigidbody::SetMoveXZ(const Vector3& _velocity)
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//Y軸以外にインパルスを与える
		m_RigidBody->body->applyImpulse(btVector3{_velocity.x,m_RigidBody->body->getLinearVelocity().y(),_velocity.z }, m_RigidBody->body->getWorldTransform().getOrigin());
	}
}

//=============================================================================
// 剛体XYZ軸移動関数
//=============================================================================
void Component_Rigidbody::SetMoveXYZ(const Vector3& _velocity)
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//インパルスを与える
		m_RigidBody->body->applyImpulse(btVector3{ _velocity.x,_velocity.y,_velocity.z }, m_RigidBody->body->getWorldTransform().getOrigin());
	}
}

//=============================================================================
// 剛体重力設定関数
//=============================================================================
void Component_Rigidbody::SetGravity(const Vector3& _velocity)
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//重力設定
		m_RigidBody->body->setGravity(btVector3{ _velocity.x,_velocity.y,_velocity.z });
	}
}

//=============================================================================
// 剛体摩擦設定関数
//=============================================================================
void Component_Rigidbody::SetFriction(const float& _friction)
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//摩擦設定
		m_RigidBody->body->setFriction(_friction);
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void Component_Rigidbody::Jump()
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//ジャンプ上昇時間設定
		m_JumpTime = JUMP_UP_TIME;
	}
}
//=============================================================================
// ハイジャンプ関数
//=============================================================================
void Component_Rigidbody::HighJump()
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//ジャンプ上昇時間設定
		m_JumpTime = HIGH_JUMP_UP_TIME;
	}
}

//=============================================================================
// ワープ関数
//=============================================================================
void Component_Rigidbody::SetWarp(const Vector3& _position)
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//現在のトランスフォーム取得
		btTransform transform = m_RigidBody->body->getWorldTransform();

		//移動結果を計算し代入
		transform.setOrigin(btVector3{ _position.x,_position.y, _position.z });

		//トランスフォームの更新
		m_RigidBody->body->setWorldTransform(transform);
	}
}

//=============================================================================
// 速度取得関数
//=============================================================================
Vector3 Component_Rigidbody::GetVelociy()
{
	//剛体をnullチェック
	if (m_RigidBody != nullptr)
	{
		//速度取得
		btVector3 velocity = m_RigidBody->body->getLinearVelocity();
		return Vector3{ velocity.x(),velocity.y(),velocity.z() };
	}

	return Vector3 { 0.0f,0.0f,0.0f };
}

//=============================================================================
// スフィア型剛体追加関数
//=============================================================================
void  Component_Rigidbody::AddSphere(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//剛体をnullチェック
	if (m_RigidBody == nullptr)
	{
		//剛体マネージャーを取得出来た場合
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//スケール設定
			m_Scale = _scale;

			//スフィア型剛体追加
			m_RigidBody = manager_Rigidbody->AddSphere(_scale, _position, _mass);
		}
	}
}

//=============================================================================
// ボックス型剛体追加関数
//=============================================================================
void  Component_Rigidbody::AddBox(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//剛体をnullチェック
	if (m_RigidBody == nullptr)
	{
		//剛体マネージャーを取得出来た場合
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//スケール設定
			m_Scale = _scale;

			//ボックス型剛体追加
			m_RigidBody = manager_Rigidbody->AddBox(_scale, _position, _mass);
		}
	}
}

//=============================================================================
// カプセル型剛体追加関数
//=============================================================================
void  Component_Rigidbody::AddCapsule(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass)
{
	//剛体をnullチェック
	if (m_RigidBody == nullptr)
	{
		//剛体マネージャーを取得出来た場合
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//スケール設定
			m_Scale = Vector3{ _radius,_height,_radius };

			//カプセル型剛体追加
			m_RigidBody = manager_Rigidbody->AddCapsule(_radius, _height, _position, _rotation, _mass);
		}
	}
}

//=============================================================================
// 平面型剛体追加関数
//=============================================================================
void Component_Rigidbody::AddStaticPlane(const Vector3& _up, const Vector3& _position, float _mass)
{
	//剛体をnullチェック
	if (m_RigidBody == nullptr)
	{
		//剛体マネージャーを取得出来た場合
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//平面型剛体追加
			m_RigidBody = manager_Rigidbody->AddStaticPlane(_up, _position, _mass);
		}
	}
}