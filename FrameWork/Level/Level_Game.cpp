//=============================================================================
//
//  ゲームレベル [Level_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Level_Game.h"
#include "../PlayerController/PC_Title.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Audio.h"
#include "../Manager/Manager_Shader.h"
#include "../Actor/2D/Atomosphere/Atomosphere.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/Prop/Cube.h"
#include "../Actor/3D/Prop/Gun.h"
#include "../Actor/3D/Prop/Goal.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/3D/ActorRB/Prop/Cube_LD.h"
#include "../Actor/3D/ActorRB/Prop/Cube_LD_Movable.h"
#include "../Actor/3D/ActorRB/Prop/FallFloor.h"
#include "../Actor/3D/ActorRB/Prop/BreakWall.h"
#include "../Actor/3D/ActorRB/Prop/Pusher.h"
#include "../Actor/3D/ActorRB/Prop/GunTargetRail.h"
#include "../Actor/3D/ActorRB/Prop/GunTarget.h"
#include "../Actor/3D/ActorRB/Prop/GunTable.h"
#include "../Actor/3D/Billboard/Explosion.h"
#include "../Actor/HUD/HUD_Title.h"
#include "../Component/Component_Cube.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr int TAEGET_NUM = 7;//銃ターゲットの数

//=============================================================================
// 初期化関数
//=============================================================================
void Level_Game::Init()
{
	//基底クラス初期化
	Level::Init();

#pragma region Resource Load

	//リソース読み込み

	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//BGM読み込み
		manager_audio->Load_Resource("Moonlight", "ROM\\Sound\\BGM\\Moonlight.wav");

		//BGM再生
		manager_audio->Play("Moonlight", XAUDIO2_LOOP_INFINITE);
	}

	//テクスチャーマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{

		//テクスチャー読み込み
		manager_Texture->LoadTexture("Concrete1",  "ROM/2D/Material/T_Concrete1.png");
		manager_Texture->LoadTexture("Concrete2",  "ROM/2D/Material/T_Concrete2.png");
		manager_Texture->LoadTexture("Brick2",     "ROM/2D/Material/T_Brick2.png");
		manager_Texture->LoadTexture("Celling",    "ROM/2D/Material/T_Celling.png");
		manager_Texture->LoadTexture("Hex",        "ROM/2D/Material/T_Hex.png");
		manager_Texture->LoadTexture("Metal1",     "ROM/2D/Material/T_Metal1.png");
		manager_Texture->LoadTexture("Metal2",     "ROM/2D/Material/T_Metal2.png");
		manager_Texture->LoadTexture("Metal3",     "ROM/2D/Material/T_Metal3.png");
		manager_Texture->LoadTexture("Metal4",     "ROM/2D/Material/T_Metal4.png");
		manager_Texture->LoadTexture("Sand",       "ROM/2D/Material/T_Sand.png");
		manager_Texture->LoadTexture("Arrow",      "ROM/2D/Material/T_Arrow.png");
		manager_Texture->LoadTexture("Arrow2",     "ROM/2D/Material/T_Arrow2.png");
		manager_Texture->LoadTexture("Wood",       "ROM/2D/Material/T_Wood.png");
		manager_Texture->LoadTexture("Road",       "ROM/2D/Material/T_Road.png");
		manager_Texture->LoadTexture("White",      "ROM/2D/Material/T_White.png");
		manager_Texture->LoadTexture("Blue",       "ROM/2D/Material/T_Blue.png");
		manager_Texture->LoadTexture("Red",        "ROM/2D/Material/T_Red.png");
		manager_Texture->LoadTexture("Tile",       "ROM/2D/Material/T_Tile.png");
		manager_Texture->LoadTexture("Guide1",     "ROM/2D/Guide/T_Guide1.png");
		manager_Texture->LoadTexture("Guide2",     "ROM/2D/Guide/T_Guide2.png");
		manager_Texture->LoadTexture("Guide3",     "ROM/2D/Guide/T_Guide3.png");
		manager_Texture->LoadTexture("Guide4",     "ROM/2D/Guide/T_Guide4.png");
		manager_Texture->LoadTexture("Guide5",     "ROM/2D/Guide/T_Guide5.png");
		manager_Texture->LoadTexture("Guide6",     "ROM/2D/Guide/T_Guide6.png");
		manager_Texture->LoadTexture("Guide7",     "ROM/2D/Guide/T_Guide7.png");
		manager_Texture->LoadTexture("Guide8",     "ROM/2D/Guide/T_Guide8.png");
		manager_Texture->LoadTexture("Guide9",     "ROM/2D/Guide/T_Guide9.png");
	}

	//キャラクタークラスロード
	Character::Load();

	//銃クラスロード
	Gun::Load();

	//大気クラスロード
	Atomosphere::Load();

	//キューブクラスロード
	Cube::Load();

	//レベルデザインキューブクラスロード
	Cube_LD::Load();

	//落ちる床クラスロード
	FallFloor::Load();

	//爆発ビルボードクラスロード
	Explosion::Load();

