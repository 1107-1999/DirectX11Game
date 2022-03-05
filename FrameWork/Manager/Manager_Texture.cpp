//=============================================================================
//
//  テクスチャーマネージャー [Manage_Texturer.cpp]
//  Date   : 2021/11/2
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Manager_Texture.h"
#include "../Renderer/Renderer_DirectX11.h"

//=============================================================================
// 初期化関数
//=============================================================================
void Manager_Texture::Init(void)
{
	//エラー用テクスチャ読み込み

	//多重ロード防止
	if (!m_Textures["Error"])
	{
		// テクスチャ読み込み
		D3DX11CreateShaderResourceViewFromFile(Renderer_DirectX11::Instance()->GetDevice(),
			"ROM/2D/Error/T_Error.png",
			NULL,
			NULL,
			&m_Textures["Error"],
			NULL);

		assert(m_Textures["Error"]);
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void Manager_Texture::Uninit()
{
	//イテレーター
	std::unordered_map<std::string, ID3D11ShaderResourceView*>::iterator itr = m_Textures.begin();

	for (itr; itr != m_Textures.end(); itr++)
	{//全要素分ループ
		if (ID3D11ShaderResourceView* texture = itr->second)
		{
			texture->Release();//対象の要素を削除
		}
	}

	m_Textures.clear();
}

//=============================================================================
// リソース読み込み関数
//=============================================================================
ID3D11ShaderResourceView*  Manager_Texture::LoadTexture(const char* _key, const char* _fileName)
{
	if (!m_Textures[_key])//多重ロード防止
	{
		D3DX11CreateShaderResourceViewFromFile(Renderer_DirectX11::Instance()->GetDevice(),// テクスチャ読み込み
			_fileName,
			NULL,
			NULL,
			&m_Textures[_key],
			NULL);
	}

	return m_Textures[_key];
}

//=============================================================================
// リソース解放関数
//=============================================================================
void Manager_Texture::UnloadTexture(const char* _key)
{
	if (m_Textures[_key])//多重アンロード防止
	{
		m_Textures[_key]->Release();//対象の要素を削除
		m_Textures.erase(_key);//キーを削除
	}
}
