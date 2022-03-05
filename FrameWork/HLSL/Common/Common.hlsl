//=============================================================================
//
//  [Common.hlsl]
//  Date   : 2021/12/08
//
//=============================================================================


// ワールドマトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
	matrix World;
}

// ビューバッファ
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}

// プロジェクションバッファ
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}


// マテリアル構造体
struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float  Shininess;
	float3 Dummy;
};

// マテリアルバッファ
cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}

// ライト構造体
struct LIGHT
{
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	bool   Enable;
	bool3  Dummy;
	matrix View;
	matrix Projection;
};

// ライトバッファ
cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}

// カメラバッファ
cbuffer CameraBuffer : register(b5)
{
	float4 CameraPosition;
	float CameraLength;
	float3 Dummy;
}

// バーテックスシェーダー構造体
struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};

// ピクセルシェーダー構造体
struct PS_IN
{
	float4 Position		 : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal        : NORMAL0;
	float4 Diffuse		 : COLOR0;
	float2 TexCoord		 : TEXCOORD0;
	float4 ShadowPosition : POSITION1;
};


// スクリーンのレイ構造体
cbuffer CB : register(b6)
{
	float4 FrustumRayTL;// スクリーンの左上に向かうカメラのレイ
	float4 FrustumRayTR;// スクリーンの右上に向かうカメラのレイ
	float4 FrustumRayBL;// スクリーンの左下に向かうカメラのレイ
	float2 WindowSize;   // ウィンドウサイズ
	float2 Enable;
};

// 大気散乱用バッファ構造体
cbuffer SkyCB : register(b7)
{
	float3 CameraPos;		// カメラのポジション
	float  CameraHeight;	// カメラの高さ

	float3 LightDirection;	// ライトの向き
	float  Scale;			// 大気の大きさ

	float3 InvWavelength;	// 光の波長の長さ
	float exposure;

	float OuterRadius;		// 大気の大きさ
	float InnerRadius;		// 地球の大きさ

	float KrESun;			// 太陽の明るさ*粒子の大きさ(レイリー散乱)
	float KmESun;			// 太陽の明るさ*粒子の大きさ(ミー散乱)
	float Kr4PI;			// 粒子の大きさ(レイリー散乱)*円周率
	float Km4PI;			// 粒子の大きさ(ミー散乱)*円周率

	float ScaleDepth;		// 大気の平均的な密度
	float ScaleOverScaleDepth;	// fScale / fScaleDepth
	float g;

	float3 dummy;// バイト数合わせ
};