#pragma endregion

	//プレイヤーコントローラーをPC_Titleに設定
	Manager_Game::Instance()->SetPlayerController<PC_Title>();

	//描画マネージャーキャッシュ
	if (Manager_Drawer* manager_Drawer = GetManager_Drawer())
	{

		//各種描画マネージャー追加
		manager_Drawer->AddManager_Model();        //モデルマネージャー追加
		manager_Drawer->AddManager_Cube();         //キューブマネージャー追加
		manager_Drawer->AddManager_Billboard();    //ビルボードマネージャー追加
		manager_Drawer->AddManager_Sprite();       //スプライトマネージャー追加
		manager_Drawer->AddManager_OBB();          //OBBマネージャー追加
		manager_Drawer->AddManager_Rigidbody();    //剛体マネージャー追加


#pragma region Tutorial

		//床
		Cube_LD* floor = AddActor<Cube_LD>();
		floor->SetRigidbodyPosition(Vector3{ 0.0f,0.0f,189.5f });
		floor->SetRigidbodyScale(Vector3{ 20.0f,1.0f,400.0f });
		floor->GetComponentByClass<Component_Cube>()->SetTexture("Concrete1");

		//ガイド
		Cube_LD* guide1 = AddActor<Cube_LD>();
		guide1->SetRigidbodyPosition(Vector3{ -1.0f,0.75f,-2.5f });
		guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* guide2 = AddActor<Cube_LD>();
		guide2->SetRigidbodyPosition(Vector3{ -1.0f,1.1f,-2.5f });
		guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* guide3 = AddActor<Cube>();
		guide3->SetPosition(Vector3{ -1.0f,1.1f,-2.6f });
		guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide1");
		guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//ガイド2
		Cube_LD* guide4 = AddActor<Cube_LD>();
		guide4->SetRigidbodyPosition(Vector3{ -1.0f,0.75f,4.5f });
		guide4->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		guide4->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide4->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* guide5 = AddActor<Cube_LD>();
		guide5->SetRigidbodyPosition(Vector3{ -1.0f,1.1f,4.5f });
		guide5->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		guide5->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide5->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* guide6 = AddActor<Cube>();
		guide6->SetPosition(Vector3{ -1.0f,1.1f,4.4f });
		guide6->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		guide6->GetComponentByClass<Component_Cube>()->SetTexture("Guide7");
		guide6->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//ガイド3
		Cube_LD* guide7 = AddActor<Cube_LD>();
		guide7->SetRigidbodyPosition(Vector3{ -1.0f,0.75f,-6.5f });
		guide7->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		guide7->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide7->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* guide8 = AddActor<Cube_LD>();
		guide8->SetRigidbodyPosition(Vector3{ -1.0f,1.1f,-6.5f });
		guide8->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		guide8->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		guide8->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* guide9 = AddActor<Cube>();
		guide9->SetPosition(Vector3{ -1.0f,1.1f,-6.4f });
		guide9->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		guide9->GetComponentByClass<Component_Cube>()->SetTexture("Guide9");
		guide9->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//段差
		Cube_LD* floor2 = AddActor<Cube_LD>();
		floor2->SetRigidbodyPosition(Vector3{ 0.0f,0.625f,0.0f });
		floor2->SetRigidbodyScale(Vector3{ 20.0f,0.25f,3.0f });
		floor2->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		//天井
		Cube_LD* celling = AddActor<Cube_LD>();
		celling->SetRigidbodyPosition(Vector3{ 0.0f,5.0f,0.0f });
		celling->SetRigidbodyScale(Vector3{ 20.0f,1.0f,20.0f });
		celling->GetComponentByClass<Component_Cube>()->SetTexture("Celling");

		Cube_LD* celling2 = AddActor<Cube_LD>();
		celling2->SetRigidbodyPosition(Vector3{ 0.0f,7.0f,9.5f });
		celling2->SetRigidbodyScale(Vector3{ 20.0f,3.0f,1.0f });
		celling2->GetComponentByClass<Component_Cube>()->SetTexture("Celling");

		//左壁
		Cube_LD* wall1 = AddActor<Cube_LD>();
		wall1->SetRigidbodyPosition(Vector3{ -10.5f,4.5f,189.5f });
		wall1->SetRigidbodyScale(Vector3{ 1.0f,8.0f,400.0f });
		wall1->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		//右壁
		Cube_LD* wall2 = AddActor<Cube_LD>();
		wall2->SetRigidbodyPosition(Vector3{ 10.5f,4.5f,189.5f });
		wall2->SetRigidbodyScale(Vector3{ 1.0f,8.0f,400.0f });
		wall2->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		//後壁
		Cube_LD* wall3 = AddActor<Cube_LD>();
		wall3->SetRigidbodyPosition(Vector3{ 0.0f,4.5f,-10.5f });
		wall3->SetRigidbodyScale(Vector3{ 20.0f,8.0f,1.0f });
		wall3->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		//エレベーター
		Cube_LD_Movable* elevator = AddActor<Cube_LD_Movable>();
		elevator->SetRigidbodyPosition(Vector3{ 0.0f,0.625f,11.5f });
		elevator->SetRigidbodyScale(Vector3{ 3.0f,0.25f,3.0f });
		elevator->SetTarget(Vector3{ 0.0f,5.125f,10.5f });
		elevator->SetVelocity(Vector3{ 0.0f,250000.0f, 0.0f });
		elevator->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		elevator->GetComponentByClass<Component_Cube>()->SetTexture("Hex");

		//ステージ1始まりの壁
		Cube_LD* wall5 = AddActor<Cube_LD>();
		wall5->SetRigidbodyPosition(Vector3{ 5.75f,3.0f,11.5f });
		wall5->SetRigidbodyScale(Vector3{ 8.5f,5.0f,3.0f });
		wall5->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* wall6 = AddActor<Cube_LD>();
		wall6->SetRigidbodyPosition(Vector3{ -5.75f,3.0f,11.5f });
		wall6->SetRigidbodyScale(Vector3{ 8.5f,5.0f,3.0f });
		wall6->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* wall7 = AddActor<Cube_LD>();
		wall7->SetRigidbodyPosition(Vector3{ 0.0f,3.0f,13.5f });
		wall7->SetRigidbodyScale(Vector3{ 20.0f,5.0f,1.0f });
		wall7->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");


		//階段
		Cube_LD* stair = AddActor<Cube_LD>();
		stair->SetRigidbodyPosition(Vector3{ 0.0f,0.75f,14.5f });
		stair->SetRigidbodyScale(Vector3{ 4.0f,0.5f,1.0f });
		stair->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		for (int i = 0; i < 8; i++)
		{
			Cube_LD* stairR = AddActor<Cube_LD>();
			stairR->SetRigidbodyPosition(Vector3{ -2.0f - i * 1.0f,1.25f + i * 0.5f,14.5f });
			stairR->SetRigidbodyScale(Vector3{ 2.0f,0.5f,1.0f });
			stairR->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* stairL = AddActor<Cube_LD>();
			stairL->SetRigidbodyPosition(Vector3{ 2.0f + i * 1.0f,1.25f + i * 0.5f,14.5f });
			stairL->SetRigidbodyScale(Vector3{ 2.0f,0.5f,1.0f });
			stairL->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");
		}

#pragma endregion

#pragma region Stage1

		//ステージ1ブロック
		Cube_LD* s1Block1 = AddActor<Cube_LD>();
		s1Block1->SetRigidbodyPosition(Vector3{ 0.0f,5.25f,16.5f });
		s1Block1->SetRigidbodyScale(Vector3{ 3.0f,0.5f,5.0f });
		s1Block1->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		Cube_LD* s1Block2 = AddActor<Cube_LD>();
		s1Block2->SetRigidbodyPosition(Vector3{ 0.0f,5.75f,22.5f });
		s1Block2->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s1Block2->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		//ガイド
		Cube_LD* s1guide1 = AddActor<Cube_LD>();
		s1guide1->SetRigidbodyPosition(Vector3{ -1.5f,5.75f,13.5f });
		s1guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		s1guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s1guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* s1guide2 = AddActor<Cube_LD>();
		s1guide2->SetRigidbodyPosition(Vector3{ -1.5f,6.1f,13.5f });
		s1guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		s1guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s1guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* s1guide3 = AddActor<Cube>();
		s1guide3->SetPosition(Vector3{ -1.5f,6.1f,13.4f });
		s1guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s1guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide2");
		s1guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		for (int i = 0; i < 3; i++)
		{
			Cube_LD* stairR = AddActor<Cube_LD>();
			stairR->SetRigidbodyPosition(Vector3{ -1.0f - i * 1.5f,3.75f + 0.75f * i,25.5f + i * 1.5f });
			stairR->SetRigidbodyScale(Vector3{ 1.5f,1.0f,1.0f });
			stairR->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* stairL = AddActor<Cube_LD>();
			stairL->SetRigidbodyPosition(Vector3{ 1.0f + i * 1.5f,3.75f + 0.75f * i,25.5f + i * 1.5f });
			stairL->SetRigidbodyScale(Vector3{ 1.5f,1.0f,1.0f });
			stairL->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* stairR2 = AddActor<Cube_LD>();
			stairR2->SetRigidbodyPosition(Vector3{ -5.5f - i * 1.5f,3.75f + 0.75f * i,30.0f + i * 1.5f });
			stairR2->SetRigidbodyScale(Vector3{ 1.5f,1.0f,1.0f });
			stairR2->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* stairL2 = AddActor<Cube_LD>();
			stairL2->SetRigidbodyPosition(Vector3{ 5.5f + i * 1.5f,3.75f + 0.75f * i,30.0f + i * 1.5f });
			stairL2->SetRigidbodyScale(Vector3{ 1.5f,1.0f,1.0f });
			stairL2->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");
		}

		//リフト
		Cube_LD_Movable* lift = AddActor<Cube_LD_Movable>();
		lift->SetRigidbodyPosition(Vector3{ -8.5f,5.25f,35.0f });
		lift->SetRigidbodyScale(Vector3{ 3.0f,0.25f,3.0f });
		lift->SetTarget(Vector3{ 8.5f,5.25f,35.0f });
		lift->SetVelocity(Vector3{ 250000.0f,0.0f, 0.0f });
		lift->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		lift->GetComponentByClass<Component_Cube>()->SetTexture("Hex");

		Cube_LD* s1Block3 = AddActor<Cube_LD>();
		s1Block3->SetRigidbodyPosition(Vector3{0.0f,2.875f,38.0f });
		s1Block3->SetRigidbodyScale(Vector3{ 20.0f,4.75f,3.0f });
		s1Block3->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

#pragma endregion
#pragma region Stage2

		//ガイド
		Cube* s2Guide = AddActor<Cube>();
		s2Guide->SetPosition(Vector3{ -2.5f,6.5f,38.49f });
		s2Guide->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s2Guide->GetComponentByClass<Component_Cube>()->SetTexture("Guide3");
		s2Guide->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//床
		Cube_LD* s2floor = AddActor<Cube_LD>();
		s2floor->SetRigidbodyPosition(Vector3{ 0.0f,2.875f,59.5f });
		s2floor->SetRigidbodyScale(Vector3{ 20.0f,4.75f,40.0f });
		s2floor->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_SAND);
		s2floor->GetComponentByClass<Component_Cube>()->SetTexture("Sand");

		//迷路
		Cube_LD* s2wood1 = AddActor<Cube_LD>();
		s2wood1->SetRigidbodyPosition(Vector3{ -5.25f,6.875f,39.0f });
		s2wood1->SetRigidbodyScale(Vector3{ 9.5f,3.25f,1.0f });
		s2wood1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood2 = AddActor<Cube_LD>();
		s2wood2->SetRigidbodyPosition(Vector3{  5.25f,6.875f,39.0f });
		s2wood2->SetRigidbodyScale(Vector3{ 9.5f,3.25f,1.0f });
		s2wood2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood3 = AddActor<Cube_LD>();
		s2wood3->SetRigidbodyPosition(Vector3{ 1.0f,6.875f,41.0f });
		s2wood3->SetRigidbodyScale(Vector3{ 14.0f,3.25f,1.0f });
		s2wood3->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood4 = AddActor<Cube_LD>();
		s2wood4->SetRigidbodyPosition(Vector3{ 0.75f,6.875f,47.0f });
		s2wood4->SetRigidbodyScale(Vector3{ 18.5f,3.25f,1.0f });
		s2wood4->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood5 = AddActor<Cube_LD>();
		s2wood5->SetRigidbodyPosition(Vector3{ -8.0f,6.875f,44.0f });
		s2wood5->SetRigidbodyScale(Vector3{ 1.0f,3.25f,7.0f });
		s2wood5->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood6 = AddActor<Cube_LD>();
		s2wood6->SetRigidbodyPosition(Vector3{ -6.0f,6.875f,43.0f });
		s2wood6->SetRigidbodyScale(Vector3{ 1.0f,3.25f,5.0f });
		s2wood6->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood7 = AddActor<Cube_LD>();
		s2wood7->SetRigidbodyPosition(Vector3{ 8.5f,6.875f,43.0f });
		s2wood7->SetRigidbodyScale(Vector3{ 1.0f,3.25f,5.0f });
		s2wood7->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood8 = AddActor<Cube_LD>();
		s2wood8->SetRigidbodyPosition(Vector3{ 6.5f,6.875f,44.0f });
		s2wood8->SetRigidbodyScale(Vector3{ 1.0f,3.25f,7.0f });
		s2wood8->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood9 = AddActor<Cube_LD>();
		s2wood9->SetRigidbodyPosition(Vector3{ -3.5f,6.875f,44.0f });
		s2wood9->SetRigidbodyScale(Vector3{ 1.0f,3.25f,7.0f });
		s2wood9->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood10 = AddActor<Cube_LD>();
		s2wood10->SetRigidbodyPosition(Vector3{ -8.0f,6.875f,51.0f });
		s2wood10->SetRigidbodyScale(Vector3{ 1.0f,3.25f,7.0f });
		s2wood10->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood11 = AddActor<Cube_LD>();
		s2wood11->SetRigidbodyPosition(Vector3{ -5.0f,6.875f,54.5f });
		s2wood11->SetRigidbodyScale(Vector3{ 7.0f,3.25f,1.0f });
		s2wood11->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood12 = AddActor<Cube_LD>();
		s2wood12->SetRigidbodyPosition(Vector3{ 1.0f,6.875f,52.0f });
		s2wood12->SetRigidbodyScale(Vector3{ 1.0f,3.25f,6.0f });
		s2wood12->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood13 = AddActor<Cube_LD>();
		s2wood13->SetRigidbodyPosition(Vector3{ -2.5f,6.875f,58.0f });
		s2wood13->SetRigidbodyScale(Vector3{ 15.0f,3.25f,1.0f });
		s2wood13->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood14 = AddActor<Cube_LD>();
		s2wood14->SetRigidbodyPosition(Vector3{ 4.5f,6.875f,54.5f });
		s2wood14->SetRigidbodyScale(Vector3{ 7.0f,3.25f,1.0f });
		s2wood14->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood15 = AddActor<Cube_LD>();
		s2wood15->SetRigidbodyPosition(Vector3{ 7.5f,6.875f,60.0f });
		s2wood15->SetRigidbodyScale(Vector3{ 1.0f,3.25f,10.0f });
		s2wood15->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood16 = AddActor<Cube_LD>();
		s2wood16->SetRigidbodyPosition(Vector3{ -1.5f,6.875f,61.0f });
		s2wood16->SetRigidbodyScale(Vector3{ 13.0f,3.25f,1.0f });
		s2wood16->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood17 = AddActor<Cube_LD>();
		s2wood17->SetRigidbodyPosition(Vector3{ 0.0f,6.875f,65.5f });
		s2wood17->SetRigidbodyScale(Vector3{ 16.0f,3.25f,1.0f });
		s2wood17->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood18 = AddActor<Cube_LD>();
		s2wood18->SetRigidbodyPosition(Vector3{ -7.5f,6.875f,63.25f });
		s2wood18->SetRigidbodyScale(Vector3{ 1.0f,3.25f,3.5f });
		s2wood18->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood19 = AddActor<Cube_LD>();
		s2wood19->SetRigidbodyPosition(Vector3{ -1.0f,6.875f,66.5f });
		s2wood19->SetRigidbodyScale(Vector3{ 18.0f,3.25f,1.0f });
		s2wood19->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood20 = AddActor<Cube_LD>();
		s2wood20->SetRigidbodyPosition(Vector3{ 2.5f,6.875f,72.0f });
		s2wood20->SetRigidbodyScale(Vector3{ 15.0f,3.25f,1.0f });
		s2wood20->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood21 = AddActor<Cube_LD>();
		s2wood21->SetRigidbodyPosition(Vector3{ 7.5f,6.875f,52.0f });
		s2wood21->SetRigidbodyScale(Vector3{ 1.0f,3.25f,6.0f });
		s2wood21->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood22 = AddActor<Cube_LD>();
		s2wood22->SetRigidbodyPosition(Vector3{ 3.5f,6.875f,49.0f });
		s2wood22->SetRigidbodyScale(Vector3{ 1.0f,3.25f,5.0f });
		s2wood22->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood23 = AddActor<Cube_LD>();
		s2wood23->SetRigidbodyPosition(Vector3{ 0.0f,6.875f,69.0f });
		s2wood23->SetRigidbodyScale(Vector3{ 16.0f,3.25f,1.0f });
		s2wood23->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood24 = AddActor<Cube_LD>();
		s2wood24->SetRigidbodyPosition(Vector3{ -3.5f,6.875f,49.0f });
		s2wood24->SetRigidbodyScale(Vector3{ 1.0f,3.25f,5.0f });
		s2wood24->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood25 = AddActor<Cube_LD>();
		s2wood25->SetRigidbodyPosition(Vector3{ -9.0f,6.875f,65.0f });
		s2wood25->SetRigidbodyScale(Vector3{ 2.0f,3.25f,2.0f });
		s2wood25->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood26 = AddActor<Cube_LD>();
		s2wood26->SetRigidbodyPosition(Vector3{ 1.0f,6.875f,80.0f });
		s2wood26->SetRigidbodyScale(Vector3{ 18.0f,3.25f,1.0f });
		s2wood26->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2wood27 = AddActor<Cube_LD>();
		s2wood27->SetRigidbodyPosition(Vector3{ -7.5f,6.875f,74.5f });
		s2wood27->SetRigidbodyScale(Vector3{ 1.0f,3.25f,11.0f });
		s2wood27->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		Cube_LD* s2Block = AddActor<Cube_LD>();
		s2Block->SetRigidbodyPosition(Vector3{ 0.0f,2.875f,82.0f });
		s2Block->SetRigidbodyScale(Vector3{ 20.0f,4.75f,5.0f });
		s2Block->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");


