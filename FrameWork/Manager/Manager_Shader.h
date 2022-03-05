//=============================================================================
//
//  シェーダーマネージャー [Manager_Shader.h]
//  Date   : 2021/11/05
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include"../System/Singleton.h"
#include "../System/Main.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Shader : public Singleton<Manager_Shader>
{
private:

	friend class Singleton<Manager_Shader>;//シングルトン

	struct s_Shader
	{
		ID3D11InputLayout*    VertexLayout;//IL
		ID3D11VertexShader*   VertexShader;//VS
		ID3D11PixelShader*    PixelShader; //PS
	};//シェーダー情報

	//シェーダー配列
	std::unordered_map < int, s_Shader > m_Shaders;

public:

	//初期化・終了
	void Init(void);
	void Uninit(void);

	//適用シェーダー設定
	void SetShader(int _key);

	enum SHADER_TYPE//シェーダータイプ
	{
		SHADER_NONE = 0,
		SHADER_UNLIT,
		SHADER_VERTEX_LIGHTING,
		SHADER_PIXEL_LIGHTING,
		SHADER_ATOMOSPHERE,
		SHADER_TOON,
		SHADER_NORMALMAP,
		SHADER_ENVMAP,
		SHADER_DEPTHSHADOW
	};
};
