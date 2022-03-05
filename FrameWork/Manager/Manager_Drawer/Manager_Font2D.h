//=============================================================================
//
//  フォント2Dマネージャー [Manager_Font2D.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "../../System/Singleton.h"
#include "../Manager_Font.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Font2D : public Manager_Font, public Singleton<Manager_Font2D>
{
private:

	friend Singleton<Manager_Font2D>;
	struct s_CachePrint2DData
	{
		Vector2* pPos;
		std::string* pText;
	};
	std::unordered_map<const char*, s_CachePrint2DData>cacheList;

public:

	void Init() override;  //初期化
	void Uninit() override;//終了
	void Draw() override;

	//書式指定子ありの文字描画
	void Printf2D(Vector2 _pos, const char* _text, ...);

	//書式指定子のない文字描画
	void PrintfStatic2D(Vector2 _pos, const char* _text);

	//文字列のポインタを登録して外から文字列を操作
	void AddPrintData(Vector2& _pos, std::string& _text, const char* _key);
};