#pragma endregion
#pragma region Stage3

		//ガイド
		Cube_LD* s3guide1 = AddActor<Cube_LD>();
		s3guide1->SetRigidbodyPosition(Vector3{ -5.5f,5.505f,83.5f });
		s3guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		s3guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s3guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* s3guide2 = AddActor<Cube_LD>();
		s3guide2->SetRigidbodyPosition(Vector3{ -5.5f,5.855f,83.5f });
		s3guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		s3guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s3guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* s3guide3 = AddActor<Cube>();
		s3guide3->SetPosition(Vector3{ -5.5f,5.855f,83.4f });
		s3guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s3guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide4");
		s3guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//レール
		Cube_LD* s3Floor = AddActor<Cube_LD>();
		s3Floor->SetRigidbodyPosition(Vector3{ 0.0f,5.0f,185.0f });
		s3Floor->SetRigidbodyScale(Vector3{ 10.0f,0.5f,200.0f });
		s3Floor->GetComponentByClass<Component_Cube>()->SetTexture("Road");

		//ブロック
		Cube_LD* s3Block = AddActor<Cube_LD>();
		s3Block->SetRigidbodyPosition(Vector3{ 0.0f,2.625f,225.0f });
		s3Block->SetRigidbodyScale(Vector3{ 20.0f,4.25f,5.0f });
		s3Block->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		Cube_LD* s3Block2 = AddActor<Cube_LD>();
		s3Block2->SetRigidbodyPosition(Vector3{ 0.0f,2.625f,257.5f });
		s3Block2->SetRigidbodyScale(Vector3{ 10.0f,4.25f,65.0f });
		s3Block2->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s3Block3 = AddActor<Cube_LD>();
		s3Block3->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,287.5f });
		s3Block3->SetRigidbodyScale(Vector3{ 20.0f,4.0f,5.0f });
		s3Block3->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s3Block4 = AddActor<Cube_LD>();
		s3Block4->SetRigidbodyPosition(Vector3{ 7.5f,6.5f,265.0f });
		s3Block4->SetRigidbodyScale(Vector3{ 5.0f,4.0f,50.0f });
		s3Block4->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s3Block5 = AddActor<Cube_LD>();
		s3Block5->SetRigidbodyPosition(Vector3{ -7.5f,6.5f,265.0f });
		s3Block5->SetRigidbodyScale(Vector3{ 5.0f,4.0f,50.0f });
		s3Block5->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s3Block6 = AddActor<Cube_LD>();
		s3Block6->SetRigidbodyPosition(Vector3{ 7.5f,6.5f,239.9f });
		s3Block6->SetRigidbodyScale(Vector3{ 5.0f,4.0f,0.001f });
		s3Block6->GetComponentByClass<Component_Cube>()->SetTexture("Arrow2");
		s3Block6->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		Cube_LD* s3Block7 = AddActor<Cube_LD>();
		s3Block7->SetRigidbodyPosition(Vector3{ -7.5f,6.5f,239.9f });
		s3Block7->SetRigidbodyScale(Vector3{ 5.0f,4.0f,0.001f });
		s3Block7->GetComponentByClass<Component_Cube>()->SetTexture("Arrow");
		s3Block7->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//プッシャー
		Pusher* pusher = AddActor<Pusher>();
		pusher->SetRigidbodyPosition(Vector3{ 0.0f,5.75f,285.0f });
		pusher->SetRigidbodyScale(Vector3{ 10.0f,1.0f,1.0f });
		pusher->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		pusher->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Pusher* pusher2 = AddActor<Pusher>();
		pusher2->SetRigidbodyPosition(Vector3{ -1.75f,7.25f,200.0f });
		pusher2->SetRigidbodyScale(Vector3{ 6.5f,4.0f,0.5f });
		pusher2->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");
		pusher2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Pusher* pusher3 = AddActor<Pusher>();
		pusher3->SetRigidbodyPosition(Vector3{ 1.75f,7.25f,150.0f });
		pusher3->SetRigidbodyScale(Vector3{ 6.5f,4.0f,0.5f });
		pusher3->GetComponentByClass<Component_Cube>()->SetTexture("Metal4");
		pusher3->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		//階段
		Cube_LD* s3stair = AddActor<Cube_LD>();
		s3stair->SetRigidbodyPosition(Vector3{ 0.0f,0.75f,85.0f });
		s3stair->SetRigidbodyScale(Vector3{ 4.0f,0.5f,1.0f });
		s3stair->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		for (int i = 0; i < 8; i++)
		{
			Cube_LD* stairR = AddActor<Cube_LD>();
			stairR->SetRigidbodyPosition(Vector3{ -2.0f - i * 1.0f,1.25f + i * 0.5f,85.0f });
			stairR->SetRigidbodyScale(Vector3{ 2.0f,0.5f,1.0f });
			stairR->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* stairL = AddActor<Cube_LD>();
			stairL->SetRigidbodyPosition(Vector3{ 2.0f + i * 1.0f,1.25f + i * 0.5f,85.0f });
			stairL->SetRigidbodyScale(Vector3{ 2.0f,0.5f,1.0f });
			stairL->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");
		}

