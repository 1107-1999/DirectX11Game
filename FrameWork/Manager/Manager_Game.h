//=============================================================================
//
//  ゲームマネージャー [Manager_Game.h]
//  Date   : 2021/11/02
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <vector>
#include "../System/Singleton.h"
#include "../Level/Base/Level.h"
#include "../PlayerController/Base/PlayerController.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Game : public Singleton<Manager_Game>
{
private: 
	friend class Singleton<Manager_Game>;//シングルトン

	class Level*             m_Level;    //現在のレベル
	class Level*             m_NextLevel;//次のレベル

	class PlayerController*  m_PlayerController;//プレイヤーコントローラー

public:

	//初期化・更新・終了
	void Init();  
	void Update();
	void Uninit();

	//描画
	void Draw(); 

	inline class Level*            GetLevel()            const { return m_Level;}            //現在のレベル取得
	inline class PlayerController* GetPlayerController() const { return m_PlayerController; }//現在のプレイヤーコントローラー取得


	//レベル変更関数(フェードあり)
	template <typename T>
	void LoadLevelByClass(float _time)
	{
		m_NextLevel = new T();//レベル作成

		//現在のレベルがある場合フェード開始
		if (m_Level != nullptr)
		{
			m_Level->SetFade(_time);
		}
		else if (m_NextLevel != nullptr)
		{//現在のレベルない場合

			//レベル読み込み	
			m_Level = m_NextLevel;//読み込み
			m_Level->Init();//初期化

		}
	}

	//次のレベルに変更
	void OpenLevel()
	{
		//現在のレベルがある場合終了
		if (m_Level != nullptr)
		{
			m_Level->Uninit();//終了
			delete m_Level;//削除
			m_Level = nullptr;//nullptr代入
		}

		//新しいレベル読み込み	
		if (m_NextLevel != nullptr)
		{
			m_Level = m_NextLevel;
			m_Level->Init();//初期化
		}
	}

	//プレイヤーコントローラー変更関数
	template <typename T>
	void SetPlayerController()
	{
		if (m_PlayerController != nullptr)
		{//現在のプレイヤーコントローラー終了
			delete m_PlayerController;//削除
			m_PlayerController = nullptr;//nullptr代入
		}
		m_PlayerController = new T();//作成
		m_PlayerController->Init();//初期化
	}

};