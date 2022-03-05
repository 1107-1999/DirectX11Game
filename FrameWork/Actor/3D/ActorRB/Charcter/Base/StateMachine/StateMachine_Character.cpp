////=============================================================================
//
//  キャラクターステートマシン [StateMachine_Character.cpp].
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "StateMachine_Character.h"
#include "State/CharacterState_Idle.h"
#include "State/CharacterState_Jump_Start.h"
#include "State/CharacterState_Jump_Loop.h"
#include "State/CharacterState_Fall.h"
#include "State/CharacterState_Walk.h"
#include "State/CharacterState_Sprint.h"

//=============================================================================
// 初期化関数
//=============================================================================
void StateMachine_Character::Init(Character* _owner)
{
	//オーナー代入
	m_Owner = _owner;

	//ステートを配列に格納
	m_CharacterStates.push_back(new CharacterState_Idle);
	m_CharacterStates.push_back(new CharacterState_Jump_Start);
	m_CharacterStates.push_back(new CharacterState_Jump_Loop);
	m_CharacterStates.push_back(new CharacterState_Fall);
	m_CharacterStates.push_back(new CharacterState_Walk);
	m_CharacterStates.push_back(new CharacterState_Sprint);

	//初期ステートはアイドル
	SetState<CharacterState_Idle>();

}

//=============================================================================
// 更新関数
//=============================================================================
void StateMachine_Character::Update()
{
	//現在の状態をnullチェック
	if (m_CharacterState != nullptr)
	{
		//更新
		m_CharacterState->Update();
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void StateMachine_Character::Uninit()
{
	//全状態を削除
	for (CharacterState* state : m_CharacterStates)
	{
		delete state;
		state = nullptr;
	}

	//状態配列ののクリア
	m_CharacterStates.clear();

}

//=============================================================================
//　軸移動関数
//=============================================================================
void StateMachine_Character::MoveAxis(float _forward_value, float _right_value)
{
	//現在の状態をnullチェック
	if (m_CharacterState != nullptr)
	{
		//軸移動
		m_CharacterState->MoveAxis(_forward_value,_right_value);
	}
}

//=============================================================================
//　スプリント関数
//=============================================================================
void StateMachine_Character::Sprint(bool _input)
{
	//現在の状態をnullチェック
	if (m_CharacterState != nullptr)
	{
		//スプリント処理
		m_CharacterState->Sprint(_input);
	}
}

//=============================================================================
//　ジャンプ関数
//=============================================================================
void StateMachine_Character::Jump()
{
	//現在の状態をnullチェック
	if (m_CharacterState != nullptr)
	{
		//ジャンプ処理
		m_CharacterState->Jump();
	}
}