#pragma endregion
#pragma region Stage4

		//階段
		for (int i = 0; i < 8; i++)
		{
			Cube_LD* s4stair = AddActor<Cube_LD>();
			s4stair->SetRigidbodyPosition(Vector3{ 0.0f,0.75f + i * 0.5f,295.0f  + i * 1.0f});
			s4stair->SetRigidbodyScale(Vector3{ 20.0f,0.5f,1.0f });
			s4stair->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");
		}
		
		//エレベーター
		Cube_LD_Movable* s4elevator = AddActor<Cube_LD_Movable>();
		s4elevator->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,308.0f });
		s4elevator->SetRigidbodyScale(Vector3{ 20.0f,1.0f,1.0f });
		s4elevator->SetTarget(Vector3{ 0.0f,1.0f,308.0f });
		s4elevator->SetVelocity(Vector3{ 0.0f,250000.0f, 0.0f });
		s4elevator->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s4elevator->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");


		//ガイド
		Cube_LD* s4guide1 = AddActor<Cube_LD>();
		s4guide1->SetRigidbodyPosition(Vector3{ -5.5f,5.3f,305.5f });
		s4guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		s4guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s4guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* s4guide2 = AddActor<Cube_LD>();
		s4guide2->SetRigidbodyPosition(Vector3{ -5.5f,5.65f,305.5f });
		s4guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		s4guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s4guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* s4guide3 = AddActor<Cube>();
		s4guide3->SetPosition(Vector3{ -5.5f,5.65f,305.4f });
		s4guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s4guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide5");
		s4guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//ブロック
		Cube_LD* s4Block = AddActor<Cube_LD>();
		s4Block->SetRigidbodyPosition(Vector3{ 0.0f,2.75f,305.0f });
		s4Block->SetRigidbodyScale(Vector3{ 20.0f,4.75f,5.0f });
		s4Block->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		Cube_LD* s4Block2 = AddActor<Cube_LD>();
		s4Block2->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,311.0f });
		s4Block2->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block2->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Cube_LD* s4Block3 = AddActor<Cube_LD>();
		s4Block3->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,324.5f });
		s4Block3->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block3->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block3->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		FallFloor* fall1 = AddActor<FallFloor>();
		fall1->SetRigidbodyPosition(Vector3{ 5.75f,4.5f,317.75f });
		fall1->GetComponentByClass<Component_Cube>()->SetTexture("Blue");
		fall1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block4 = AddActor<Cube_LD>();
		s4Block4->SetRigidbodyPosition(Vector3{ -5.75f,4.5f,317.75f });
		s4Block4->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s4Block4->GetComponentByClass<Component_Cube>()->SetTexture("Red");
		s4Block4->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block5 = AddActor<Cube_LD>();
		s4Block5->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,317.75f });
		s4Block5->SetRigidbodyScale(Vector3{ 3.0f,4.25f,8.5f });
		s4Block5->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block5->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		FallFloor* fall2 = AddActor<FallFloor>();
		fall2->SetRigidbodyPosition(Vector3{ -5.75f,4.5f,331.25f });
		fall2->GetComponentByClass<Component_Cube>()->SetTexture("Red");
		fall2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block6 = AddActor<Cube_LD>();
		s4Block6->SetRigidbodyPosition(Vector3{ 5.75f,4.5f,331.25f });
		s4Block6->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s4Block6->GetComponentByClass<Component_Cube>()->SetTexture("Blue");
		s4Block6->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block7 = AddActor<Cube_LD>();
		s4Block7->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,331.25f });
		s4Block7->SetRigidbodyScale(Vector3{ 3.0f,4.25f,8.5f });
		s4Block7->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block7->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Cube_LD* s4Block8 = AddActor<Cube_LD>();
		s4Block8->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,338.0f });
		s4Block8->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block8->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block8->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		FallFloor* fall3 = AddActor<FallFloor>();
		fall3->SetRigidbodyPosition(Vector3{ -5.75f,4.5f,344.75f });
		fall3->GetComponentByClass<Component_Cube>()->SetTexture("Red");
		fall3->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block9 = AddActor<Cube_LD>();
		s4Block9->SetRigidbodyPosition(Vector3{ 5.75f,4.5f,344.75f });
		s4Block9->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s4Block9->GetComponentByClass<Component_Cube>()->SetTexture("Blue");
		s4Block9->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block10 = AddActor<Cube_LD>();
		s4Block10->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,344.75f });
		s4Block10->SetRigidbodyScale(Vector3{ 3.0f,4.25f,8.5f });
		s4Block10->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block10->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Cube_LD* s4Block11 = AddActor<Cube_LD>();
		s4Block11->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,351.5f });
		s4Block11->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block11->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block11->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		FallFloor* fall4 = AddActor<FallFloor>();
		fall4->SetRigidbodyPosition(Vector3{ 5.75f,4.5f,358.25f });
		fall4->GetComponentByClass<Component_Cube>()->SetTexture("Blue");
		fall4->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block12 = AddActor<Cube_LD>();
		s4Block12->SetRigidbodyPosition(Vector3{-5.75f,4.5f,358.25f });
		s4Block12->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s4Block12->GetComponentByClass<Component_Cube>()->SetTexture("Red");
		s4Block12->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block13 = AddActor<Cube_LD>();
		s4Block13->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,358.25f });
		s4Block13->SetRigidbodyScale(Vector3{ 3.0f,4.25f,8.5f });
		s4Block13->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block13->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Cube_LD* s4Block14 = AddActor<Cube_LD>();
		s4Block14->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,365.0f });
		s4Block14->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block14->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block14->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		FallFloor* fall5 = AddActor<FallFloor>();
		fall5->SetRigidbodyPosition(Vector3{ -5.75f,4.5f,371.75f });
		fall5->GetComponentByClass<Component_Cube>()->SetTexture("Red");
		fall5->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block15 = AddActor<Cube_LD>();
		s4Block15->SetRigidbodyPosition(Vector3{ 5.75f,4.5f,371.75f });
		s4Block15->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s4Block15->GetComponentByClass<Component_Cube>()->SetTexture("Blue");
		s4Block15->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);

		Cube_LD* s4Block16 = AddActor<Cube_LD>();
		s4Block16->SetRigidbodyPosition(Vector3{ 0.0f,6.5f,371.75f });
		s4Block16->SetRigidbodyScale(Vector3{ 3.0f,4.25f,8.5f });
		s4Block16->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block16->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

		Cube_LD* s4Block17 = AddActor<Cube_LD>();
		s4Block17->SetRigidbodyPosition(Vector3{ 0.0f,4.625f,378.5f });
		s4Block17->SetRigidbodyScale(Vector3{ 20.0f,1.0f,5.0f });
		s4Block17->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");
		s4Block17->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);

