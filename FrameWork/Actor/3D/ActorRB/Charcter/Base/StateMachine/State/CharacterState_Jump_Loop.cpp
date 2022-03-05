//=============================================================================
//
//  キャラクタージャンプ中状態 [CharacterState_Jump_Loop.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Jump_Loop.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Sprint.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Jump_Loop::Init(Character* _owner)
{

	//基底クラス初期化
	CharacterState::Init(_owner);

	//スプリントフラグ初期化
	m_Sprint = false;

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド先のアニメをジャンプ中アニメに設定
		component_SkeletalMesh->SetNextAnimationName("Jump_Loop");
	}

	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//最低速度補正
		(m_KeepVelocity < MAX_WALK_VELOCITY)? m_KeepVelocity = MAX_WALK_VELOCITY : m_KeepVelocity = m_Owner->GetPlayerVelocity();
	}

	//レイの無視レイヤーのリスト
	m_IgnoreList.push_back(ACTOR_TYPE::COLLISION_GOAL);
	m_IgnoreList.push_back(ACTOR_TYPE::COLLISION_GUN);

}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Jump_Loop::Update()
{

	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//速度設定(ジャンプ開始時から一定)
		m_Owner->SetPlayerVelocity(m_KeepVelocity);

		//プレイヤーの足元にレイを飛ばして接地を判定する
		s_HIT_Result hit_result = m_Owner->GetComponentByClass<Component_OBB>()->Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true,
			m_IgnoreList,//自身を無視
			Color(0, 1, 1, 1));//RGBAを水色に設定

		//接地している場合
		if (hit_result.physicsMaterial != INVALID_ID && hit_result.physicsMaterial != PM_IGNORE)
		{
			//物理マテリアルに応じた着地音を再生
			m_Owner->PlayFootStep(hit_result.physicsMaterial);

			if (m_Sprint)
			{//走り状態に遷移
				m_Owner->GetStateMachine()->SetState<CharacterState_Sprint>();
			}
			else if (m_KeepVelocity >= STOP_VELOCITY)
			{//歩き状態に遷移
				m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
			}
			else
			{//棒立ち状態に遷移
				m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
			}

		}
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void CharacterState_Jump_Loop::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド元のアニメをジャンプ中アニメに設定
		component_SkeletalMesh->SetCurrentAnimationName("Jump_Loop");
	}
}

//=============================================================================
// スプリント関数
//=============================================================================
void CharacterState_Jump_Loop::Sprint(bool _input)
{
	//スプリントのキーが押されているかどうかを確認
	m_Sprint = _input;
}