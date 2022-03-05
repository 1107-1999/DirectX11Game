//=============================================================================
//
//   弾クラス [Bullet.h]
//  Date   : 2021/1/10
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../Base/Actor3D.h"

//=============================================================================
// クラス宣言
//=============================================================================
class Bullet : public Actor3D
{
private:

	//静的メッシュコンポーネント
	class Component_StaticMesh*   m_Component_StaticMesh;

	//生存時間カウント
	int m_LifeTime = 0;

	//有効フラグ
	bool m_Active;     

	//速度
	Vector3 m_Velocity;

public:

	//初期化・更新
	void Init()override;
	void Update()override;

	//弾生成
	void SpawnBullet(Vector3 _position, Vector3 _velocity, Vector3 _rotation);

	//使用可能フラグ取得
	inline bool GetActive()const { return m_Active; }

};