//=============================================================================
//
// 銃のテーブルクラス [GunTable.h]
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
class GunTable : public ActorRB
{
private:

	//静的メッシュコンポーネント
	class Component_StaticMesh* m_Component_StaticMesh;

public:

	//初期化関数
	virtual void Init()override;

};