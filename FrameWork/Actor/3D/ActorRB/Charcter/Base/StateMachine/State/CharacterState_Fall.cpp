//=============================================================================
//
//  キャラクター落下状態 [CharacterState_Fall.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Fall.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Sprint.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Fall::Init(Character*  _owner)
{
	//基底クラス初期化
	CharacterState::Init(_owner);

	//スプリントフラグ初期化
	m_Sprint = false;

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド先のアニメを落下アニメに設定
		component_SkeletalMesh->SetNextAnimationName("Fall");

	}

	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//速度設定
		(m_KeepVelocity < MAX_WALK_VELOCITY) ? m_KeepVelocity = MAX_WALK_VELOCITY : m_KeepVelocity = m_Owner->GetPlayerVelocity();

		//服の音を再生
		m_Owner->PlayClothSound();

	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Fall::Update()
{
	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//プレイヤーの足元にレイを飛ばして接地を判定する
		s_HIT_Result hit_result = m_Owner->GetComponentByClass<Component_OBB>()->
			Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true,
			std::list<ACTOR_TYPE>(),//自身を無視
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
void CharacterState_Fall::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド元のアニメを落下アニメに設定
		component_SkeletalMesh->SetCurrentAnimationName("Fall");
	}
}

//=============================================================================
// スプリント関数
//=============================================================================
void CharacterState_Fall::Sprint(bool _input)
{
	//スプリントのキーが押されているかどうかを確認
	m_Sprint = _input;
}
