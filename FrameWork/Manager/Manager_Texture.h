//=============================================================================
//
//  テクスチャーマネージャー [Manager_Texturer.h]
//  Date   : 2021/11/02
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
class Manager_Texture : public Singleton<Manager_Texture>
{
private:

	friend class Singleton<Manager_Texture>;//シングルトン

	std::unordered_map < std::string, ID3D11ShaderResourceView* > m_Textures;//テクスチャー情報

public:

	//初期化・終了
	void Init(void);  
	void Uninit(void);

	//リソース読み込み・解放
	ID3D11ShaderResourceView* LoadTexture(const char* _key,const char* _fileName);
	void UnloadTexture(const char* Key);

	//既にロードされたテクスチャを管理
	void AddTexture(ID3D11ShaderResourceView* _texture,const char* _key)
	{
		for (auto& i : m_Textures)
		{
			if (i.second == _texture)return;
		}

		//同じテクスチャが無かったので追加
		m_Textures[_key] = _texture;
	}

	//テクスチャ取得
	inline ID3D11ShaderResourceView*  GetTexture(const char* _key) 
	{
		if (m_Textures[_key])
		{
			return m_Textures[_key];
		}

		//テクスチャが存在しない場合はエラーテクスチャを返す
		return m_Textures["Error"];
		
	}
};
