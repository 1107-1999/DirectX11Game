//=============================================================================
//
//  ビルボードコンポーネント [Component_Billboard.cpp]
//  Date   : 2021/11/05
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Component_Billboard.h"
#include "../Actor/3D/Camera.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_Billboard.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Level/Base/Level.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Component_Billboard::Init()
{
	//基底クラス初期化
	Component::Init();

	//デフォルトはアンリットシェーダー
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//現在のフレーム数初期化
	m_AnimationInformation.AnimCount    = 0;     

	//何フレームで更新するか初期化
	m_AnimationInformation.MaxAnimCount = 0;       

	//1コマ辺りのサイズ初期化
	m_AnimationInformation.OneFrameSize    = { 0.0f,0.0f };

	//切り取り開始座標初期化
	m_AnimationInformation.CutStartPostion = { 0.0f,0.0f };

	//ループさせるかフラグ初期化
	m_AnimationInformation.Loop     = true;

	//色初期値
	m_Color = { 1.0f,1.0f,1.0f,1.0f };

	//ビルボードマネージャーを取得できた場合
	if (Manager_Billboard* manager_Billboard = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Billboard())
	{
		//自身をマネージャーに登録
		manager_Billboard->AddComponent(this);
	}

}

//=============================================================================
// 更新関数
//=============================================================================
void Component_Billboard::Update()
{
	//有効の場合
	if (m_Active)
	{
		//現在のフレーム数加算
		m_AnimationInformation.AnimCount++; 
		
		//更新フレーム到達時にアニメーション更新
		if (m_AnimationInformation.AnimCount == m_AnimationInformation.MaxAnimCount)
		{
			//現在のフレーム数リセット
			m_AnimationInformation.AnimCount = 0;

			//X方向にアニメーション更新可能の場合
			if (m_AnimationInformation.CutStartPostion.x + m_AnimationInformation.OneFrameSize.x < MAX_CUT_START_POSTION)
			{
				//X切り取り座標を1コマ分ずらす
				m_AnimationInformation.CutStartPostion.x += m_AnimationInformation.OneFrameSize.x;
			}
			//X方向にアニメーション更新可不可の場合
			else
			{
				//X切り取り座標初期化
				m_AnimationInformation.CutStartPostion.x = 0.0f;

				//Y方向にアニメーション更新可能の場合
				if (m_AnimationInformation.CutStartPostion.y + m_AnimationInformation.OneFrameSize.y < MAX_CUT_START_POSTION)
				{
					//Y切り取り座標を1コマ分ずらす
					m_AnimationInformation.CutStartPostion.y += m_AnimationInformation.OneFrameSize.y;
				}
				//XとY共に更新不可の場合
				else
				{
					//Y切り取り座標初期化
					m_AnimationInformation.CutStartPostion.y = 0.0f;

					//ループしないアニメーションの場合
					if (!m_AnimationInformation.Loop)
					{
						//非アクティブ化
						m_Active = false;
					}
				}
			}
		}
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void Component_Billboard::Uninit()
{
	//キャッシュしたテクスチャがある場合
	if (m_Texture != nullptr)
	{
		//nullptr化
		m_Texture = nullptr;
	}
}


//=============================================================================
// 描画関数
//=============================================================================
void Component_Billboard::Draw()
{
	//有効且つテクスチャがnullではない場合
	if (m_Active && m_Texture != nullptr)
	{
		//Actor3Dにキャスト
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//シェーダー設定
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			//テクスチャ設定
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			//ポリゴン描画機構で描画
			Renderer_Polygon::Instance()->DrawBillboard(actor3D->GetPosition(), actor3D->GetScale(),m_Color, m_AnimationInformation.OneFrameSize, m_AnimationInformation.CutStartPostion);
		}
	}
}

//=============================================================================
// テクスチャ設定関数
//=============================================================================
void Component_Billboard::SetTexture(const char* _Key)
{
	//指定のキーのテクスチャがあるか確認
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(_Key))
	{
		//テクスチャ設定
		m_Texture = texture;
	}
}

//=============================================================================
// リプレイ関数
//=============================================================================
void Component_Billboard::Replay()
{
	//有効化
	m_Active = true;

	//アニメーションリセット
	m_AnimationInformation.AnimCount = 0;     

	//切り取り開始座標リセット
	m_AnimationInformation.CutStartPostion = { 0.0f,0.0f };

}