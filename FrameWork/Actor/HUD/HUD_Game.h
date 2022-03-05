//=============================================================================
//
//  ゲームレベル用HUDクラス [HUD_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/HUD.h"

//=============================================================================
// クラス定義
//=============================================================================
class HUD_Game : public HUD
{
private:

	//ポリゴン描画機構クラスキャッシュ
	class Renderer_Polygon*    m_Renderer_Polygon;

	//2Dマネージャーフォントキャッシュ
	class Manager_Font2D*      m_Manager_Font2D;

	//プレイヤーコントローラーキャッシュ
	class PC_Game*             m_PlayerConroller;

	//スコープUI用スプライトコンポーネント
	class Component_Sprite*    m_Component_Sprite_Scope;


public:

	//初期化・終了・更新
	void Init()  override;
	void Update()override;
	void Uninit()override;

	//描画
	void Draw()override;

	//スコープのUIを設定
	void SetScopeUI(bool _flag);

};