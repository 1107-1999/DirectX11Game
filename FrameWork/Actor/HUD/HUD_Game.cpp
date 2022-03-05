//=============================================================================
//
//  ゲームレベル用HUDクラス [HUD_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "HUD_Game.h"
#include "../../Component/Component_Sprite.h"
#include "../../Manager/Manager_Drawer/Manager_Font2D.h"
#include "../../Manager/Manager_Game.h"
#include "../../Manager/Manager_Texture.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/MainWindow.h"
#include "../../PlayerController/PC_Game.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float LERP_SPEED = 0.085f;//補間速度
constexpr float LERP_START = 0.01f; //補間開始
constexpr float LERP_END   = 0.99f; //補間終了

//=============================================================================
// 初期化
//=============================================================================
void HUD_Game::Init()
{
	//テクスチャーマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//スコープテクスチャ読み込み
		manager_Texture->LoadTexture("Scope", "ROM\\2D\\Gun\\T_Scope.png");
	}

	//スコープUI用スプライトコンポーネント設定
	m_Component_Sprite_Scope = AddComponent<Component_Sprite>(0);//追加

		//スコープUI用スプライトコンポーネントnullチェック
	if (m_Component_Sprite_Scope != nullptr)
	{
		m_Component_Sprite_Scope->SetTexture("Scope");	//テクスチャー設定
		m_Component_Sprite_Scope->SetPosition2D(Vector2_Zero);//座標オフセット調整
		m_Component_Sprite_Scope->SetActive(false);//初期設定では非表示

		//windowサイズ取得
		Int2 windowSize = MainWindow::Instance()->GetWindowSize();
		//スケールをwindowサイズに設定
		m_Component_Sprite_Scope->SetScale2D(Vector2{ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
	}

	
	//プレイヤーコントローラーを取得&キャストしてキャッシュ
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());


	//2Dフォントマネージャーキャッシュキャッシュ
	if (m_Manager_Font2D = Manager_Font2D::Instance())
	{
		//中心ぞろえ
		m_Manager_Font2D->SetAilgningMode(Manager_Font::e_Aligning::center);

		//フォント設定
		m_Manager_Font2D->SetFont(L"02UtsukushiMincho", L"02うつくし明朝体");

		//文字の間隔
		m_Manager_Font2D->SetCharLength(1.0f);

		//フォントサイズ設定
		m_Manager_Font2D->SetFontSize(64);

		//イタリック体使用しない
		m_Manager_Font2D->SetIsUseItalic(false);

		//文字の太さ
		m_Manager_Font2D->SetFontWeight(FW_DONTCARE);

		//白色
		m_Manager_Font2D->SetFontColor(Color(1, 1, 1, 1));
	}

	//ポリゴン描画機構クラスキャッシュ
	m_Renderer_Polygon = Renderer_Polygon::Instance();

}

//=============================================================================
// 更新関数
//=============================================================================
void HUD_Game::Update()
{
	//親クラス更新
	HUD::Update();
}

//=============================================================================
// 終了関数
//=============================================================================	
void HUD_Game::Uninit()
{

	//テクスチャーマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//スコープテクスチャ削除
		manager_Texture->UnloadTexture("Scope");
	}

	//親クラス終了
	HUD::Uninit();
}
//=============================================================================
// 描画関数
//=============================================================================
void HUD_Game::Draw()
{
	//2Dフォントマネージャーとポリゴン描画機構クラスnullチェック
	if (m_Manager_Font2D != nullptr && m_Renderer_Polygon != nullptr)
	{
		//銃衝突フラグが立っている場合
		if (m_PlayerConroller->GetGunFlag() && !m_PlayerConroller->GetScopeFlag())
		{
			//UI描画(引数は座標・スケール・色)
			m_Renderer_Polygon->DrawBox2D(Vector2{ 400.0f, -256.0f }, Vector2{ 400.0f,200.0f }, Color{0.0f,0.0f,0.0f,0.75f});

			//テキスト描画(引数は座標)
			m_Manager_Font2D->Printf2D({ 200.0f, -290.0f }, "右クリック:ADS");

		}
		//ゴールフラグが立っている場合
		if (m_PlayerConroller->GetGoalFlag())
		{
			//UI描画(引数は座標・スケール・色)
			m_Renderer_Polygon->DrawBox2D(Vector2{ 400.0f, -256.0f }, Vector2{ 600.0f,200.0f }, Color{ 0.0f,0.0f,0.0f,0.75f });

			//テキスト描画(引数は座標)
			m_Manager_Font2D->Printf2D({ 200.0f, -290.0f }, "左クリック:スタートに戻る");
		}
	}
}

//=============================================================================
// スコープUI設定関数
//=============================================================================
void HUD_Game::SetScopeUI(bool _flag)
{
	//スコープUI用スプライトコンポーネント
	if (m_Component_Sprite_Scope != nullptr)
	{
		//描画フラグ設定
		m_Component_Sprite_Scope->SetActive(_flag);
	}
}
