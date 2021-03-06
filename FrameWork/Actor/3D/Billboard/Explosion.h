//=============================================================================
//
//  爆発ビルボードエフェクトクラス [Explosion.h]
//  Date   : 2022/1/26
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
class Explosion : public Actor3D
{
private:

	//ビルボードコンポーネント
	class Component_Billboard*    m_Component_Billboard;  

public:

	//リソース読み込み・削除
	 static void Load();
	 static void Unload();

	 //初期化
	 void Init()override;

	 //再生
	 void Play();

};