#pragma endregion
#pragma region Stage5

		//ガイド
		Cube_LD* s5guide1 = AddActor<Cube_LD>();
		s5guide1->SetRigidbodyPosition(Vector3{ -5.5f,0.75f,393.5f });
		s5guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		s5guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s5guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* s5guide2 = AddActor<Cube_LD>();
		s5guide2->SetRigidbodyPosition(Vector3{ -5.5f,1.1f,393.5f });
		s5guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		s5guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s5guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* s5guide3 = AddActor<Cube>();
		s5guide3->SetPosition(Vector3{ -5.5f,1.1f,393.4f });
		s5guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s5guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide6");
		s5guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);


		//ブロック
		Cube_LD* s5Block = AddActor<Cube_LD>();
		s5Block->SetRigidbodyPosition(Vector3{ 0.0f,2.75f,383.5f });
		s5Block->SetRigidbodyScale(Vector3{ 20.0f,4.75f,5.0f });
		s5Block->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		Cube_LD* s5Block2 = AddActor<Cube_LD>();
		s5Block2->SetRigidbodyPosition(Vector3{ 1.5f,4.5f,387.75f });
		s5Block2->SetRigidbodyScale(Vector3{ 17.0f,8.0f,3.5f });
		s5Block2->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s5Block3 = AddActor<Cube_LD>();
		s5Block3->SetRigidbodyPosition(Vector3{ -8.5f,3.75f,389.25f });
		s5Block3->SetRigidbodyScale(Vector3{ 3.0f,3.5f,0.5f });
		s5Block3->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s5Arrow = AddActor<Cube_LD>();
		s5Arrow->SetRotation(Vector3{ DegToRad(0.0f), DegToRad(0.0f), DegToRad(-90.0f) });
		s5Arrow->SetRigidbodyPosition(Vector3{ -8.5f,6.5f,388.99f });
		s5Arrow->SetRigidbodyScale(Vector3{ 3.0f,3.0f,0.01f });
		s5Arrow->GetComponentByClass<Component_Cube>()->SetTexture("Arrow2");
		s5Arrow->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

		//床
		Cube_LD* s5floor = AddActor<Cube_LD>();
		s5floor->SetRigidbodyPosition(Vector3{ 0.0f,0.0f,414.5f });
		s5floor->SetRigidbodyScale(Vector3{ 20.0f,1.0f,50.0f });
		s5floor->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s5floor->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		//天井
		Cube_LD* s5cellingr = AddActor<Cube_LD>();
		s5cellingr->SetRigidbodyPosition(Vector3{ 0.0f,6.0f,414.5f });
		s5cellingr->SetRigidbodyScale(Vector3{ 20.0f,1.0f,50.0f });
		s5cellingr->GetComponentByClass<Component_Cube>()->SetTexture("Celling");

		//壁
		Cube_LD* s5wall1 = AddActor<Cube_LD>();
		s5wall1->SetRigidbodyPosition(Vector3{ 10.5f,3.0f,414.5f });
		s5wall1->SetRigidbodyScale(Vector3{ 1.0f,5.0f,50.0f });
		s5wall1->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		Cube_LD* s5wall2 = AddActor<Cube_LD>();
		s5wall2->SetRigidbodyPosition(Vector3{ -10.5f,3.0f,414.5f });
		s5wall2->SetRigidbodyScale(Vector3{ 1.0f,5.0f,50.0f });
		s5wall2->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		BreakWall* breakwall = AddActor<BreakWall>();
		breakwall->SetRigidbodyPosition(Vector3{ 0.0f,4.5f,441.25f });
		breakwall->SetRigidbodyScale(Vector3{ 20.0f,8.0f,3.5f });
		breakwall->GetComponentByClass<Component_Cube>()->SetTexture("Concrete2");

		//テーブル
		GunTable* guntable = AddActor<GunTable>();
		guntable->SetRigidbodyPosition(Vector3{ 0.0f,1.1f,395.0f });

		//銃
		Gun* gun = AddActor<Gun>();
		gun->SetPosition(Vector3{ 0.0f,1.21f,394.9f });


		//ターゲット配列
		GunTarget* target[TAEGET_NUM];

		//射撃場
		for (int i = 0; i < TAEGET_NUM; i++)
		{
			//右レール
			GunTargetRail* RailR = AddActor<GunTargetRail>();
			RailR->SetRigidbodyPosition(Vector3{  2.5f,0.5f,400.0f + i * 5.0f });

			//左レール
			GunTargetRail* RailL = AddActor<GunTargetRail>();
			RailL->SetRigidbodyPosition(Vector3{ -2.5f,0.5f,400.0f + i * 5.0f });

			//ターゲット
			target[i] = AddActor<GunTarget>();
			target[i]->SetRigidbodyPosition(Vector3{ 0.0f,0.5f,400.0f + i * 5.0f });
			target[i]->SetVelocity(500000.0f + i * 10000.0f );
			
			//右テーブル
			GunTable* guntableR = AddActor<GunTable>();
			guntableR->SetRigidbodyPosition(Vector3{ -1.3f - i * 1.3f,1.1f,395.0f });

			//左テーブル
			GunTable* guntableL = AddActor<GunTable>();
			guntableL->SetRigidbodyPosition(Vector3{ 1.3f + i * 1.3f,1.1f,395.0f });
		}

		//的の進行方向設定
		target[0]->SetVector(false);
		target[2]->SetVector(false);
		target[4]->SetVector(false);
		target[6]->SetVector(false);

