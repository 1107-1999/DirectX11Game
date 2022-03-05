//=============================================================================
//
// キューブクラス [Cube.cpp]
//  Date   : 2021/1/19
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Cube.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../Component/Component_Cube.h"
#include "../../../Manager/Manager_Texture.h"
#include "../../../Manager/Manager_Shader.h"

//=============================================================================
// リソース読み込み・削除関数
//=============================================================================
void  Cube::Load()
{
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{//テクスチャーマネージャーキャッシュ

		//テクスチャー読み込み
		manager_Texture->LoadTexture("LD","ROM/2D/Material/T_BasicGrid_M.png");
	}

}
void  Cube::Unload()
{
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{//テクスチャーマネージャーキャッシュ

		//テクスチャー解放
		manager_Texture->UnloadTexture("LD");
	}
}

//=============================================================================
// 初期化関数
//=============================================================================
void  Cube::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//キューブコンポーネント追加
	m_Component_Cube = AddComponent<Component_Cube>(0);

	//キューブコンポーネントnullチェック
	if (m_Component_Cube != nullptr)
	{
		//テクスチャ設定
		m_Component_Cube->SetTexture("LD");
	}

}