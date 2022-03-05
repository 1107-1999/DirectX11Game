//=============================================================================
//
//  フェードマネージャー [Manager_Fade.h]
//  Date   : 2021/11/16
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../System/Main.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Fade
{
public:

	//フェード状態
	enum State
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	};

	//初期化・更新・終了
	void Init();
	void Update();
	void Uninit();

	//描画
	void Draw();

	//フェード設定(引数はフェード状態と時間)
	void SetFade(State _fadeState, float _time);

	//現在のフェード状態取得
	inline State GetState()    const { return m_FadeState; }

	//現在のフェード時間取得
	inline float GetFadeTime() const { return m_FadeTime; }

private:

	//シェーダータイプ
	int m_ShaderType;

	//現在のフェード状態
	State m_FadeState = FADE_NONE;

	//フェード時間
	float m_FadeTime  = 0.0f;

	//フェード開始時間
	float m_StartTime = 0.0f;

	//色
	Color m_Color = Color(0.0f, 0.0f, 0.0f, 0.0f);

	//テクスチャ
	ID3D11ShaderResourceView* m_Texture;

};