#pragma endregion
#pragma region Stage6

		//床
		Cube_LD* s6floor = AddActor<Cube_LD>();
		s6floor->SetRigidbodyPosition(Vector3{ 0.0f,0.0f,467.5f });
		s6floor->SetRigidbodyScale(Vector3{ 50.0f,1.0f,50.0f });
		s6floor->GetComponentByClass<Component_Cube>()->SetTexture("Concrete1");

		Cube_LD* s6floor2 = AddActor<Cube_LD>();
		s6floor2->SetRigidbodyPosition(Vector3{ 0.0f,0.0f,441.0f });
		s6floor2->SetRigidbodyScale(Vector3{ 50.0f,1.0f,3.0f });
		s6floor2->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		//壁
		Cube_LD* s6Wall1 = AddActor<Cube_LD>();
		s6Wall1->SetRigidbodyPosition(Vector3{ 27.5f,25.5f,467.5f });
		s6Wall1->SetRigidbodyScale(Vector3{ 5.0f,50.0f,50.0f });
		s6Wall1->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall2 = AddActor<Cube_LD>();
		s6Wall2->SetRigidbodyPosition(Vector3{-27.5f,25.5f,467.5f });
		s6Wall2->SetRigidbodyScale(Vector3{ 5.0f,50.0f,50.0f });
		s6Wall2->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall3 = AddActor<Cube_LD>();
		s6Wall3->SetRigidbodyPosition(Vector3{ 0.0f,25.5f,495.0f });
		s6Wall3->SetRigidbodyScale(Vector3{ 50.0f,50.0f,5.0f });
		s6Wall3->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall4 = AddActor<Cube_LD>();
		s6Wall4->SetRigidbodyPosition(Vector3{ 17.5f,25.5f,441.0f });
		s6Wall4->SetRigidbodyScale(Vector3{ 15.0f,50.0f,3.0f });
		s6Wall4->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall5 = AddActor<Cube_LD>();
		s6Wall5->SetRigidbodyPosition(Vector3{-17.5f,25.5f,441.0f });
		s6Wall5->SetRigidbodyScale(Vector3{ 15.0f,50.0f,3.0f });
		s6Wall5->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall6 = AddActor<Cube_LD>();
		s6Wall6->SetRigidbodyPosition(Vector3{ 0.0f,29.5f,441.0f });
		s6Wall6->SetRigidbodyScale(Vector3{ 20.0f,42.0f,3.0f });
		s6Wall6->GetComponentByClass<Component_Cube>()->SetTexture("Tile");

		Cube_LD* s6Wall7 = AddActor<Cube_LD>();
		s6Wall7->SetRigidbodyPosition(Vector3{ 0.0f,8.0f,439.0f });
		s6Wall7->SetRigidbodyScale(Vector3{ 20.0f,3.0f,1.0f });
		s6Wall7->GetComponentByClass<Component_Cube>()->SetTexture("Celling");

		//ブロック

		//始点
		Cube_LD* s6Block = AddActor<Cube_LD>();
		s6Block->SetRigidbodyPosition(Vector3{ 0.0f ,0.75f ,467.5f });
		s6Block->SetRigidbodyScale(Vector3{ 1.0f,0.5f,1.0f });
		s6Block->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		//階段
		for (int i = 1; i < 10; i++)
		{
			Cube_LD* s6Block = AddActor<Cube_LD>();
			s6Block->SetRigidbodyPosition(Vector3{ 0.0f + i * 1.0f,0.75f + i * 0.5f,467.5f + i * 1.0f });
			s6Block->SetRigidbodyScale(Vector3{ 1.0f,0.5f,1.0f });
			s6Block->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* s6Block2 = AddActor<Cube_LD>();
			s6Block2->SetRigidbodyPosition(Vector3{ 0.0f - i * 1.0f,0.75f + i * 0.5f,467.5f - i * 1.0f });
			s6Block2->SetRigidbodyScale(Vector3{ 1.0f,0.5f,1.0f });
			s6Block2->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* s6Block3 = AddActor<Cube_LD>();
			s6Block3->SetRigidbodyPosition(Vector3{ 0.0f + i * 1.0f,0.75f + i * 0.5f,467.5f - i * 1.0f });
			s6Block3->SetRigidbodyScale(Vector3{ 1.0f,0.5f,1.0f });
			s6Block3->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

			Cube_LD* s6Block4 = AddActor<Cube_LD>();
			s6Block4->SetRigidbodyPosition(Vector3{ 0.0f - i * 1.0f,0.75f + i * 0.5f,467.5f + i * 1.0f });
			s6Block4->SetRigidbodyScale(Vector3{ 1.0f,0.5f,1.0f });
			s6Block4->GetComponentByClass<Component_Cube>()->SetTexture("Brick2");

		}


		//横奥
		Cube_LD* s6SideBlock = AddActor<Cube_LD>();
		s6SideBlock->SetRigidbodyPosition(Vector3{ 0.0f,5.75f,477.5f });
		s6SideBlock->SetRigidbodyScale(Vector3{ 22.0f,0.5f,1.0f });
		s6SideBlock->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);
		s6SideBlock->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		//横前
		Cube_LD* s6SideBlock2 = AddActor<Cube_LD>();
		s6SideBlock2->SetRigidbodyPosition(Vector3{ 0.0f,5.75f,457.5f });
		s6SideBlock2->SetRigidbodyScale(Vector3{ 22.0f,0.5f,1.0f });
		s6SideBlock2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);
		s6SideBlock2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		//柱
		for (int i = 0; i < 10; i++)
		{
			//柱1
			Cube_LD* s6Block = AddActor<Cube_LD>();
			s6Block->SetRigidbodyPosition(Vector3{ 10.0f,5.25f - i * 0.5f,477.5f });
			s6Block->SetRigidbodyScale(Vector3{ 0.25f,0.5f,0.25f });
			s6Block->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

			//柱2
			Cube_LD* s6Block2 = AddActor<Cube_LD>();
			s6Block2->SetRigidbodyPosition(Vector3{10.0f,5.25f - i * 0.5f,457.5f });
			s6Block2->SetRigidbodyScale(Vector3{ 0.25f,0.5f,0.25f });
			s6Block2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

			//柱3
			Cube_LD* s6Block3 = AddActor<Cube_LD>();
			s6Block3->SetRigidbodyPosition(Vector3{ -10.0f,5.25f - i * 0.5f,477.5f });
			s6Block3->SetRigidbodyScale(Vector3{ 0.25f,0.5f,0.25f });
			s6Block3->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

			//柱4
			Cube_LD* s6Block4 = AddActor<Cube_LD>();
			s6Block4->SetRigidbodyPosition(Vector3{ -10.0f,5.25f - i * 0.5f,457.5f });
			s6Block4->SetRigidbodyScale(Vector3{ 0.25f,0.5f,0.25f });
			s6Block4->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		}

		//エレベーター
		Cube_LD_Movable* s6elevator = AddActor<Cube_LD_Movable>();
		s6elevator->SetRigidbodyPosition(Vector3{ 12.5f,5.75f,477.5f });
		s6elevator->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s6elevator->SetTarget(Vector3{ 12.5f,5.75f,457.5f });
		s6elevator->SetVelocity(Vector3{ 0.0f,0.0f, 250000.0f });
		s6elevator->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");

		Cube_LD_Movable* s6elevator2 = AddActor<Cube_LD_Movable>();
		s6elevator2->SetRigidbodyPosition(Vector3{ -12.5f,5.75f,457.5f });
		s6elevator2->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s6elevator2->SetTarget(Vector3{ -12.5f,5.75f,477.5f });
		s6elevator2->SetVelocity(Vector3{ 0.0f,0.0f, 250000.0f });
		s6elevator2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator2->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");

		Cube_LD_Movable* s6elevator3 = AddActor<Cube_LD_Movable>();
		s6elevator3->SetRigidbodyPosition(Vector3{ 16.0f,6.0f,467.5f });
		s6elevator3->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s6elevator3->SetTarget(Vector3{ 16.0f,10.0f,467.5f });
		s6elevator3->SetVelocity(Vector3{ 0.0f,600000.0f, 0.0f });
		s6elevator3->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator3->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");

		Cube_LD_Movable* s6elevator4 = AddActor<Cube_LD_Movable>();
		s6elevator4->SetRigidbodyPosition(Vector3{ -16.0f,6.0f,467.5f });
		s6elevator4->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s6elevator4->SetTarget(Vector3{ -16.0f,10.0f,467.5f });
		s6elevator4->SetVelocity(Vector3{ 0.0f,600000.0f, 0.0f });
		s6elevator4->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator4->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");

		Cube_LD_Movable* s6elevator5 = AddActor<Cube_LD_Movable>();
		s6elevator5->SetRigidbodyPosition(Vector3{ -12.0f,9.5f,467.5f });
		s6elevator5->SetRigidbodyScale(Vector3{ 3.0f,0.5f,3.0f });
		s6elevator5->SetTarget(Vector3{ 12.0f,9.5f,467.5f });
		s6elevator5->SetVelocity(Vector3{ 350000.0f,0.0f, 0.0f });
		s6elevator5->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator5->GetComponentByClass<Component_Cube>()->SetTexture("Metal1");

		//エレベーター踊り場
		Cube_LD* s6SideBlock4 = AddActor<Cube_LD>();
		s6SideBlock4->SetRigidbodyPosition(Vector3{ 0.0f,9.5f,461.75f });
		s6SideBlock4->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s6SideBlock4->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);
		s6SideBlock4->GetComponentByClass<Component_Cube>()->SetTexture("Blue");

		FallFloor* s6SideBlock5 = AddActor<FallFloor>();
		s6SideBlock5->SetRigidbodyPosition(Vector3{ 0.0f,9.5f,473.25f });
		s6SideBlock5->SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });
		s6SideBlock5->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_GLASS);
		s6SideBlock5->GetComponentByClass<Component_Cube>()->SetTexture("Red");

		//階段
		for(int i = 0; i <  7; i++)
		{
			Cube_LD* s6SideBlock6 = AddActor<Cube_LD>();
			s6SideBlock6->SetRigidbodyPosition(Vector3{ 0.0f,9.75f + 0.25f * i,456.5f - 2.0f * i });
			s6SideBlock6->SetRigidbodyScale(Vector3{ 8.5f,0.25f,2.0f });
			s6SideBlock6->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
			s6SideBlock6->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");

			Cube_LD* s6SideBlock7 = AddActor<Cube_LD>();
			s6SideBlock7->SetRigidbodyPosition(Vector3{ 0.0f,9.75f + 0.25f * i,478.5f + 2.0f * i });
			s6SideBlock7->SetRigidbodyScale(Vector3{ 8.5f,0.25f,2.0f });
			s6SideBlock7->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
			s6SideBlock7->GetComponentByClass<Component_Cube>()->SetTexture("Metal3");
		}

		//エレベーター
		Cube_LD_Movable* s6elevator6 = AddActor<Cube_LD_Movable>();
		s6elevator6->SetRigidbodyPosition(Vector3{ 0.0f,11.5f,443.0f });
		s6elevator6->SetRigidbodyScale(Vector3{ 8.5f,0.25f,1.0f });
		s6elevator6->SetTarget(Vector3{ 0.0f,17.5f,443.0f });
		s6elevator6->SetVelocity(Vector3{ 0.0f,300000.0f, 0.0f });
		s6elevator6->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator6->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");

		Cube_LD_Movable* s6elevator7 = AddActor<Cube_LD_Movable>();
		s6elevator7->SetRigidbodyPosition(Vector3{ 0.0f,11.5f,492.0f });
		s6elevator7->SetRigidbodyScale(Vector3{ 8.5f,0.25f,1.0f });
		s6elevator7->SetTarget(Vector3{ 0.0f,17.5f,492.0f });
		s6elevator7->SetVelocity(Vector3{ 0.0f,300000.0f, 0.0f });
		s6elevator7->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_METAL);
		s6elevator7->GetComponentByClass<Component_Cube>()->SetTexture("Metal2");

		//床3
		Cube_LD* s6Floor3 = AddActor<Cube_LD>();
		s6Floor3->SetRigidbodyPosition(Vector3{ 0.0f,17.5f,467.5f });
	    s6Floor3->SetRigidbodyScale(Vector3{ 50.0f,0.25f,48.0f });
		s6Floor3->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);
		s6Floor3->GetComponentByClass<Component_Cube>()->SetTexture("Wood");

		//ゴール
		Goal* goal = AddActor<Goal>();
		goal->SetPosition(Vector3{ 0.0f,18.25f,467.5f });

		//ガイド
		Cube_LD* s6guide1 = AddActor<Cube_LD>();
		s6guide1->SetRigidbodyPosition(Vector3{ 0.0f,17.9f,467.5f });
		s6guide1->SetRigidbodyScale(Vector3{ 0.1f,0.5f,0.1f });
		s6guide1->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s6guide1->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube_LD* s6guide2 = AddActor<Cube_LD>();
		s6guide2->SetRigidbodyPosition(Vector3{ 0.0f,18.25f,467.5f });
		s6guide2->SetRigidbodyScale(Vector3{ 0.8f,0.45f,0.2f });
		s6guide2->GetComponentByClass<Component_Cube>()->SetTexture("Wood");
		s6guide2->GetComponentByClass<Component_OBB>()->SetPhysicsMaterial(PM_WOOD);

		Cube* s6guide3 = AddActor<Cube>();
		s6guide3->SetPosition(Vector3{ 0.0f,18.25f,467.4f });
		s6guide3->SetScale(Vector3{ 0.8f,0.45f,0.001f });
		s6guide3->GetComponentByClass<Component_Cube>()->SetTexture("Guide8");
		s6guide3->GetComponentByClass<Component_Cube>()->SetTexLoop(false);

