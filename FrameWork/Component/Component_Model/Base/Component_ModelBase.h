//=============================================================================
//
//  モデル関連コンポーネント基底 [Componet_ModelBase.h]
//  Date   : 2021/12/08
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "../../Base/Component.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_ModelBase : public Component
{
protected:

	//シェーダータイプ
	int m_ShaderType;

	//描画スケール比率
	float m_ScaleRate;

	//座標オフセット値
	Vector3 m_PositionOffset;

	//回転オフセット値
	Vector3	m_RotationOffset;

	//頂点&インデックスバッファー
	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;

	//モデルカラー
	Vector4 m_ModelColor;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

public:

	Component_ModelBase(class Actor* _owner, int _updatePriority) :
		Component(_owner, _updatePriority) {}

	//描画関数
	virtual void Draw() = 0;

	//座標オフセット値設定
	inline void SetPositionOffset(Vector3 _set) { m_PositionOffset = _set; }

	//回転オフセット値設定
	inline void SetRotationOffset(Vector3 _set) { m_RotationOffset = _set; }

	//シェーダー取得・設定
	inline int  GetShaderType() { return m_ShaderType; }
	inline void SetShaderType(int _type) { m_ShaderType = _type; }


	//サイズ比率設定
	inline void SetScaleRate(float _scaleRate) { m_ScaleRate = _scaleRate; }

	//色取得・設定
	inline Vector4 GetColor() { return m_ModelColor; }
	virtual inline void SetColor(Vector4 _color) { m_ModelColor; }

};