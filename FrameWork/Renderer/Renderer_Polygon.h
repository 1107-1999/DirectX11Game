//=============================================================================
//
//  ポリゴン描画機構 [Renderer_Polygon.h]
//  Date   : 2021/11/02
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../System/Main.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../System/Singleton.h"

//=============================================================================
//　定数宣言
//=============================================================================
constexpr float MAX_CUT_START_POSTION = 1.0f;//最大切り取り座標

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct 
{
	int     AnimCount;        //現在のフレーム数
	int     MaxAnimCount;     //何フレームで更新するか

	Vector2 OneFrameSize;     //1コマ辺りのサイズ
	Vector2 CutStartPostion;  //切り取り開始座標

	bool    Loop;//ループさせるか
}s_SpriteAnimation;

//=============================================================================
// クラス定義
//=============================================================================
class Renderer_Polygon : public Singleton<Renderer_Polygon>
{
private:
	
	friend class Singleton<Renderer_Polygon>;//シングルトン

	//矩形頂点バッファー
	ID3D11Buffer* m_CubePolygonVertexBuffer;

	//線頂点バッファー
	ID3D11Buffer* m_LineVertexBuffer;

	//3Dキューブ頂点バッファー
	ID3D11Buffer* m_VertexBuffer3DBox;
	
	//頂点情報をデフォルトに設定
	void SetRectVertexToDefault(VERTEX_3D* _vertex);

	//3D頂点情報をデフォルトに設定
	void Set3DBoxVertexToDefault(VERTEX_3D* _vertex, Vector3 _magni = Vector3(1.0f,1.0f,1.0f));

	//無地テクスチャー
	ID3D11ShaderResourceView* m_TextureWhite;

	//メインウィンドウキャッシュ
	class MainWindow* m_MainWindow = nullptr;

	//DX11描画クラスキャッシュ
	class Renderer_DirectX11* m_Renderer_DX11 = nullptr;

public:

	//初期化・終了
	 void Init();
	 void Uninit();

	 //無地テクスチャ設定
	 void SetDefaultTexture();

	 //無地テクスチャ取得
	 inline ID3D11ShaderResourceView* GetDefaultTexture() { return m_TextureWhite; }
	

//=============================================================================
//
//  2D描画系
//
//=============================================================================

	//テクスチャなし2D矩形描画
	 void DrawBox2D(Vector2 _postion, Vector2 _scale,
		 Color _color, bool _reverse = false, float _z = 0.0f);

	 //2Dスプライト描画
	 void Draw2D(Vector2 _postion, Vector2 _scale, Color _color,
		 bool _reverse = false,float _z = 0.0f);//デフォルト引数は反転フラグとz座標

	 //2Dスプライトアニメーション描画
	 void Draw2DAnimation(Vector2 _position, Vector2 _scale, Color _color,
		 Vector2 _OneFrameSize, Vector2 _CutStartPostion,
		 bool _reverse = false);//最後のデフォルト引数は反転フラグ

	 //2Dライン描画	 ※画面左上中心
	 void DrawLine2D(Vector2 _startPos, Vector2 _endPos, Color _color);

//=============================================================================
//
//  3D描画系
//
//=============================================================================

	 //ビルボード描画
	 void DrawBillboard(Vector3 _postion, Vector3 _scale, Color _color, 
		 Vector2 _OneFrameSize, Vector2 _CutStartPostion,bool _isUseDefaultTex = false);

	 //ボックス描画
	 void DrawBox(Vector3 _postion, Vector3 _Rotation,
		 Vector3 _scale, Color _color, bool _isLoop = true);

	 //線描画
	 void DrawLine(Vector3 _start, Vector3 _end, Color _color);

};
