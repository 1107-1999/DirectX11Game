//=============================================================================
//
//  キューブコンポーネント [Component_Cube.cpp]
//  Author : Ryosuke Kotera
//  Date   : 2021/1/19
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <math.h>
#include "Component_Cube.h"
#include "../Level/Base/Level.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"
#include "../Manager/Manager_Game.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Actor/3D/Base/Actor3D.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Component_Cube::Init()
{
	//基底クラス初期化
	Component::Init();

	//デフォルトはアンリットシェーダー
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//テクスチャループ設定
	m_TexLoop = true;

	//色を白に設定
	m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

	//キューブマネージャーを取得できたら自身を登録
	if (m_Manager_Cube = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Cube())
	{
		m_Manager_Cube->AddComponent(this);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void Component_Cube::Draw()
{
	//Actor3Dにキャスト
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{
		//シェーダー設定
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//デバッグ描画
		if (Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetDebugCube())
		{
			ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture("LD");
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
		}
		//通常描画
		else
		{
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
		}
		
	
		// 影描画用テクスチャ
		if (m_ShaderType == Manager_Shader::SHADER_DEPTHSHADOW)
		{
			ID3D11ShaderResourceView* ShadowTexture = Renderer_DirectX11::Instance()->GetShadowDepthTexture();
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(1, 1, &ShadowTexture);
		}

		//ポリゴンレンダラーから描画
		Renderer_Polygon::Instance()->DrawBox(actor3D->GetPosition(), actor3D->GetRotation(), actor3D->GetScale(), m_Color, m_TexLoop);
	}
}

//=============================================================================
// テクスチャ設定関数
//=============================================================================
void Component_Cube::SetTexture(const char* _Key)
{
	//指定のキーのテクスチャーがあるか確認
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(_Key))
	{
		//テクスチャ設定
		m_Texture = texture;
	}
}