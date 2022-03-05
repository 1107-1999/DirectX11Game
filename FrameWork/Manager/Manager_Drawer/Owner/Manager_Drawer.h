//=============================================================================
//
//  描画マネージャー [Manager_Drawer.h]
//  Date   : 2021/11/03
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Drawer
{
private:

	//DirextX11描画機構クラスキャッシュ
	class Renderer_DirectX11*           m_Renderer_DX11;        

	//各種描画機能持ちクラスマネージャー
	class Manager_Cube*            m_Manager_Cube;         //キューブマネージャー
	class Manager_Model*           m_Manager_Model;        //モデルマネージャー
	class Manager_Billboard*       m_Manager_Billboard;    //ビルボードマネージャー
	class Manager_Sprite*          m_Manager_Sprite;       //スプライトマネージャー
	class Manager_Fade*            m_Manager_Fade;         //フェードマネージャー
	class Manager_OBB*             m_Manager_OBB;          //OBBマネージャー
	class Manager_Rigidbody*       m_Manager_Rigidbody;    //剛体マネージャー
	class HUD3D*                   m_HUD3D;				   //使用HUD3D
	class HUD*                     m_HUD;                  //使用HUD
	class Manager_Font2D*		   m_Manager_Font2D;       //フォントマネージャーキャッシュ用
	class Manager_Font3D*		   m_Manager_Font3D;       //3Dフォントマネージャー
	class Manager_ImGui*           m_Manager_ImGui;        //ImGuiマネージャー

    //コリジョンデバッグ表示フラグ
	bool m_DebugDraw;             

	//キューブデバッグ表示フラグ
	bool m_DebugCube;                                     

	//光源
	struct LIGHT*  m_Light;              

public:

	//初期化・終了
	void Init();      
	void Uninit(); 

	//アクター更新前の更新
	void UpdateBefore();

	//アクター更新後の更新
	void UpdateAfter(); 

	//描画
	void Draw();      

	//3Dオブジェクトのみ描画関数
	void Draw3D();

	//各種描画機能持ちクラスマネージャー追加関数

	void AddManager_Cube();         //キューブマネージャー追加
	void AddManager_Model();        //モデルマネージャー追加
	void AddManager_Billboard();    //ビルボードマネージャー追加
	void AddManager_Sprite();       //スプライトマネージャー追加
	void AddManager_OBB();          //OBBマネージャー追加
	void AddManager_Rigidbody();    //剛体マネージャー追加


	//各種描画機能持ちクラスマネージャー取得関数
	inline class Manager_Cube*          GetManager_Cube()          const { return m_Manager_Cube; }         //キューブマネージャー取得
	inline class Manager_Model*         GetManager_Model()         const { return m_Manager_Model; }        //モデルマネージャー取得
	inline class Manager_Billboard*     GetManager_Billboard()     const { return m_Manager_Billboard; }    //ビルボードマネージャー取得
	inline class Manager_Sprite*        GetManager_Sprite()        const { return m_Manager_Sprite; }       //スプライトマネージャー取得
	inline class Manager_Fade*          GetManager_Fade()          const { return m_Manager_Fade; }         //フェードマネージャー取得
	inline class Manager_OBB*           GetManager_OBB()           const { return m_Manager_OBB; }          //OBBマネージャー取得
	inline class Manager_Rigidbody*     GetManager_Rigidbody()     const { return m_Manager_Rigidbody; }    //剛体マネージャー取得
	inline class Manager_Font3D*        GetManager_Font3D()        const { return m_Manager_Font3D; }       //3Dフォントマネージャー取得

	//HUD取得
	inline class HUD* GetHUD()const { return m_HUD; }                 

	//デバッグキューブのフラグ取得
	inline bool GetDebugCube() const{ return m_DebugCube; }

	//HUD設定関数
	template <typename T>
	void SetHUD()
	{
		//現在のHUDがある場合
		if (m_HUD != nullptr)
		{
			m_HUD->Uninit();//終了
			delete m_HUD;//削除
			m_HUD = nullptr;//nullptr代入
		}

		//HUD読み込み	
		if (m_HUD == nullptr)
		{
			m_HUD = new T();//HUD作成;
			m_HUD->Init();//初期化
		}
	}

};
