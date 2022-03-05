//=============================================================================
//
// 動的レベルデザイン用キューブクラス [Cube_LD_Movable.h]
//  Date   : 2021/1/23
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Cube_LD.h"

//=============================================================================
// クラス
//=============================================================================
class Cube_LD_Movable : public Cube_LD
{
private:

	//1フレーム前の座標
	Vector3 m_OldPosition = Vector3_Zero;

	//開始座標
	Vector3 m_Start    = Vector3_Zero;

	//目標座標
	Vector3 m_Target   = Vector3_Zero;

	//速度
	Vector3 m_Velocity = Vector3_Zero;


public:

	//初期化・更新
	void Init()override;
	void Update()override;

	//目標位置設定
	inline void SetTarget(Vector3 _target) { m_Target = _target, m_Start = m_Position;}

	//速度設定
	inline void SetVelocity(Vector3 _velocity) { m_Velocity = _velocity; }
};