//=============================================================================
//
//  2Dアクタークラス [Actor2D.cpp]
//  Date   : 2021/11/1
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Actor2D.h"

//=============================================================================
// 初期化関数
//=============================================================================
void  Actor2D::Init()
{
	//2次元座標初期値
	m_Position2D       = Vector2_Zero;

	//2次元サイズ初期値
	m_Scale2D          = Vector2_Zero;
}
