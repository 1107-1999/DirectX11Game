//=============================================================================
//
//  ゴールクラス [Goal.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Goal.h"
#include "../Camera.h"
#include "../ActorRB/Prop/GunTarget.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../Component/Component_OBB.h"
#include "../../../Manager/Manager_Game.h"
#include "../../../Level/Base/Level.h"
#include "../../../PlayerController/PC_Game.h"

//=============================================================================
// 初期化関数
//=============================================================================
void  Goal::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//OBBコンポーネント追加
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//リジッドボディと同スケールに調整
		m_Component_OBB->SetScale(Vector3{ 2.0f,0.05f,2.0f });

		//レイコリジョンを無視
		m_Component_OBB->SetIsReactRay(false);

		//物理マテリアルを無効
		m_Component_OBB->SetPhysicsMaterial(PM_IGNORE);
	}

	//プレイヤーコントローラーを取得&キャストしてキャッシュ
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());

}

//=============================================================================
// 更新関数
//=============================================================================
void Goal::Update()
{
	//プレイヤーコントローラーとOBBコンポーネントnullチェック
	if (m_PlayerConroller != nullptr && m_Component_OBB != nullptr)
	{
	    //プレイヤーと接触している場合
		if (m_Component_OBB->GetOverlap())
		{
			//プレイヤーコントローラーにゴールとのオーバーラップ判定を渡す
			m_PlayerConroller->SetGoalFlag(true);

		}
		//プレイヤーと接触していない場合
		else
		{
			//プレイヤーコントローラーのゴールとのオーバーラップ判定を消す
			m_PlayerConroller->SetGoalFlag(false);

		}
	}
	else//nullの場合キャッシュ
	{
		//プレイヤーコントローラーを取得&キャストしてキャッシュ
		m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());
	}

	//親クラス更新
	Actor3D::Update();
}

//=============================================================================
// 終了関数
//=============================================================================
void Goal::Uninit()
{
	//親クラス更新
	Actor3D::Uninit();
}

