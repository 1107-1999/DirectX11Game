//=============================================================================
//
//  プレイヤーコントローラー(キーマッピング) [PlayerConroller.h]
//  Date   : 2021/12/24 oh.....
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "PlayerController.h"
#include "../../System/Math.h"
#include "../../System/MainWindow.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float EFFECTIVE_VALUE = 1.0f;//入力時の値

//=============================================================================
// 初期化関数
//=============================================================================
void PlayerController::Init()
{
	//インプットキャッシュ
	m_Input = Input::Instance();

	//Windowキャッシュ
	m_MainWindow = MainWindow::Instance();
}


//=============================================================================
// 前後移動キーマッピング
//=============================================================================
float PlayerController::MoveForward()
{
	float value = 0.0f;

	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyPress('W') || m_Input->GetGamepad_State(Input::GAMEPAD_1).LEFT_STICK_Y == Input::STICK_UP)
		{//前進
			value += EFFECTIVE_VALUE;
		}
		if (m_Input->GetKeyPress('S') || m_Input->GetGamepad_State(Input::GAMEPAD_1).LEFT_STICK_Y == Input::STICK_DOWN)
		{//後進
			value -= EFFECTIVE_VALUE;
		}
	}
	return value;
}

//=============================================================================
// 左右移動キーマッピング
//=============================================================================
float PlayerController::MoveRight()
{
	float value = 0.0f;

	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyPress('D') || m_Input->GetGamepad_State(Input::GAMEPAD_1).LEFT_STICK_X == Input::STICK_RIGHT)
		{//右移動
			value += EFFECTIVE_VALUE;
		}

		if (m_Input->GetKeyPress('A') || m_Input->GetGamepad_State(Input::GAMEPAD_1).LEFT_STICK_X == Input::STICK_LEFT)
		{//左移動
			value -= EFFECTIVE_VALUE;
		}
	}
	return value;
}

//=============================================================================
// カメラ左右キーマッピング
//=============================================================================
float PlayerController::Turn()
{
	float value = 0.0f;

	if (m_Input != nullptr)
	{
		//パッド
		if (m_Input->GetGamepad_State(Input::GAMEPAD_1).RIGHT_STICK_X == Input::STICK_RIGHT)
		{//右入力
			return  m_Gamepad_Sensi;
		}
		else if (m_Input->GetGamepad_State(Input::GAMEPAD_1).RIGHT_STICK_X == Input::STICK_LEFT)
		{//左入力
			return -m_Gamepad_Sensi;
		}
		//マウス
		if (m_Input->GetMouse_State().x > HalfSize(m_MainWindow->GetWindowSize().x))
		{//右回転
			value -= static_cast<float>(m_Input->GetMouse_State().x) * m_Mouse_Sensi;
		}
		if (m_Input->GetMouse_State().x < HalfSize(m_MainWindow->GetWindowSize().x))
		{//左回転
			value += static_cast<float>(m_Input->GetMouse_State().x) * m_Mouse_Sensi;
		}
	
	}
	return value;
}

//=============================================================================
// カメラ上下キーマッピング
//=============================================================================
float PlayerController::LookUp()
{
	if (m_Input != nullptr)
	{
		//パッド
		if (m_Input->GetGamepad_State(Input::GAMEPAD_1).RIGHT_STICK_Y == Input::STICK_DOWN)
		{//下入力
			return  m_Gamepad_Sensi;
		}
		else if (m_Input->GetGamepad_State(Input::GAMEPAD_1).RIGHT_STICK_Y == Input::STICK_UP)
		{//上入力
			return -m_Gamepad_Sensi;
		}
		//マウス
		else if (m_Input->GetMouse_State().y > HalfSize(m_MainWindow->GetWindowSize().y))	//マウス
		{//下回転
			return  -static_cast<float>(m_Input->GetMouse_State().y) * m_Mouse_Sensi;
		}
		else
		{//上回転
			return   static_cast<float>(m_Input->GetMouse_State().y) * m_Mouse_Sensi;
		}
	}
	return 0.0f;
}

//=============================================================================
// カメラズームキーマッピング
//=============================================================================
float PlayerController::Zoom()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetMouse_State().scrollWheelValue > 0)
		{//マウスホイールテストでポーズ処理
			m_Input->Mouse_ResetScrollWheelValue();
			return -ZOOM_SPEED;
		}
		else if (m_Input->GetMouse_State().scrollWheelValue < 0)
		{//マウスホイールテストでポーズ処理
			m_Input->Mouse_ResetScrollWheelValue();
			return  ZOOM_SPEED;
		}
		else if (m_Input->GetGamepad_State(Input::GAMEPAD_1).LT_BUTTON)
		{
			return  ZOOM_SPEED;
		}
		else if (m_Input->GetGamepad_State(Input::GAMEPAD_1).RT_BUTTON)
		{
			return  -ZOOM_SPEED;
		}
	}
	return 0.0f;
}

//=============================================================================
// メインアクションキーマッピング
//=============================================================================
bool PlayerController::InputAction_Main()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetMouse_State().leftButton || m_Input->GetGamepad_State(Input::GAMEPAD_1).B_BUTTON)
		{
			return true;
		}
	}
	return false;
}


//=============================================================================
// セカンドアクションキーマッピング
//=============================================================================
bool PlayerController::InputAction_Second()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetMouse_State().rightButton)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// スプリントキーマッピング
//=============================================================================
bool PlayerController::InputAction_Sprint()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyPress(VK_SHIFT) || m_Input->GetGamepad_State(Input::GAMEPAD_1).LB_BUTTON)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// ジャンプキーマッピング
//=============================================================================
bool PlayerController::InputAction_Jump()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyTrigger(VK_SPACE) || m_Input->GetGamepad_State(Input::GAMEPAD_1).A_BUTTON)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// ポーズキーマッピング
//=============================================================================
bool PlayerController::InputAction_Pause()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyTrigger(VK_CONTROL) || m_Input->GetGamepad_State(Input::GAMEPAD_1).START_BUTTON)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// 使用キーマッピング
//=============================================================================
bool PlayerController::InputAction_Use()
{
	if (m_Input != nullptr)
	{
		if (m_Input->GetKeyTrigger('F') || m_Input->GetGamepad_State(Input::GAMEPAD_1).X_BUTTON)
		{
			return true;
		}
	}
	return false;
}