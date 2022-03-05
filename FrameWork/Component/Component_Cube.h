//=============================================================================
//
//  キューブコンポーネント [Component_Cube.h]
//  Author : Ryosuke Kotera
//  Date   : 2021/1/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/Component.h"
#include "../Manager/Manager_Drawer/Manager_Cube.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_Cube : public Component
{
public:

	Component_Cube(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//初期化・更新・終了
	void Init()   override;
	void Update() override {};
	void Uninit() override {};

	//描画
	void Draw();

	//テクスチャ設定
	void SetTexture(const char* _Key);

	//シェーダー取得・設定
	inline int GetShaderType() const { return m_ShaderType; }
	inline void SetShaderType(int _type) { m_ShaderType = _type; }

	//色設定
	inline void SetColor(Color _color) { m_Color = _color; }

	//テクスチャループ設定
	inline void SetTexLoop(bool _isLoop) { m_TexLoop = _isLoop; }

private:

	//テクスチャ
	ID3D11ShaderResourceView*  m_Texture;

	//キューブマネージャーキャッシュ用
	class Manager_Cube* m_Manager_Cube;

	//色
	Color   m_Color;

	//使用するシェーダーの種類
	int  m_ShaderType;

	//テクスチャをループさせるか
	bool m_TexLoop;
	
};


