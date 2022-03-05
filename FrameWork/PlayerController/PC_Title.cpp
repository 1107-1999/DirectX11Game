//=============================================================================
//
//  タイトルシーン用プレイヤーコントローラー [PC_Title.cpp]
//  Date   : 2021/1/08
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "PC_Title.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../System/Main.h"
#include "../System/MainWindow.h"
#include "../System/Math.h"
#include "../Level/Base/Level.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/HUD/HUD_Game.h"
#include "../PlayerController/PC_Game.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float HALF_SPEED  = 0.5f;
constexpr float ACCEL_SPEED = 2.0f;

//=============================================================================
// 初期化関数
//=============================================================================
void PC_Title::Init()
{
	//基底初期化
	PlayerController::Init();

	//マウス相対座標モードに変更
	if (m_Input != nullptr)
	{
		m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_ABSOLUTE);
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void PC_Title::Update()
{
	if (m_Input != nullptr)
	{
		//適当なキー押したら
		if (InputAction_Main() || InputAction_Second() || InputAction_Jump())
		{
			//カメラがレベルに存在する場合
			if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
			{
				//初期カメラ距離
				camera->AddTargetLength(300.0f);
			}

			//PlayerController変更
			Manager_Game::Instance()->SetPlayerController<PC_Game>();

			//HUD変更
			Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->SetHUD<HUD_Game>();
		}
	}

	//キャラクターがレベルに存在する場合
	if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
	{			
		//停止処理
		character->MoveAxis(0.0f, 0.0f);
	}
}
