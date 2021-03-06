//=============================================================================
//
// レベルデザイン用キューブクラス [Cube_LD.h]
//  Date   : 2021/1/19
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
class Cube_LD : public ActorRB
{
protected:

	//キューブコンポーネント
	class Component_Cube* m_Component_Cube;

public:

	//リソース読み込み・削除
	static void Load();
	static void Unload();

	//初期化
	void Init()override;

};