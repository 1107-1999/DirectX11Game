//=============================================================================
//
//  銃クラス [Gun.h]
//  Date   : 2021/1/25
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../Base/Actor3D.h"

//=============================================================================
// クラス宣言
//=============================================================================
class Gun : public Actor3D
{
private:

	//コンポーネント
	class Component_StaticMesh* m_Component_StaticMesh;	//静的メッシュコンポーネント
	class Component_OBB*        m_Component_OBB;	    //OBBコンポーネント


	//弾管理クラス
	class Manager_Bullet* m_Manager_Bullet;

	//銃声クラス
	class GunFire* m_GunFire;

	//プレイヤーコントローラーキャッシュ
	class PC_Game*    m_PlayerConroller;

	//リコイルカウント
	int m_RecoilCount;

	//リコイル右向きか
	bool  m_RecoilVectorRight;

public:

	//リソース読み込み・削除
	static void Load();
	static void Unload();

	//初期化・更新・終了
	virtual void Init()override;
	virtual void Update()override;
	virtual void Uninit()override;

	//射撃
	void Shot();

};