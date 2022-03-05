//=============================================================================
//
//  変換機 [Exchanger.h]
//  Date   : 2021/11/2
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <string>

//=============================================================================
// 名前空間定義
//=============================================================================
namespace Exchanger
{
	//stringに変換
    std::string INT_TO_STRING(int _value);
    std::string FLOAT_TO_STRING(float _value);
    std::string DOUBLE_TO_STRING(double _value);
    std::string BOOL_TO_STRING(bool _value);
    std::string VEC2_TO_STRING(Vector2 _value);
    std::string VEC3_TO_STRING(Vector3 _value);
    std::string VEC4_TO_STRING(Vector4 _value);
    std::string WSTRING_TO_STRING(std::wstring _text);
    std::wstring STRING_TO_WSTRING(std::string _text);

	//Color系
	Color   VEC4_TO_COLOR(Vector4 _color);
	Vector4 COLOR_TO_VEC4(Color _color);

};
