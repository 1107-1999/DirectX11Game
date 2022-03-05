//=============================================================================
//
//  キャラクター歩き状態 [CharacterState_Walk.h]
//  Date   : 2021/11/28
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/CharacterState.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CharacterState_Walk : public CharacterState
{
private:

	//キーフレームイベント用のフレーム
	int m_Frame;

public:

	//初期化・更新・終了
	void Init(Character* _owner)override;
	void Update()override;
	void Uninit()override;

	//軸移動
	void MoveAxis(float _forward_value, float _right_value)override;

	//ジャンプ
	void Jump()override;

	//スプリント
	void Sprint(bool _input)override;

};