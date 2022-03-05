//=============================================================================
//
//  キャラクターステートマシン [StateMachine_Character.h]
//  Date   : 2021/11/28
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <vector>
#include <typeinfo>
#include "State/Base/CharacterState.h"

//=============================================================================
// クラス定義
//=============================================================================
class StateMachine_Character
{
private:

	//オーナー
	class Character* m_Owner;

	//オーナーの現在の状態
	class CharacterState* m_CharacterState = nullptr;

	//オーナーの状態配列
	std::vector<class CharacterState*> m_CharacterStates;

public:

	//初期化・更新・終了
	void Init(Character* _owner);
	void Update();
	void Uninit();

	//軸移動
	void MoveAxis(float _forward_value, float _right_value);

	//スプリント
	void Sprint(bool _input);

	//ジャンプ
	void Jump();

	//=============================================================================
	// 状態設定関数
	//=============================================================================
	template<typename T>
	inline void SetState()
	{
		//現在の状態が存在する場合
		if (m_CharacterState != nullptr)
		{
			//終了処理
			m_CharacterState->Uninit();
			m_CharacterState = nullptr;
		}

		//状態配列から指定の状態を検索
		for (CharacterState* state : m_CharacterStates)
		{
			if (typeid(*state) == typeid(T))
			{
				//指定の状態に遷移
				m_CharacterState = state;

				//初期化関数
				m_CharacterState->Init(m_Owner);
			}
		}
	}

	//状態取得
	inline CharacterState* GetCharacterState() { return m_CharacterState; }
};

