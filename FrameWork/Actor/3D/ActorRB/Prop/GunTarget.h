//=============================================================================
//
// 銃のターゲットクラス [GunTarget.h]
//  Date   : 2021/1/25
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../Base/ActorRB.h"

//=============================================================================
// クラス宣言
//=============================================================================
class GunTarget : public ActorRB
{
private:

	//静的メッシュコンポーネント
	class Component_StaticMesh* m_Component_StaticMesh;

	//爆発エフェクトクラス
	class Explosion* m_Explosion;

	//進行方向
	bool m_Vector;

	//速度
	float m_Velocity;


public:

	//初期化・更新
	void Init()override;
	void Update()override;

	//速度設定
	inline void SetVelocity(float _velocity) { m_Velocity = _velocity; }

	//進行方向設定
	inline void SetVector(bool _vector) { m_Vector = _vector; }
};