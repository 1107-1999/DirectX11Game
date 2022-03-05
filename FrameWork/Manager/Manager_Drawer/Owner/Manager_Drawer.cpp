//=============================================================================
//
//  描画マネージャー [Manager_Drawer.cpp]
//  Date   : 2021/11/16
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <string>
#include "Manager_Drawer.h"
#include "../Manager_Cube.h"
#include "../Manager_Model.h"
#include "../Manager_Billboard.h"
#include "../Manager_Sprite.h"
#include "../Manager_Fade.h"
#include "../Manager_OBB.h"
#include "../Manager_Rigidbody.h"
#include "../Manager_ImGui.h"
#include "../Manager_Font2D.h"
#include "../../Manager_Game.h"
#include "../../../Level/Base/Level.h"
#include "../../../System/MainWindow.h"
#include "../../../System/Color.h"
#include "../../../System/Exchanger.h"
#include "../../../Actor/3D/Camera.h"
#include "../../../Actor/HUD/Base/HUD.h"
#include "../../../Renderer/Renderer_DirectX11.h"

//=============================================================================
// 定数定義
//=============================================================================
const Vector3 LIGHT_OFFSET = { -5.0f, 12.5f, -10.0f };//ライト座標

//=============================================================================
// 初期化関数
//=============================================================================
void Manager_Drawer::Init()
{
	//DirextX11描画機構クラスをキャッシュ
	m_Renderer_DX11 = Renderer_DirectX11::Instance();

	//各種マネージャー初期化
	m_Manager_Model     = nullptr;//モデルマネージャーnullptr化
	m_Manager_Billboard = nullptr;//ビルボードマネージャーnullptr化
	m_Manager_Sprite    = nullptr;//スプライトマネージャーnullptr化
	m_Manager_OBB       = nullptr;//OBBマネージャーnullptr化
	m_Manager_Rigidbody = nullptr;//剛体マネージャーnullptr化
	m_HUD               = nullptr;//HUDをnullptr化
	m_Manager_Font2D    = Manager_Font2D::Instance();//キャッシュ


	m_Manager_Fade      = new Manager_Fade;//フェードマネージャー生成
	m_Manager_Fade->Init();//フェードマネージャー初期化
	m_Manager_Fade->SetFade(Manager_Fade::FADE_IN, 3.0f);

	m_Manager_ImGui = Manager_ImGui::Instance();//ImGuiマネージャーキャッシュ

	m_DebugDraw     = false;//デバッグコリジョン非表示
	m_DebugCube     = false;//デバッグキューブ非表示                             

	//光源計算
	m_Light = new LIGHT;

	//ステータス
	m_Light->Enable = true;
	m_Light->Direction = Vector4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&m_Light->Direction, &m_Light->Direction);
	m_Light->Ambient   = Color(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light->Diffuse   = Color(1.0f, 1.0f, 1.0f, 1.0f);

	Int2 windowSize = MainWindow::Instance()->GetWindowSize();

	//2次元サイズ初期値
	Vector2 Scale2D = Vector2{ static_cast<float>(windowSize.x),static_cast<float>(windowSize.y) };

	//ライトカメラのビュー行列を作成
	D3DXMatrixLookAtLH(&m_Light->ViewMatrix, &LIGHT_OFFSET,
		&Vector3(0.0f, 0.0f, 0.0f), &Vector3(0.0f, 1.0f, 0.0f));

	//ライトカメラのプロジェクション行列を作成
	D3DXMatrixPerspectiveFovLH(&m_Light->ProjectionMatrix, 1.0f,
		Scale2D.x / Scale2D.y, 5.0f, 30.0f);

	//デバッグウィンドウ作成
	Window_ImGui* debugWindow = Manager_ImGui::Instance()->CreateGuiWindow("Manager_Drawer");
	Vector4 tempColor = ColorSpace::Yellow;
	std::string tempColorString = Exchanger::VEC4_TO_STRING(tempColor);
	debugWindow->DebugLog(tempColorString, "none", tempColor);

	//デバッグコリジョン
	debugWindow->SendBoolData(&m_DebugDraw, "DebugCollision");

	//デバッグキューブ
	debugWindow->SendBoolData(&m_DebugCube, "DebugCube");


}

