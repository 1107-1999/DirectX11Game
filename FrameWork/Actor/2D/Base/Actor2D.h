//=============================================================================
//
//  2Dアクタークラス [Actor2D.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../Base/Actor.h"

//=============================================================================
// クラス定義
//=============================================================================
class Actor2D : public Actor
{
protected:

	//2次元座標
	Vector2 m_Position2D;

	//2次元スケール
	Vector2 m_Scale2D;

public:

	//初期化
	virtual void Init()override;


	//2次元座標取得・設定
	inline Vector2 GetPosition2D() const { return m_Position2D;}
	inline void SetPosition2D(Vector2 _position3D) { m_Position2D = _position3D; }


	//2次元スケール取得・設定
	inline Vector2 GetScale2D()    const { return m_Scale2D; }  
	inline void SetScale2D(Vector2 _scale2D) { m_Scale2D = _scale2D; }


};