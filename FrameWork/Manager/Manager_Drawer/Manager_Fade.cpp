//=============================================================================
//
//  フェードマネージャー [Manager_Fade.cpp]
//  Date   : 2021/11/16
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <time.h>
#include "Manager_Fade.h"
#include "../Manager_Game.h"
#include "../Manager_Shader.h"
#include "../Manager_Texture.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/MainWindow.h"

//=============================================================================
// 定数定義
//=============================================================================
constexpr float MAX_FADE_OPACITY = 1.0f;//フェード最大オパシティ
constexpr float MIN_FADE_OPACITY = 0.0f;//フェード最小オパシティ

//=============================================================================
// 初期化
//=============================================================================
void Manager_Fade::Init()
{
	//アンリットシェーダー
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//フェードしていない状態で初期化
	m_FadeState = FADE_NONE;

	//フェード時間初期化
	m_FadeTime  = 0.0f;

	//フェード開始時間初期化
	m_StartTime = 0.0f;

	//黒色で初期化
	m_Color = Color(0.0f,0.0f,0.0f, MAX_FADE_OPACITY);

	//テクスチャマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//テクスチャロード
		manager_Texture->LoadTexture("Fade", "../ROM/2D/Test/FadeTexture.png");

		//テクスチャ設定
		m_Texture = manager_Texture->GetTexture("Fade");
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void Manager_Fade::Update()
{
	//フェード中の場合
	if (m_FadeState != FADE_NONE)
	{

		float Time = clock() - m_StartTime;
		Time /= 1000.0f;

		switch (m_FadeState)
		{
		case FADE_IN:

			m_Color.a = MAX_FADE_OPACITY - Time / m_FadeTime;

			//フェードイン終了
			if (Time > m_FadeTime)
			{
				m_Color.a = MIN_FADE_OPACITY;
				m_FadeState = FADE_NONE;
			}
			break;

		case FADE_OUT:

			m_Color.a = Time / m_FadeTime;

			//フェードアウト終了
			if (Time > m_FadeTime)
			{
				m_Color.a = MAX_FADE_OPACITY;

				m_FadeState = FADE_NONE;

				//レベル変更
				Manager_Game::Instance()->OpenLevel();
			}
			break;
		}
	}
}
//=============================================================================
// 終了関数
//=============================================================================
void Manager_Fade::Uninit()
{
	//テクスチャマネージャーキャッシュ
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//テクスチャアンロード
		manager_Texture->UnloadTexture("Fade");
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void Manager_Fade::Draw()
{
	if (m_FadeState != FADE_NONE)
	{
		if (m_Texture != nullptr)
		{
			//シェーダー設定
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			// テクスチャ設定
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			Int2 windowSize = MainWindow::Instance()->GetWindowSize();

			//プレーンレンダラーから描画
			Renderer_Polygon::Instance()->Draw2D(Vector2_Zero, Vector2{ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) }, m_Color, false);
		}
	}
}

//=============================================================================
// フェード設定関数(引数はフェード状態と時間)
//=============================================================================
void Manager_Fade::SetFade(State _fadeState, float _time)
{
	m_FadeState = _fadeState;
	m_FadeTime  = _time;
	m_StartTime = static_cast<float>(clock());

	if (_fadeState == FADE_IN)
	{
		m_Color.a = MAX_FADE_OPACITY;
	}
	else if (_fadeState == FADE_OUT)
	{
		m_Color.a = MIN_FADE_OPACITY;
	}
}