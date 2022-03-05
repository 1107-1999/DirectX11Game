//=============================================================================
//
//  プレイヤーコントローラー(キーマッピング) [PlayerConroller.h]
//  Date   : 2021/10/13
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../System/Input.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float ZOOM_SPEED = 0.25f;

//=============================================================================
// クラス定義
//=============================================================================
class PlayerController
{
protected :

	class Input* m_Input;           //インプットキャッシュ
	class MainWindow* m_MainWindow; //Windowキャッシュ

	float m_Mouse_Sensi   = 0.002f;//マウス感度
	float m_Gamepad_Sensi = 0.04f; //ゲームパッド感度

	//前後移動キーマッピング
	float MoveForward();

	//左右移動キーマッピング
	float MoveRight();
	
	//カメラ左右キーマッピング
	float Turn();
	
	//カメラ上下キーマッピング
	float LookUp();

	//カメラズームキーマッピング
	float Zoom();

	//メインアクションキーマッピング
	bool InputAction_Main();

	//セカンドアクションキーマッピング
	bool InputAction_Second();

	//スプリントキーマッピング
	bool InputAction_Sprint();

	//ジャンプキーマッピング
	bool InputAction_Jump();

	//ポーズキーマッピング
	bool InputAction_Pause();

	//使用キーマッピング
	bool InputAction_Use();

public:

	//初期化
	virtual void Init();

	//更新純粋仮想関数
	virtual void Update() = 0;

};
