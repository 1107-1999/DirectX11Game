//=//=============================================================================
//
//  ゲームシーン用プレイヤーコントローラー [PC_Game.h]
//  Date   : 2021/1/22
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/PlayerController.h"

//=============================================================================
// クラス定義
//=============================================================================
class PC_Game : public PlayerController
{
private:

	//フラグ
	bool m_GunFlag;   //銃接触フラグ
	bool m_ScopeFlag; //スコープ使用フラグ
	bool m_ShotFlag;  //射撃フラグ
	bool m_GoalFlag;  //ゴールフラグ

	//線形補間比率
	float m_LerpRate;

public:

	void Init()override;
	void Update()override;

	//銃接触フラグ取得・設定
	inline bool GetGunFlag()const  { return m_GunFlag; }
	inline void SetGunFlag(bool _flag) { m_GunFlag = _flag; }

	//ゴールフラグチェック
	inline bool GetGoalFlag()const { return m_GoalFlag; }
	inline void SetGoalFlag(bool _flag) { m_GoalFlag = _flag; }

	//スコープ使用フラグ取得・設定
	inline bool GetScopeFlag()const{ return m_ScopeFlag; }

};