//=============================================================================
// アクター更新前の更新関数
//=============================================================================
void Manager_Drawer::UpdateBefore()
{
	//剛体更新
	if (m_Manager_Rigidbody != nullptr)
	{
		m_Manager_Rigidbody->Update();
	}
}

//=============================================================================
// アクター更新後の更新関数
//=============================================================================
void Manager_Drawer::UpdateAfter()
{
	//ライトnullチェック
	if (m_Light != nullptr)
	{
		//カメラがある場合
		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{
			//ステータス
			m_Light->Enable = true;
			m_Light->Direction = Vector4(1.0f, -1.0f, 1.0f, 0.0f);
			D3DXVec4Normalize(&m_Light->Direction, &m_Light->Direction);
			m_Light->Ambient = Color(0.1f, 0.1f, 0.1f, 1.0f);
			m_Light->Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);

			//ウィンドウサイズ取得
			Int2 windowSize = MainWindow::Instance()->GetWindowSize();

			//2次元サイズ初期値
			Vector2 Scale2D = Vector2{ static_cast<float>(windowSize.x),static_cast<float>(windowSize.y) };

			//オーナー座標
			Vector3 position = camera->GetOwner()->GetPosition();

			//ライトカメラのビュー行列を作成
			D3DXMatrixLookAtLH(&m_Light->ViewMatrix, &Vector3(LIGHT_OFFSET.x + position.x, LIGHT_OFFSET.y + position.y, LIGHT_OFFSET.z + position.z),
				&position, &Vector3(0.0f, 1.0f, 0.0f));

			//ライトカメラのプロジェクション行列を作成
			D3DXMatrixPerspectiveFovLH(&m_Light->ProjectionMatrix, 1.0f,
				Scale2D.x / Scale2D.y, 5.0f, 30.0f);
		}	
	}

	//HUD更新
	if (m_HUD != nullptr)
	{
		m_HUD->Update();
	}
	//OBBマネージャー更新
	if (m_Manager_OBB != nullptr)
	{
		m_Manager_OBB->Update();
	}
	//フェード更新
	if (m_Manager_Fade != nullptr)
	{
		m_Manager_Fade->Update();
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void Manager_Drawer::Draw()
{
	if (m_Renderer_DX11 != nullptr)
	{//DirextX11描画機構クラスがある場合

	    //光源設定
		m_Renderer_DX11->SetLight(*m_Light);

		//ビュー設定
		m_Renderer_DX11->SetViewMatrix(&m_Light->ViewMatrix);
		m_Renderer_DX11->SetProjectionMatrix(&m_Light->ProjectionMatrix);
		

		//影描画開始
		m_Renderer_DX11->BeginDepth();

		//影対応3Dモデル描画
		Draw3D();

		//通常描画開始
		m_Renderer_DX11->Begin();

		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{//カメラがある場合

			//カメラ視点設定
			camera->SetView();

			//3Dモデル描画
			Draw3D();

			//ビルボード描画
			if (m_Manager_Billboard != nullptr)
			{
				m_Manager_Billboard->Draw();
			}
			//デバッグ表示オンならコリジョン描画
			if (m_DebugDraw)
			{
				//剛体描画
				if (m_Manager_Rigidbody != nullptr)
				{
					m_Manager_Rigidbody->Draw();
				}

				//OBB&レイ描画
				if (m_Manager_OBB != nullptr)
				{
					m_Manager_OBB->Draw();
				}
			}


		}
		//スプライト描画
		if (m_Manager_Sprite != nullptr)
		{
			m_Manager_Sprite->Draw();
		}
		//フォント2D
		{
			m_Manager_Font2D->Draw();
		}
		//HUD描画
		if (m_HUD != nullptr)
		{
			m_HUD->Draw();
		}
	
		//フェード描画
		if (m_Manager_Fade != nullptr)
		{
			m_Manager_Fade->Draw();
		}
		//ImGUI描画
		if (m_Manager_ImGui != nullptr)
		{
			m_Manager_ImGui->Draw();
		}

		//描画終了
		m_Renderer_DX11->End();
	}
}


//=============================================================================
// 終了関数
//=============================================================================
void Manager_Drawer::Uninit()
{

	//光源終了
	if (m_Light != nullptr)
	{
		delete m_Light;//削除
		m_Light = nullptr;//nullptr代入
	}

	//キューブマネージャー終了
	if (m_Manager_Cube != nullptr)
	{
		m_Manager_Cube->Uninit();//終了
		delete m_Manager_Cube;//削除
		m_Manager_Cube = nullptr;//nullptr代入
	}
	//モデルマネージャー終了
	if (m_Manager_Model != nullptr)
	{
		m_Manager_Model->Uninit();//終了
		delete m_Manager_Model;//削除
		m_Manager_Model = nullptr;//nullptr代入
	}
	//ビルボードマネージャー終了
	if (m_Manager_Billboard != nullptr)
	{
		m_Manager_Billboard->Uninit();//終了
		delete m_Manager_Billboard;//削除
		m_Manager_Billboard = nullptr;//nullptr代入
	}
	//OBBマネージャー終了
	if (m_Manager_OBB != nullptr)
	{
		m_Manager_OBB->Uninit();//終了
		delete m_Manager_OBB;//削除
		m_Manager_OBB = nullptr;//nullptr代入
	}
	//剛体マネージャー終了
	if (m_Manager_Rigidbody != nullptr)
	{
		m_Manager_Rigidbody->Uninit();//終了
		delete m_Manager_Rigidbody;//削除
		m_Manager_Rigidbody = nullptr;//nullptr代入
	}
	//スプライトマネージャー終了
	if (m_Manager_Sprite != nullptr)
	{
		m_Manager_Sprite->Uninit();//終了
		delete m_Manager_Sprite;//削除
		m_Manager_Sprite = nullptr;//nullptr代入
	}
	//HUD終了
	if (m_HUD != nullptr)
	{
		m_HUD->Uninit();//終了
		delete m_HUD;//削除
		m_HUD = nullptr;//nullptr代入
	}

	//フェードマネージャー終了
	if (m_Manager_Fade != nullptr)
	{
		delete m_Manager_Fade;//削除
		m_Manager_Fade = nullptr;//nullptr代入
	}

	Manager_ImGui::Instance()->Uninit();//リストを全てクリア
}

//=============================================================================
// 描画関数(3Dオブジェクトのみ)
//=============================================================================
void Manager_Drawer::Draw3D()
{
	//キューブ描画
	if (m_Manager_Cube != nullptr)
	{
		m_Manager_Cube->Draw();
	}

	//モデル描画
	if (m_Manager_Model != nullptr)
	{
		m_Manager_Model->Draw();
	}
}


//=============================================================================
// マネージャー追加関数
//=============================================================================
//キューブマネージャー追加
void Manager_Drawer::AddManager_Cube()
{
	m_Manager_Cube = new Manager_Cube;
}
//モデルマネージャー追加
void Manager_Drawer::AddManager_Model()
{
	m_Manager_Model = new Manager_Model;
}
//ビルボードマネージャー追加
void Manager_Drawer::AddManager_Billboard()
{
	m_Manager_Billboard = new Manager_Billboard;
}
//スプライトマネージャー追加
void Manager_Drawer::AddManager_Sprite()
{
	m_Manager_Sprite = new Manager_Sprite;
}
//OBBマネージャー追加
void Manager_Drawer::AddManager_OBB()
{
	m_Manager_OBB = new Manager_OBB;
}

//剛体マネージャー追加
void Manager_Drawer::AddManager_Rigidbody()
{
	m_Manager_Rigidbody = new Manager_Rigidbody;
	m_Manager_Rigidbody->Init();//初期化
}

