//=============================================================================
//
//  キャラクター走り状態 [CharacterState_Run.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Sprint.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Fall.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr int KEY_FRAME   =  5;//キーフレーム
constexpr int FRAME_RESET = 15;//フレームリセット時間

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Sprint::Init(Character* _owner)
{

	//基底クラス初期化
	CharacterState::Init(_owner);

	//フレーム初期化
	m_Frame = 0;

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド先のアニメを走りアニメに設定
		component_SkeletalMesh->SetNextAnimationName("Run");

	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Sprint::Update()
{
	if (m_Owner != nullptr)
	{
		//速度設定(歩き以上走り未満にクランプ)
		m_Owner->SetPlayerVelocity(Math::clamp(m_Owner->GetPlayerVelocity() + ONE_FRAME_UP_VELOCITY, MAX_WALK_VELOCITY, MAX_SPRINT_VELOCITY));

		//プレイヤーの足元にレイを飛ばして接地を判定する
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
			//物理マテリアルに応じた足音を再生
			m_Owner->PlayFootStep(hit_result.physicsMaterial);

			//服の音を再生
			m_Owner->PlayClothSound();

		}
		//最大フレーム到達時
		else if (m_Frame == FRAME_RESET)
		{
			//アクセサリ音を再生
			m_Owner->PlayClothSoundMetal();
			//フレーム初期化
			m_Frame = 0;
		}

	}
}

//=============================================================================
// 終了関数
//=============================================================================
void CharacterState_Sprint::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())

	{	//ブレンド元のアニメを走りアニメに設定
		component_SkeletalMesh->SetCurrentAnimationName("Run");

	}
}

//=============================================================================
// 軸移動関数
//=============================================================================
void CharacterState_Sprint::MoveAxis(float _forward_value, float _right_value)
{
	//軸入力がされていない場合
	if (fabsf(_forward_value) + fabsf(_right_value) <= STOP_VELOCITY)
	{
		//棒立ち状態に遷移
		m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
	}
	else
	{//軸入力がされている場合

		//軸移動処理
		CharacterState::MoveAxis(_forward_value, _right_value);

	}
}

//=============================================================================
// スプリント関数
//=============================================================================
void  CharacterState_Sprint::Sprint(bool _input)
{
	//スプリント命令をされていない場合
	if (!_input)
	{
		//歩き状態に遷移
		m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void CharacterState_Sprint::Jump()
{
	//剛体コンポーネントをnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//ハイジャンプ処理
		m_Component_Rigidbody->HighJump();
	}

	//ジャンプ開始状態に遷移
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();
}