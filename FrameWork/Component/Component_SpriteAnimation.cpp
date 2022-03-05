//=============================================================================
//
//  アニメーションスプライトコンポーネント [Component_SpriteAnimation.cpp]
//  Date   : 2021/11/04
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Component_SpriteAnimation.h"
#include "../Actor/2D/Base/Actor2D.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Manager_Sprite.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Level/Base/Level.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Component_SpriteAnimation::Init()
{
	//親クラス初期化
	Component_Sprite::Init();

	//現在のフレーム数初期化
	m_AnimationInformation.AnimCount       = 0;

	//何フレームで更新するか初期化
	m_AnimationInformation.MaxAnimCount    = 0;

	//1コマ辺りのサイズ初期化
	m_AnimationInformation.OneFrameSize    = {0.0f,0.0f};

	//切り取り開始座標初期化
	m_AnimationInformation.CutStartPostion = {0.0f,0.0f};

	//ループさせるかフラグ
	m_AnimationInformation.Loop = true;

}

//=============================================================================
// 更新関数
//=============================================================================
void Component_SpriteAnimation::Update()
{
	//有効の場合
	if (m_Active)
	{
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
// 描画関数
//=============================================================================
void Component_SpriteAnimation::Draw()
{
	//有効且つテクスチャがnullではない場合
	if (m_Active && m_Texture != nullptr)
	{
		//シェーダー設定
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//テクスチャ設定
		Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		//ポリゴン描画機構で描画
		Renderer_Polygon::Instance()->Draw2DAnimation(m_Position2D, m_Scale2D, m_Color,
			m_AnimationInformation.OneFrameSize, m_AnimationInformation.CutStartPostion, m_Reverse);
	}
}

