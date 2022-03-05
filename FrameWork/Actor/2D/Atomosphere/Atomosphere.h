//=============================================================================
//
//  大気クラス [Atomosphere.h]
//  Date   : 2021/12/10
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../2D/Base/Actor2D.h"
#include "../Atomosphere/Atomosphere.h"

//=============================================================================
// 構造体定義
//=============================================================================
// 大気散乱用バッファ構造体
struct SKY_RAY
{
	D3DXVECTOR4 frustumRayTL;  // スクリーンの左上のレイ
	D3DXVECTOR4 frustumRayTR;  // スクリーンの右上のレイ
	D3DXVECTOR4 frustumRayBL;  // スクリーンの左下のレイ
	D3DXVECTOR2 windowSize;	   // ウィンドウのサイズ
	D3DXVECTOR2	Enable;		   // バッファサイズ合わせ
};

struct SKY
{
	Vector3 CameraPos;        // カメラのポジション
	float   CameraHeight;	    // カメラの高さ

	Vector3 LightDirection;	// ライトの向き
	float Scale;			    // 大気の大きさ

	Vector3 InvWavelength;    // 光の波長の長さ
	float exposure;

	float OuterRadius;		    // 大気の大きさ
	float InnerRadius;		    // 地球の大きさ

	float KrESun;			    // 太陽の明るさ*粒子の大きさ(レイリー散乱)
	float KmESun;			    // 太陽の明るさ*粒子の大きさ(ミー散乱)
	float Kr4PI;			    // 粒子の大きさ(レイリー散乱)*円周率
	float Km4PI;			    // 粒子の大きさ(ミー散乱)*円周率

	float ScaleDepth;		    // 大気の平均的な密度
	float ScaleOverScaleDepth;	// fScale / fScaleDepth
	float g;
	Vector3 dammy;
};

//=============================================================================
// クラス定義
//=============================================================================
class Atomosphere : public Actor2D
{
private:

	class Component_Sprite*    m_Component_Sprite;   //スプライトコンポーネント

	//DirectX11描画クラスキャッシュ
	class Renderer_DirectX11* m_Renderer_DirectX11 = nullptr;


	ID3D11Buffer* m_SkyRayBuffer; // 大気散乱用スクリーンレイ構造体
	ID3D11Buffer* m_SkyBuffer;    // 大気散乱用パラメータ構造体

	//時間
	double m_Time;

	//天球
	class SkySphere* m_SkySphere;

public:

	//リソース読み込み・削除
	static void Load();
	static void Unload();

	//初期化・終了・更新
	void Init()override;
	void Uninit()override;
	void Update()override;

	// レイのセット
	void SetSkyRay(SKY_RAY _skyray);

	// 大気散乱構造体のセット
	void SetSky(SKY _sky);

private:

	// 太陽の向きの計算
	Vector3 SunDirection(int _day, double _time, double _eastLongitude, double _northLatitude);

	// スクリーンのレイの計算
	void RayCalculation(D3DXMATRIX view, D3DXMATRIX proj);

	// 大気散乱の計算
	void AtomosphereCalculation();
};