#pragma endregion

		//キャラクター追加
		Character* character = AddActor<Character>();
		//初期座標
		character->SetRigidbodyPosition({ 0.0f,3.0f,-3.5f });

		//大気追加
		AddActor<Atomosphere>();

		//カメラ追加
		Camera* main_camera = AddActor<Camera>();
		//注視点にキャラクターにセット
		main_camera->SetOwner(character);
		//初期回転角度
		main_camera->SetRotation(Vector3{DegToRad(4.8f),DegToRad(160.0f),DegToRad(0.0f)});
		//初期カメラ距離
		main_camera->AddTargetLength(-100.0f);

		//HUDをHUD_Titleに設定
		manager_Drawer->SetHUD<HUD_Title>();
	}

}

//=============================================================================
// 更新関数
//=============================================================================
void Level_Game::Update()
{
	//基底クラス更新
	Level::Update();
}

//=============================================================================
// 終了関数
//=============================================================================
void Level_Game::Uninit()
{
	//リソース解放

	//オーディオマネージャーキャッシュ
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//BGM解放
		manager_audio->Unload_Resource("Moonlight");
	}

	//爆発ビルボードクラスリソース解放
	Explosion::Unload();

	//落ちる床クラスリソース解放
	FallFloor::Unload();

	//レベルデザインキューブクラスリソース解放
	Cube_LD::Unload();

	//キューブクラスリソース解放
	Cube::Unload();

	//大気クラスリソース解放
	Atomosphere::Unload();

	//銃クラスリソース解放
	Gun::Unload();

	//キャラクタークラスリソース解放
	Character::Unload();

	//基底クラス終了
	Level::Uninit();

};