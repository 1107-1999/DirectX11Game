//=============================================================================
//
//  キャラクタージャンプ中状態 [CharacterState_Jump_Loop.h]
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
class CharacterState_Jump_Loop : public CharacterState
{

private:

	//ジャンプ中の移動速度を保存
	float m_KeepVelocity;

	//スプリントフラグ
	bool  m_Sprint;      

	//レイの無視レイヤーのリスト
	std::list<ACTOR_TYPE>m_IgnoreList;

public:
	
	//初期化・更新・終了
	void Init(Character* _owner)override;
	void Update()override;
	void Uninit()override;

	//スプリント
	void Sprint(bool _input)override;

	//ジャンプ不可
	void Jump()override {};
};