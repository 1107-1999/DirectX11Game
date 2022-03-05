//=============================================================================
//
//  ゲームマネージャー [Manager_Game.cpp]
//  Date   : 2021/11/02
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <time.h>
#include "Manager_Game.h"
#include "Manager_Texture.h"
#include "Manager_Shader.h"
#include "Manager_Drawer/Manager_ImGui.h"
#include "Manager_Drawer/Manager_Font2D.h"
#include "Manager_Font.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Level/Level_Game.h"
#include "../Level/Level_Title.h"
#include "../System/Input.h"
#include "../System/Main.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Manager_Game::Init()
{

	//各種ゲーム表現に必要なシングルトンマネージャー初期化
	Manager_Texture::Instance()->Init();  //テクスチャマネージャー初期化
	Manager_Shader::Instance()->Init();   //シェーダーマネージャー初期化
	Renderer_Polygon::Instance()->Init(); //ポリゴン描画機構初期化
	Manager_Font2D::Instance()->Init();   //2Dフォントマネージャー初期化

    //プレイヤーコントローラーにnull代入
	m_PlayerController = nullptr;      
	 
	//現在のレベルにnull代入
	m_Level = nullptr;

	//  次のレベルにnull代入
	m_NextLevel = nullptr;

	//ゲームシーンセット
	LoadLevelByClass<Level_Game>(30.0f);

}
//=============================================================================
// 更新関数
//=============================================================================
void Manager_Game::Update()
{
	//プレイヤーコントローラーnullチェック
	if (m_PlayerController != nullptr)
	{
		//プレイヤーコントローラー更新
		m_PlayerController->Update();
	}

	//レベルnullチェック
	if (m_Level != nullptr)
	{
		//レベル更新
		m_Level->Update();
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void Manager_Game::Uninit()
{
	//プレイヤーコントローラーnullチェック
	if (m_PlayerController != nullptr)
	{
		delete m_PlayerController;   //削除
		m_PlayerController = nullptr;//null代入
	}

	//レベルnullチェック
	if (m_Level != nullptr)
	{
		m_Level->Uninit(); //終了
		delete m_Level;    //削除
		m_Level = nullptr; //null代入
	}

	//マネージャー終了
	Manager_Texture::Instance()->Uninit(); //テクスチャマネージャー終了
	Manager_Shader::Instance()->Uninit();  //シェーダーマネージャー終了
	Manager_Font2D::Instance()->Uninit();  //フォント初期化

}

//=============================================================================
// 描画関数
//=============================================================================
void Manager_Game::Draw()
{
	//レベルnullチェック
	if (m_Level != nullptr)
	{
		//レベル描画
		m_Level->Draw();
	}
}
