//=============================================================================
//
//  シェーダーマネージャー [Manager_Shader.h]
//  Date   : 2021/11/05
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Manager_Shader.h"
#include "../Renderer/Renderer_DirectX11.h"


//=============================================================================
// 初期化関数
//=============================================================================
void Manager_Shader::Init()
{
	//SHADER_UNLIT初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_UNLIT].VertexShader, &m_Shaders[SHADER_UNLIT].VertexLayout, "ROM/cso/unlitTextureVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_UNLIT].PixelShader, "ROM/cso/unlitTexturePS.cso");

	//SHADER_VERTEX_LIGHTING初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_VERTEX_LIGHTING].VertexShader, &m_Shaders[SHADER_VERTEX_LIGHTING].VertexLayout, "ROM/cso/VertexLightingVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_VERTEX_LIGHTING].PixelShader, "ROM/cso/VertexLightingPS.cso");
	
	//SHADER_PIXEL_LIGHTING初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_PIXEL_LIGHTING].VertexShader, &m_Shaders[SHADER_PIXEL_LIGHTING].VertexLayout, "ROM/cso/PixelLightingVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_PIXEL_LIGHTING].PixelShader, "ROM/cso/PixelLightingPS.cso");

	//SHADER_ATOMOSPHERE初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_ATOMOSPHERE].VertexShader, &m_Shaders[SHADER_ATOMOSPHERE].VertexLayout, "ROM/cso/Atomosphere_VS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_ATOMOSPHERE].PixelShader, "ROM/cso/Atomosphere_PS.cso");

	//SHADER_TOON初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_TOON].VertexShader, &m_Shaders[SHADER_TOON].VertexLayout, "ROM/cso/ToonVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_TOON].PixelShader, "ROM/cso/ToonPS.cso");

	//SHADER_NORMALMAP初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_NORMALMAP].VertexShader, &m_Shaders[SHADER_NORMALMAP].VertexLayout, "ROM/cso/NormalMappingVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_NORMALMAP].PixelShader, "ROM/cso/NormalMappingPS.cso");

	//SHADER_ENVMAP初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_ENVMAP].VertexShader, &m_Shaders[SHADER_ENVMAP].VertexLayout, "ROM/cso/EnvMappingVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader (&m_Shaders[SHADER_ENVMAP].PixelShader, "ROM/cso/EnvMappingPS.cso");

	//SHADER_DEPTHSHADOW初期化
	Renderer_DirectX11::Instance()->CreateVertexShader(&m_Shaders[SHADER_DEPTHSHADOW].VertexShader, &m_Shaders[SHADER_DEPTHSHADOW].VertexLayout, "ROM/cso/ShadowDepthVS.cso");
	Renderer_DirectX11::Instance()->CreatePixelShader(&m_Shaders[SHADER_DEPTHSHADOW].PixelShader, "ROM/cso/ShadowDepthPS.cso");
}

//=============================================================================
// 終了関数
//=============================================================================
void Manager_Shader::Uninit()
{
	//イテレーター
	std::unordered_map < int, s_Shader >::iterator itr = m_Shaders.begin();

	for (itr; itr != m_Shaders.end(); itr++)
	{//全要素分ループ
		if (ID3D11PixelShader* pixelShader = itr->second.PixelShader)//PS解放
		{
			pixelShader->Release();//PS解放
		}
		if (ID3D11VertexShader* vertexShader = itr->second.VertexShader)
		{
			vertexShader->Release();//VS解放
		}
		if (ID3D11InputLayout* vertexLayout = itr->second.VertexLayout)
		{
			vertexLayout->Release();//IL解放
		}
	}

	m_Shaders.clear();
}

//=============================================================================
// 適用シェーダー設定関数
//=============================================================================
void Manager_Shader::SetShader(int _key)
{
	// 入力レイアウト設定
	Renderer_DirectX11::Instance()->GetDeviceContext()->IASetInputLayout(m_Shaders[_key].VertexLayout);

	// シェーダ設定
	Renderer_DirectX11::Instance()->GetDeviceContext()->VSSetShader(m_Shaders[_key].VertexShader, NULL, 0);
	Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShader(m_Shaders[_key].PixelShader , NULL, 0);
}



