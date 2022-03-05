//=============================================================================
//
//  ビルボードコンポーネント [Component_Billboard.cpp]
//  Date   : 2021/11/05
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/Component.h"
#include "../Renderer/Renderer_Polygon.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_Billboard : public Component
{
private:

	//テクスチャー
	ID3D11ShaderResourceView*  m_Texture;

	//スプライトアニメーション構造体
	s_SpriteAnimation m_AnimationInformation;

	//使用するシェーダーの種類
	int   m_ShaderType; 

	//色 
	Color m_Color;


public:

	Component_Billboard(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//初期化・更新・終了
	virtual void Init()override;   
	virtual void Update() override;
	virtual void Uninit()override; 

	//描画
	virtual void Draw();

	//リプレイ
	void Replay();

	//テクスチャセット
	void SetTexture(const char* _Key);

	//色設定
	inline void SetColor(Color _color) { m_Color = _color;}

	//1コマ辺りのサイズ割り出し
	inline void CalculationOneFrameSize(int _W_frame, int _H_frame)
	{
		m_AnimationInformation.OneFrameSize.x = static_cast<float>(1.0f / _W_frame);
		m_AnimationInformation.OneFrameSize.y = static_cast<float>(1.0f / _H_frame);
	}

	//ループさせるか設定
	inline void SetLoop(bool _loop) { m_AnimationInformation.Loop = _loop; }

	//何フレームで更新するか設定
	inline void SetMaxAnimCount(int _max_count) { m_AnimationInformation.MaxAnimCount = _max_count; }

};
