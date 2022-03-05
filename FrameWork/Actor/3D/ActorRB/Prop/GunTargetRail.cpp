//=============================================================================
//
// 銃のターゲットのレールクラス [GunTargetRail.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "GunTargetRail.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Component/Component_OBB.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// 初期化関数
//=============================================================================
void GunTargetRail::Init()
{

	//親クラス初期化
	ActorRB::Init();

	//静的メッシュコンポーネント追加
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//静的メッシュコンポーネントnullチェック
	if (m_Component_StaticMesh != nullptr)
	{

		//モデルロード
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Rail.fbx");

		//回転オフセット X軸　Y軸 Z軸
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(90.0f),DegToRad(0.0f) });

		//スケールオフセット調整
		m_Component_StaticMesh->SetScaleRate(0.5f);

	}


	//剛体コンポーネントnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//静的ボックス剛体追加(第一引数はスケールのオフセット値)
		m_Component_Rigidbody->AddBox(Vector3{2.5f,0.175f,0.625f}, m_Position, 0);
	}

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//スケールオフセット調整
		m_Component_OBB->SetScale(Vector3{ 5.0f,0.35f,1.25f });

		//物理マテリアルを金属に設定
		m_Component_OBB->SetPhysicsMaterial(PM_METAL);
	}
}

