//==============================================================================
//
//  ゲームシーン用プレイヤーコントローラー [PC_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "PC_Game.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../System/Main.h"
#include "../System/MainWindow.h"
#include "../Level/Base/Level.h"
#include "../Level/Level_Game.h"
#include "../Level/Level_Title.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/Prop/Gun.h"
#include "../Actor/HUD/HUD_Game.h"
#include "../Component/Component_Model/Component_StaticMesh.h"
#include "../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float ONE_FRAME_LERP_RATE = 0.005f;//1フレームに補完する比率

//=============================================================================
// 初期化関数
//=============================================================================
void PC_Game::Init()
{
	//基底クラス初期化
	PlayerController::Init();

	//マウス相対座標モードに変更
	if (m_Input != nullptr)
	{
		m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_RELATIVE);
	}

	//スコープフラグ初期化
	m_ScopeFlag = false;

	//銃モードフラグ初期化
	m_GunFlag = false;

	//射撃フラグ初期化
	m_ShotFlag = false;

	//ゴールフラグ初期化
	m_GoalFlag = false;  

}

//=============================================================================
// 更新関数
//=============================================================================
void PC_Game::Update()
{
	if (m_Input != nullptr)
	{
		if (InputAction_Pause())
		{//ポーズ処理
			if (m_Input->GetMouse_PositionMode() == Input::MOUSE_POSITION_MODE_RELATIVE)
			{
				m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_ABSOLUTE);
			}
			else
			{
				m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_RELATIVE);
			}
		}

		if (m_Input->GetMouse_PositionMode() == Input::MOUSE_POSITION_MODE_RELATIVE)
		{//相対座標モードならプレイヤー操作
			if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
			{
				if (!m_ScopeFlag)
				{//非スコープ操作

					if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
					{//キャラクターがレベルに存在する場合

						//=============================================================================
						//軸移動
						//=============================================================================

						character->MoveAxis(MoveForward(), MoveRight());

						//=============================================================================
						//カメラ制御
						//=============================================================================

						//Yaw軸カメラ角度
						if (camera->GetOrientRotationtoMovement())
						{//常にプレイヤーがカメラ方向を向く
							character->MoveRotation(Turn());
						}
						else
						{//オーソドックスなサードパーソンビュー
							camera->AddCameraYaw(Turn());
						}
						//Pitch軸カメラ角度
						camera->AddCameraPitch(LookUp());

						//カメラ距離
						camera->AddTargetLength(Zoom());

						//=============================================================================
						//アクション
						//=============================================================================

						if (InputAction_Jump())
						{//ジャンプ
							character->Jump();
						}

						//スプリント
						character->Sprint(InputAction_Sprint());

						if (InputAction_Main())
						{//メインアクション

							//ゴールフラグチェック
							if (m_GoalFlag)
							{
								//タイトルシーンセット
								character->SetRigidbodyPosition({ 0.0f,3.0f,-3.5f });
							}
						}

						//セカンドアクション
						if (InputAction_Second())
						{
							if (m_GunFlag)
							{//銃が近くにある

								//スコープフラグオン
								m_ScopeFlag = true;

								if (HUD_Game* hud = dynamic_cast<HUD_Game*>(Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetHUD()))
								{
									//スコープのUIを表示
									hud->SetScopeUI(m_ScopeFlag);

									//プレイヤー非表示
									character->GetComponentByClass<Component_SkeletalMesh>()->SetActive(false);

									//プレイヤー停止
									character->MoveAxis(0.0f, 0.0f);

									if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
									{
										//銃非表示
										gun->GetComponentByClass<Component_StaticMesh>()->SetActive(false);
										//カメラを一人称に設定
										camera->SetFirstPerson(true);
										//カメラのオーナーに銃をセット
										camera->SetOwner(gun);

									}
								}
							}
						}
					}
				}
				else
				{
			
					//Pitch軸カメラ角度
					camera->AddCameraPitch(LookUp());
					//Yaw軸カメラ角度
					camera->AddCameraYaw(Turn());
						
					//スコープズーム
					camera->SetFOV(camera->GetFOV() + Zoom());
				

					if (InputAction_Main())
					{//メインアクション

						m_ShotFlag = true;

					}
					else if(m_ShotFlag)
					{
						if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
						{
							gun->Shot();
							m_ShotFlag = false;
						}
					}
				
					if (!InputAction_Second())
					{//セカンドアクションを押していない

						if (m_GunFlag)
						{//銃が近くにある

							//スコープフラグオフ
							m_ScopeFlag = false;

							//ゲームHUD取得
							if (HUD_Game* hud = dynamic_cast<HUD_Game*>(Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetHUD()))
							{

								//視野角初期化
								camera->SetFOV(DEFAULT_FOV);

								//スコープのUIを削除
								hud->SetScopeUI(m_ScopeFlag);

								if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
								{
									//プレイヤー表示
									character->GetComponentByClass<Component_SkeletalMesh>()->SetActive(true);
									//カメラを三人称に設定
									camera->SetFirstPerson(false);
									//カメラのオーナーにキャラクターをセット
									camera->SetOwner(character);
								}

								//非表示
								if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
								{
									gun->GetComponentByClass<Component_StaticMesh>()->SetActive(true);
								}
							}

						}		
					}
				}
			}
		}
	}
}
