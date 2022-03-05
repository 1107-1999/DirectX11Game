//=============================================================================
//
//  OBBコンポーネント [Component_OBB.cpp]
//  Author : Ryosuke Kotera
//  Date   : 2021/10/18
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <math.h>
#include "Component_OBB.h"
#include "../Level/Base/Level.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"
#include "../Manager/Manager_Game.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Actor/3D/Base/Actor3D.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/3D/ActorRB/Prop/Bullet.h"
#include "../Actor/3D/ActorRB/Prop/GunTarget.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/Prop/Gun.h"
#include "../Actor/3D/Prop/Goal.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float HALF_SIZE = 0.5f;

//=============================================================================
// 初期化関数
//=============================================================================
void Component_OBB::Init()
{
	//基底クラス初期化
	Component::Init();

	//デフォルトはアンリットシェーダー
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//色を白に設定
	m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

	//デバッグコリジョン描画しない
	m_Visibility = true;

	//レイに反応するか
	m_isReactRay = true;

	//物理マテリアル設定(初期はコンクリート)
	m_PhysicsMaterial = PM_CONCRETE;

	//重なっているか
	m_isOverlap = false;

	//座標オフセット初期化
	m_PositionOffset = Vector3_Zero;

	//Actor3Dにキャスト成功した場合
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{

		//オーナー情報取得
		m_Position = actor3D->GetPosition();//座標
		m_Rotation = actor3D->GetRotation();//回転
		m_Scale    = actor3D->GetScale();   //スケール

		//OBBマネージャーキャッシュ
		m_Manager_OBB = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_OBB();

		///todo：クラスとリファレンスを持たずに自分で好きなタイミングでコリジョンチャンネルに登録できるようにする///

		//OBBマネージャーnullチェック
		if (m_Manager_OBB != nullptr)
		{
			//オーナーのタイプ別にコリジョンチャンネルに登録

			if (Camera* camera = dynamic_cast<Camera*>(actor3D))
			{//カメラ
				m_Manager_OBB->AddComponent(this, COLLISION_CAMERA);
			}
			else if (Character* character = dynamic_cast<Character*>(actor3D))
			{//キャラクター
				m_Manager_OBB->AddComponent(this, COLLISION_PLAYER);
			}
			else if (Gun* gun = dynamic_cast<Gun*>(actor3D))
			{//銃
				m_Manager_OBB->AddComponent(this, COLLISION_GUN);
			}
			else if (Bullet* bullet = dynamic_cast<Bullet*>(actor3D))
			{//弾
				m_Manager_OBB->AddComponent(this, COLLISION_BULLET);
			}
			else if (Goal* goal = dynamic_cast<Goal*>(actor3D))
			{//ゴール
				m_Manager_OBB->AddComponent(this, COLLISION_GOAL);
			}
			else if (GunTarget* gunTarget = dynamic_cast<GunTarget*>(actor3D))
			{//ターゲット
				m_Manager_OBB->AddComponent(this, COLLISION_GUN_TARGET);
			}
			else
			{//ブロック
				m_Manager_OBB->AddComponent(this, COLLISION_BLOCK);
			}
		}
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void Component_OBB::Update()
{

	//Actor3Dにキャスト成功した場合
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{//オーナー情報取得

		//座標取得
		m_Position = actor3D->GetPosition() + m_PositionOffset;

		//回転取得
		m_Rotation = actor3D->GetRotation();

		//色を白に設定
		m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

		//オーバーラップ判定リセット
		m_isOverlap = false;

		//マトリクス計算
		D3DXMATRIX rot, scale, world;

		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		world = scale * rot;

		//OBB計算
		m_NormaDirectionX = Vector3{ world._11 ,world._12,world._13} *HALF_SIZE;
		m_NormaDirectionY = Vector3{ world._21 ,world._22,world._23} *HALF_SIZE;
		m_NormaDirectionZ = Vector3{ world._31 ,world._32,world._33} *HALF_SIZE;

	    //OBBの線分の長さ計算
		m_LengthX = D3DXVec3Length(&m_NormaDirectionX);
		m_LengthY = D3DXVec3Length(&m_NormaDirectionY);
		m_LengthZ = D3DXVec3Length(&m_NormaDirectionZ);

	}
}

//=============================================================================
// 描画関数
//=============================================================================
void Component_OBB::Draw()
{
	//描画モードオンの時
	if (m_Visibility)
	{
		//Actor3Dにキャストに成功した場合
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//シェーダー設定
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			//ワイヤーフレーム化
			Renderer_DirectX11::Instance()->SetRasterizerState(D3D11_FILL_WIREFRAME);

			//ポリゴンレンダラーから描画
		    Renderer_Polygon::Instance()->DrawBox(m_Position, m_Rotation, m_Scale, m_Color);

			//ワイヤーフレーム解除
			Renderer_DirectX11::Instance()->SetRasterizerState(D3D11_FILL_SOLID);
		}
	}
}


//=============================================================================
// オーナーの座標設定関数
//=============================================================================
void Component_OBB::SetOwnerPosition(Vector3 position)
{
	//Actor3Dにキャストに成功した場合
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{
		actor3D->SetPosition(position);
	}
}

//=============================================================================
// レイキャスト関数
//=============================================================================
s_HIT_Result Component_OBB::Raycast(Vector3 _startPos, Vector3 _endPos,
	Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy,int _drawRayLife)
{
	//OBBマネージャーnullチェック
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->Raycast(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy ,_drawRayLife);
	}

	//HITしてない場合の値
	s_HIT_Result nohit;

	return nohit;
}

//=============================================================================
// 高精度レイキャスト関数(重め)
//=============================================================================
s_HIT_Result Component_OBB::RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
	Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//OBBマネージャーnullチェック
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->RaycastHighAccuracy(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy, _drawRayLife);
	}

	//HITしてない場合の値
	s_HIT_Result nohit;

	return nohit;
}

//=============================================================================
// 	レイキャスト関数(HITしたオブジェクト全てを配列にして返す)
//=============================================================================
std::vector<s_HIT_Result> Component_OBB::RaycastGetHit(Vector3 _startPos,
	Vector3 _endPos, Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//OBBマネージャーnullチェック
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->RaycastGetHit(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy, _drawRayLife);
	}

	return std::vector<s_HIT_Result>();
}

