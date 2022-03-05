//=============================================================================
//
//  弾クラスマネージャー [Manager_Bullet.h]
//  Date   : 2022/1/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "Base/Manager_Actor.h"
#include "../../System/Main.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Bullet : public Manager_Actor
{
private:

	//オブジェクトプール
	std::vector<class Bullet*>m_Bullets;

public:

	//初期化・終了・更新
	void Init() override;
	void Uninit()override;
	void Update()override {};

	//生成
	void SpawnBullet(Vector3 _poition, Vector3 _velocity, Vector3 _rotation);

};