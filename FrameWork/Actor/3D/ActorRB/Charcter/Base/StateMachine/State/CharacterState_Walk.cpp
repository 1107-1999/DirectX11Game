//=============================================================================
//
//  キャラクター歩き状態 [CharacterState_Walk.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Walk.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Sprint.h"
#include "CharacterState_Fall.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_OBB.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr int KEY_FRAME   = 5; //キーフレーム
constexpr int KEY_FRAME2  = 15; //キーフレーム2
constexpr int FRAME_RESET = 30;//フレームリセット時間

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Walk::Init(Character* _owner)
{

	//基底クラス初期化
	CharacterState::Init(_owner);

	//フレーム初期化
	m_Frame = 0;

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{	
		//ブレンド先のアニメを歩きアニメに設定
		component_SkeletalMesh->SetNextAnimationName("Walk");

	}

}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Walk::Update()
{
	if (m_Owner != nullptr)
	{
		//速度設定(停止判定速度以上、歩き最大速度以下にクランプ)
		m_Owner->SetPlayerVelocity(Math::clamp(m_Owner->GetPlayerVelocity() + ONE_FRAME_UP_VELOCITY, STOP_VELOCITY, MAX_WALK_VELOCITY));

		//接地を判定
		s_HIT_Result hit_result = m_Owner->GetComponentByClass<Component_OBB>()->Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true);

		//接地していない場合
		if (!hit_result.isHIT)
		{
			//ジャンプせずに空中にいるため落下状態に遷移
			m_Owner->GetStateMachine()->SetState<CharacterState_Fall>();

		}

		//キーフレームイベント用フレーム加算
		m_Frame++;

		//キーフレームイベント
		if (m_Frame == KEY_FRAME)
		{
			//物理マテリアルに応じた足音
			m_Owner->PlayFootStep(hit_result.physicsMaterial);
		}
		//キーフレームイベント2
		else if (m_Frame == KEY_FRAME2)
		{
			//服の音を再生
			m_Owner->PlayClothSound();

		}
		//最大フレーム到達時
		else if (m_Frame == FRAME_RESET)
		{
			//アクセサリ音を再生
			m_Owner->PlayClothSoundMetal();

			//フレームをリセット
			m_Frame = 0;
		}
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void CharacterState_Walk::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド元のアニメを歩きに設定
		component_SkeletalMesh->SetCurrentAnimationName("Walk");
	}
}

//=============================================================================
// 軸移動関数
//=============================================================================
void CharacterState_Walk::MoveAxis(float _forward_value, float _right_value)
{
	//軸入力がされていない場合
	if (fabsf(_forward_value) + fabsf(_right_value) <= STOP_VELOCITY)
	{
		//棒立ち状態に遷移
		m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
	}
	else
	{//軸入力がされている場合

		//軸移動
		CharacterState::MoveAxis(_forward_value, _right_value);
	}
}

//=============================================================================
// スプリント関数
//=============================================================================
void  CharacterState_Walk::Sprint(bool _input)
{
	//スプリント命令をされている場合
	if (_input)
	{
		//走り状態に遷移
		m_Owner->GetStateMachine()->SetState<CharacterState_Sprint>();
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void CharacterState_Walk::Jump()
{
	//基底クラスジャンプ処理
	CharacterState::Jump();

	//ジャンプ開始状態に遷移
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();

}