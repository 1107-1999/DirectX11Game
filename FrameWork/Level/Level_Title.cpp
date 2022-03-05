//=============================================================================
//
//  タイトル [Level_Title.h]
//  Date   : 2021/1/09
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Level_Title.h"
#include "../PlayerController/PC_Title.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/2D/Atomosphere/Atomosphere.h"
#include "../Actor/HUD/HUD_Title.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Level_Title::Init()
{
	Level::Init();

	//プレイヤーコントローラーをPC_Titleに設定
	Manager_Game::Instance()->SetPlayerController<PC_Title>();

	//リソース読み込み
	Atomosphere::Load();

	//描画マネージャー追加
	if (Manager_Drawer* manager_Drawer = GetManager_Drawer())
	{//描画マネージャーをキャッシュ

		//各種エラー番号追加
		manager_Drawer->AddManager_Model();        //FBXマネージャー追加
		manager_Drawer->AddManager_Billboard();    //ビルボードマネージャー追加
		manager_Drawer->AddManager_Sprite();       //スプライトマネージャー追加
		manager_Drawer->AddManager_OBB();          //OBBマネージャー追加
		manager_Drawer->AddManager_Rigidbody();    //Rigidbodyマネージャー追加

	
		//大気追加
		AddActor<Atomosphere>();

		//カメラ追加
		Camera* gamera = AddActor<Camera>();
		gamera->SetPosition(Vector3{ 0.0f ,40.0f ,-70.0f });
		gamera->SetRotation(Vector3{ DegToRad(8.5f) ,DegToRad(0.0f) ,DegToRad(0.0f)});

		//HUD設定
		manager_Drawer->SetHUD<HUD_Title>();
	}

}
//=============================================================================
// 更新関数
//=============================================================================
void Level_Title::Update()
{
	//基底クラス更新
	Level::Update();
}

//=============================================================================
// 終了関数
//=============================================================================
void Level_Title::Uninit()
{
	//基底クラス終了
	Level::Uninit();

	//リソース解放
	Atomosphere::Unload();
};