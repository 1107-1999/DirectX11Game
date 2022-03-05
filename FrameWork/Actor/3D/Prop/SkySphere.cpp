//=============================================================================
//
//  スカイスフィアクラス [SkySphere.cpp]
//  Date   : 2021/1/16
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "SkySphere.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"

//=============================================================================
// 初期化関数
//=============================================================================
void  SkySphere::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//静的メッシュコンポーネント追加
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//静的メッシュコンポーネントnullチェック
	if (m_Component_StaticMesh != nullptr)
	{
		//3Dモデルロード
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_SkyNight.fbx", "ROM\\2D\\Sky\\T_Stars.png");
		//スケールオフセット調整
		m_Component_StaticMesh->SetScaleRate(1000.0f);
	}

}
