//=============================================================================
//
//  キャラクター棒立ち状態 [CharacterState_Idle.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Jump_Start.h"
#include "CharacterState_Jump_Loop.h"
#include "CharacterState_Fall.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Idle::Init(Character* _owner)
{
	//基底クラス初期化
	CharacterState::Init(_owner);

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド先のアニメを棒立ちアニメに設定
		component_SkeletalMesh->SetNextAnimationName("Idle");

	}

	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//速度を停止判定速度に設定
		m_Owner->SetPlayerVelocity(STOP_VELOCITY);

	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Idle::Update()
{
	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//todo放置モーション

		//真下にレイを飛ばして接地していなかった場合
		if (!m_Owner->GetComponentByClass<Component_OBB>()->Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true).isHIT)
		{
			//ジャンプせずに空中にいるため落下状態に遷移
			m_Owner->GetStateMachine()->SetState<CharacterState_Fall>();
		}

	}
}

//=============================================================================
// 終了関数
//=============================================================================
void CharacterState_Idle::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド元のアニメを棒立ちアニメに設定
		component_SkeletalMesh->SetCurrentAnimationName("Idle");
	}
}

//=============================================================================
// 軸移動関数
//=============================================================================
void CharacterState_Idle::MoveAxis(float _forward_value, float _right_value)
{
	//軸入力がされている場合
	if (fabsf(_forward_value) + fabsf(_right_value) >= STOP_VELOCITY)
	{
		//歩き状態に遷移
		m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void CharacterState_Idle::Jump()
{
	//基底クラスジャンプ処理
	CharacterState::Jump();

	//ジャンプ開始状態に遷移
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();

}
