//================================================
//
//　デプスシャドウ
//
//================================================
#include "../Common/Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	// 頂点変換
	matrix  wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	// 光源計算
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	// ライトの計算(ハーフランバート)
	float light = 0.5f - 0.5f * dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);
	Out.Diffuse = light;
	Out.Diffuse.a = In.Diffuse.a;

	//頂点座標をワールド変換して出力
	Out.Position = mul(In.Position, wvp);
	Out.Normal = worldNormal;
	Out.TexCoord = In.TexCoord;

	// ライトの計算マトリクスを計算
	matrix lightwvp;

	lightwvp = mul(World, Light.View);//ワールド行列＊ライトビュー行列
	lightwvp = mul(lightwvp, Light.Projection);//さらに＊ライトプロジェクション行列

	//ライトからみた頂点座標を出力
	Out.ShadowPosition = mul(In.Position, lightwvp);
}