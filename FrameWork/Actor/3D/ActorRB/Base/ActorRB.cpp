//=============================================================================
//
//  剛体アクター基底クラス [ActorRB.cpp]
//  Date   : 2021/11/26
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ActorRB.h"

//=============================================================================
// 初期化関数
//=============================================================================
void  ActorRB::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//剛体コンポーネント追加
	m_Component_Rigidbody = AddComponent<Component_Rigidbody>(0);

	//OBBコンポーネント追加(オーバーラップ判定用)
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//可視性設定
		m_Component_OBB->SetVisibility(true);
		//スケール設定
		m_Component_OBB->SetScale(m_Scale);
	}

}

//=============================================================================
// 剛体座標設定関数
//=============================================================================
void ActorRB::SetRigidbodyPosition(Vector3 _position)
{
	//基礎座標設定
	m_Position = _position;

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->SetWarp(m_Position);
	}

}

//=============================================================================
// 剛体スケール設定関数
//=============================================================================
void ActorRB::SetRigidbodyScale(Vector3 _scale)
{

	//基礎スケールを設定
	m_Scale = _scale;

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->SetScale(m_Scale);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(m_Scale);
	}

}


//=============================================================================
// スフィア型剛体追加関数(引数は大きさ・座標・質量)
//=============================================================================
void ActorRB::AddSphereRB(const Vector3& _scale, const Vector3& _position, float _mass)
{

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddSphere(HalfSize(_scale), _position, _mass);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(_scale);
	}

}

//=============================================================================
// ボックス型剛体追加(引数は大きさ・座標・質量)
//=============================================================================
void ActorRB::AddBoxRB(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddBox(HalfSize(_scale), _position, _mass);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(_scale);//スケール設定
	}

}

//=============================================================================
// カプセル型剛体追加(引数は半径・高さ・座標・回転・質量)
//=============================================================================
void ActorRB::AddCapsuleRB(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass)
{

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddCapsule(HalfSize(_radius), HalfSize(_height),_position,_rotation,_mass);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(Vector3{ _radius,_height,_radius });//スケール設定
	}

}