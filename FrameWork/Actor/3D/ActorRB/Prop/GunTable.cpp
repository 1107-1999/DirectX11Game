//=============================================================================
//
// 銃のテーブルクラス [GunTable.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "GunTable.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Component/Component_OBB.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// 初期化関数
//=============================================================================
void GunTable::Init()
{

	//親クラス初期化
	ActorRB::Init();

	//静的メッシュコンポーネント追加
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//静的メッシュコンポーネントnullチェック
	if (m_Component_StaticMesh != nullptr)
	{
		//モデルロード
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Table.fbx");

		//ポジションオフセット
		m_Component_StaticMesh->SetPositionOffset(Vector3{ 0.0f,-0.6f,0.0f });
	
		//スケールオフセット調整
		m_Component_StaticMesh->SetScaleRate(0.055f);

	}

	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//静的ボックス剛体追加(第一引数はスケールのオフセット値)
		m_Component_Rigidbody->AddBox(Vector3{ 0.8f,0.65f,0.5f }, m_Position, 0);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//リジッドボディと同スケールに調整
		m_Component_OBB->SetScale(Vector3{ 1.5f,1.0f,1.0f });

		//物理マテリアルを木に設定
		m_Component_OBB->SetPhysicsMaterial(PM_WOOD);
	}
}

