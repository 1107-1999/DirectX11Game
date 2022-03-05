//=============================================================================
//
//  キャラクター基底クラス [Character.h]
//  Date   : 2021/11/4
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../Base/ActorRB.h"
#include "../../../../../PlayerController/Base/PlayerController.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float MAX_WALK_VELOCITY   = 60.0f;  //歩き移動速度
constexpr float MAX_SPRINT_VELOCITY = 90.0f;  //走り移動速度

//=============================================================================
// クラス宣言
//=============================================================================
class Character : public ActorRB
{
protected:

	//スケルタルメッシュコンポーネント
	class Component_SkeletalMesh*  m_Component_SkeletalMesh;         

	//ステートマシン
	class StateMachine_Character*  m_StateMachine;

	//移動速度
	float m_PlayerVelocity;

	//足音クラス
	class FootStep* m_FootStep;

	//服の音クラス
	class Cloth*    m_ClothSounds;
	
public:

	//リソース読み込み・削除
	static void Load();
	static void Unload();

	//初期化・更新・終了
	virtual void Init()  override;
	virtual void Update()override;
	virtual void Uninit()override;

	//軸移動
	void MoveAxis(float _forward_value, float _right_value);

	//回転
	void MoveRotation(float _mouseX);

	//スプリント
	void Sprint(bool _input);

	//ジャンプ
	void Jump();

	//足音再生
	void PlayFootStep(int _physicsMaterial);

	//服の音再生
	void PlayClothSound();

	//アクセサリ音再生
	void PlayClothSoundMetal();

	//ステートマシン取得
	inline StateMachine_Character* GetStateMachine() const{ return m_StateMachine; }

	//移動速度取得・設定
	inline float GetPlayerVelocity() const { return m_PlayerVelocity; }
	inline void  SetPlayerVelocity(float _value){  m_PlayerVelocity = _value; }

};