//=============================================================================
//
//  スプライトコンポーネント [Component_Sprite.cpp]
//  Date   : 2021/11/02
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Component_Sprite.h"
#include "../Actor/2D/Base/Actor2D.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_Sprite.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Level/Base/Level.h"

//=============================================================================
//　初期化関数
//=============================================================================
void Component_Sprite::Init()
{
	//基底クラス初期化
	Component::Init();

	//デフォルトはアンリットシェーダー
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//反転フラグ
	m_Reverse = false;

	//デフォルトテクスチャ使用フラグ
	m_isUseDefaultTexture = false;

	//色初期値
	m_Color = { 1.0f,1.0f,1.0f,1.0f };

	//Z座標初期値
	m_PostionZ = 0.0f;

	//Actor2Dにキャスト成功した場合
	if (Actor2D* actor2D = dynamic_cast<Actor2D*>(m_Owner))
	{
		//オーナーの座標キャッシュ
		m_Position2D = actor2D->GetPosition2D();

		//オーナーのスケールキャッシュ
		m_Scale2D = actor2D->GetScale2D();
	}

	//スプライトマネージャーが取得できた場合
	if (Manager_Sprite* manager_Sprite = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Sprite())
	{
		//自身をマネージャーに登録
		manager_Sprite->AddComponent(this);
	}

}

//=============================================================================
//　終了関数
//=============================================================================
void Component_Sprite::Uninit()
{
	//キャッシュしたテクスチャがある場合
	if (m_Texture != nullptr)
	{
		//nullptr化
		m_Texture = nullptr;
	}
}

//=============================================================================
//　描画関数
//=============================================================================
void Component_Sprite::Draw()
{
	//有効且つテクスチャがnullではない場合
	if (m_Active && m_Texture != nullptr && m_Owner != nullptr)
	{
		//シェーダー設定
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//テクスチャ設定
		Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		//ポリゴン描画機構で描画
		Renderer_Polygon::Instance()->Draw2D(m_Position2D, m_Scale2D, m_Color, m_Reverse, m_PostionZ);
	}
}

//=============================================================================
//　テクスチャ設定関数
//=============================================================================
void Component_Sprite::SetTexture(const char* Key)
{
	//指定のキーのテクスチャがあるか確認
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(Key))
	{
		//テクスチャ設定
		m_Texture = texture;
	}
}