//=============================================================================
//
//  フォントマネージャー [Manager_Font.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "../System/Main.h"
#include "../Renderer/Renderer_DirectX11.h"

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Font
{
public:

	//フォントテクスチャ構造体
	struct s_FontTextureData
	{
		s_FontTextureData() :rv(nullptr), fontSize(Vector2(0, 0)),
			nextCenterPoint(0.0f), relativeLeftUpPosFromCenter(Vector2(0, 0)), difY(0.0f) {};//初期化
		ID3D11ShaderResourceView* rv;//テクスチャ
		Vector2 fontSize;			//フォントサイズ
		float nextCenterPoint;		//現在のフォントの次に表示する文字の開始位置
		Vector2 relativeLeftUpPosFromCenter;//原点から左上までの距離
		float difY = 0.0f;			//原点ラインからの高さ差分
	};

	//文字列の揃え方
	enum e_Aligning
	{
		center,//中揃え
		right,//右揃え
		left,//左揃え
		MAX
	};

	virtual ~Manager_Font() {};//継承用仮想デストラクタ

	void SetFont(std::wstring _pathFontName, std::wstring _dataFontName);//使用するフォントを設定
	inline void SetAilgningMode(e_Aligning _mode) { m_AligningMode = _mode; }//揃え方をセット
	inline void SetFontSize(float _size) { m_FontSize = _size; }//フォントサイズ設定
	inline void SetFontColor(Color _color) { m_FontColor = _color; }//フォントカラー設定
	inline void SetCharLength(float _set) { m_CharLength = _set; }//文字間の距離を設定
	inline void SetFontWeight(int _set) { m_FontWeight = _set; }//フォントの太さを設定
	inline void SetIsUseItalic(bool _set) { m_IsUseItalic = _set; }//イタリック体にするかどうか

	//一度だけ呼ぶInit
	void InitMaster();

	//初期化・終了
	virtual void Init();
	virtual void Uninit();

	//描画
	virtual void Draw() = 0;

private:

	//フォントのテクスチャキャッシュ
	static std::unordered_map<std::string, s_FontTextureData*>m_FontTextures;

protected:

	//キャッシュ変数
	struct ID3D11DeviceContext* m_DeviceContext;
	class Renderer_Polygon*     m_Renderer_Polygon;
	class Manager_Shader*       m_Manager_Shader;

	//テキストスタイル変数
	bool m_IsUseItalic;//イタリック体にするか
	int m_FontWeight;//文字の太さ
	std::wstring m_PathFontName;//フォントのパス上の名前
	std::wstring m_DataFontName;//フォントのデータの名前
	e_Aligning m_AligningMode;//揃え方変数
	float m_FontSize;//フォントサイズ
	Color m_FontColor;//フォントカラー
	float m_CharLength;//文字間の距離

	//1文字分テクスチャを作ってキャッシュする関数
	s_FontTextureData* CreateSingleCharFontTexture(const char* _fontName,
		const char* _fontDataName, TCHAR* _c, float _fontSize);

	//半角、全角のスペース用のテクスチャを作成する関数
	float GetSpaceFontSize(const char* _fontPathName,
		const char* _fontDataName, bool isMini);

	//キャッシュしたテクスチャを取得
	//※キャッシュされていなかったら作るので、nullは返さない。
	s_FontTextureData* GetTextureData(const char* _fontName,
		const char* _fontPathName, TCHAR* _c, float _fontSize);

	//テキストの左端から右端までの距離を取得
	float GetStringDif(std::string _text);

	//可変引数から書式指定の内容をcharにしたstringを取得
	std::string GetStringByArg(const char* _text, va_list _argList);


};