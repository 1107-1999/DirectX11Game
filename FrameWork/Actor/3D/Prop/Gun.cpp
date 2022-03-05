//=============================================================================
//
//  銃クラス [Gun.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Gun.h"
#include "../Camera.h"
#include "../ActorRB/Prop/GunTarget.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../Component/Component_OBB.h"
#include "../../../Manager/Manager_Game.h"
#include "../../../Manager/Manager_Actor/Manager_Bullet.h"
#include "../../../Level/Base/Level.h"
#include "../../../Sound/GunFire.h"
#include "../../../PlayerController/PC_Game.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float BULLET_SPEED       = 12.0f;//弾速
constexpr float RECOIL_POWER_YAW   = 0.005f;  //YAWリコイル
constexpr float RECOIL_POWER_PITCH = -0.025f; //Pitchリコイル
constexpr int   RECOIL_COUNT       = 12;      //リコイル発生にかけるフレーム数
constexpr int   RECOIL_PATTERN     = 2;       //リコイルの種類

//=============================================================================
// リソース読み込み・削除関数
//=============================================================================
void  Gun::Load()
{
	//銃声読み込み
	GunFire::Load();
}
void  Gun::Unload()
{
	//銃声削除
	GunFire::Unload();
}

//=============================================================================
// 初期化関数
//=============================================================================
void  Gun::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//静的メッシュコンポーネント追加
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//静的メッシュコンポーネントnullチェック
	if (m_Component_StaticMesh != nullptr)
	{
		//モデルロード
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Sniper.fbx");

		//回転オフセット調整
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(90.0f),DegToRad(-95.0f),DegToRad(0.0f) });

		//スケールオフセット調整
		m_Component_StaticMesh->SetScaleRate(0.01f);
	}

	//OBBコンポーネント追加
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//リジッドボディと同スケールに調整
		m_Component_OBB->SetScale(Vector3{ 2.0f,0.25f,2.0f });

		//座標オフセット調整
		m_Component_OBB->SetPositionOffset(Vector3{ 0.0f,0.0f,-0.6f });

		//レイコリジョンを無視
		m_Component_OBB->SetIsReactRay(false);

		//物理マテリアルを無効
		m_Component_OBB->SetPhysicsMaterial(PM_IGNORE);
	}

	//プレイヤーコントローラーを取得&キャストしてキャッシュ
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());

	//弾管理クラスをレベルに追加してキャッシュ
	m_Manager_Bullet = Manager_Game::Instance()->GetLevel()->AddManager_Actor<Manager_Bullet>();

	//銃声クラス生成
	m_GunFire = new GunFire;

	//銃声クラスnullチェック
	if (m_GunFire != nullptr)
	{
		//銃声クラス初期化
		m_GunFire->Init();
	}

	//リコイルカウント初期化
	m_RecoilCount = 0;

	//リコイル右向き
	m_RecoilVectorRight = true;

}

//=============================================================================
// 更新関数
//=============================================================================
void Gun::Update()
{
	//プレイヤーコントローラーnullチェック
	if (m_PlayerConroller != nullptr)
	{
	    //プレイヤーと接触している場合
		if (m_Component_OBB->GetOverlap())
		{
			//プレイヤーコントローラーに銃とのオーバーラップ判定を渡す
			m_PlayerConroller->SetGunFlag(true);

		}
		//プレイヤーと接触していない場合
		else
		{
			//プレイヤーコントローラーの銃とのオーバーラップ判定を消す
			m_PlayerConroller->SetGunFlag(false);

		}
	}
	else//nullの場合キャッシュ
	{
		//プレイヤーコントローラーを取得&キャストしてキャッシュ
		m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());
	}

	if (m_RecoilCount > 0)
	{
		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{
			//Yawリコイル方向で分岐
			if (m_RecoilVectorRight)
			{
				//右にリコイル
				camera->AddCameraYaw(RECOIL_POWER_YAW);
			}
			else
			{
				//左にリコイル
				camera->AddCameraYaw(-RECOIL_POWER_YAW);
			}

			//Pitchリコイル
			camera->AddCameraPitch(RECOIL_POWER_PITCH);

			//リコイル時間減少
			m_RecoilCount--;
		}
	}

	//親クラス更新
	Actor3D::Update();
}

//=============================================================================
// 終了関数
//=============================================================================
void Gun::Uninit()
{
	//銃声クラス終了
	if (m_GunFire != nullptr)
	{
		m_GunFire->Uninit();
		delete m_GunFire;
		m_GunFire = nullptr;
	}

	//親クラス更新
	Actor3D::Uninit();
}

//=============================================================================
// 射撃関数
//=============================================================================
void Gun::Shot()
{
	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr && m_RecoilCount == 0)
	{

		//リコイル発生
		m_RecoilCount = RECOIL_COUNT;

		//Yawリコイル方向で分岐
		int random = rand() % RECOIL_PATTERN;

		switch (random)
		{
		case 0:
			//リコイル右向き
			m_RecoilVectorRight = true;
			break;

		case 1:
			//リコイル左向き
			m_RecoilVectorRight = false;
			break;

		}

		//カメラ座標キャッシュ
		Vector3 cameraPosition = Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetPosition();

		//カメラ前方向ベクトルキャッシュ
		Vector3 cameraForward = Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetForward();

		//レイの無視レイヤーのリスト
		std::list<ACTOR_TYPE>rocalIgnoreList;
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_PLAYER);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_GUN);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_BULLET);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_BLOCK);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_CAMERA);
		rocalIgnoreList.push_back(ACTOR_TYPE::MAX_ACTOR_TYPE);

	    //レイでアクターを取得
		s_HIT_Result hit_result = m_Component_OBB->RaycastHighAccuracy(cameraPosition, cameraPosition + cameraForward * 100.0f, this, true,
			rocalIgnoreList,
			Color(1, 0, 1, 1));

		if (GunTarget* target = dynamic_cast<GunTarget*>(hit_result.hitActor))
		{
			//OBB取得
			if (Component_OBB* target_OBB = target->GetComponentByClass<Component_OBB>())
			{
				target_OBB->SetOverlap(true);

			}
		}

		//弾マネージャー
		if (m_Manager_Bullet != nullptr)
		{
			//弾生成
			m_Manager_Bullet->SpawnBullet(cameraPosition, cameraForward, Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetRotation());
		}


		//銃声クラスnullチェック
		if (m_GunFire != nullptr)
		{
			//銃声再生
			m_GunFire->Play();
		}

	}

}