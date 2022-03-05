//=============================================================================
//
//  �ϊ��@ [Exchanger.cpp]
//  Date   : 2021/11/2
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../System/Main.h"
#include "Exchanger.h"

//=============================================================================
// int�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::INT_TO_STRING(int _value)
{
	char temp[512] = {};
	sprintf(temp, "%d", _value);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// float�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::FLOAT_TO_STRING(float _value)
{
	char temp[512] = {};
	sprintf(temp, "%f", _value);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// double�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::DOUBLE_TO_STRING(double _value)
{
	char temp[512] = {};
	sprintf(temp, "%lf", _value);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// bool�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::BOOL_TO_STRING(bool _value)
{
	std::string ret = _value ? "TRUE" : "FALSE";

	return ret;
}

//=============================================================================
// Vector2�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::VEC2_TO_STRING(Vector2 _value)
{
	char temp[512] = {};
	sprintf(temp, "x:%f,y:%f", _value.x, _value.y);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// Vector3�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::VEC3_TO_STRING(Vector3 _value)
{
	char temp[512] = {};
	sprintf(temp, "x:%f,y:%f,z:%f", _value.x, _value.y, _value.z);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// Vector4�^�𕶎���(string)�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::VEC4_TO_STRING(Vector4 _value)
{
	char temp[512] = {};
	sprintf(temp, "x:%f,y:%f,z:%f,w:%f", _value.x, _value.y, _value.z, _value.w);
	std::string ret = temp;

	return ret;
}

//=============================================================================
// wstring��string�ɕϊ�����֐�
//=============================================================================
std::string Exchanger::WSTRING_TO_STRING(std::wstring _text)
{
	//wstring to SJIS
	int bufSize = WideCharToMultiByte(CP_OEMCP, 0, _text.c_str(), -1, (char*)NULL, 0, NULL, NULL);

	//�o�b�t�@�̎擾
	CHAR* cpMultibyte = new CHAR[bufSize];
	memset(cpMultibyte, 0, sizeof(CHAR) * bufSize);

	//wstring SJUS
	WideCharToMultiByte(CP_OEMCP, 0, _text.c_str(), -1, cpMultibyte, bufSize, NULL, NULL);

	//string�̐���
	std::string ret(cpMultibyte, cpMultibyte + bufSize + 1);

	delete[] cpMultibyte;
	cpMultibyte = nullptr;

	return ret;
}

//=============================================================================
// string��wstring�ɕϊ�����֐�
//=============================================================================
std::wstring Exchanger::STRING_TO_WSTRING(std::string _text)
{
	//SJIS to wstring
	int bufSize = MultiByteToWideChar(CP_ACP, 0, _text.c_str(), -1, (wchar_t*)NULL, 0);

	//�o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[bufSize];
	memset(cpUCS2, 0, sizeof(wchar_t) * bufSize);

	//SJUS to wstring
	MultiByteToWideChar(CP_ACP, 0, _text.c_str(), -1, cpUCS2, bufSize);

	//wstring�̐���
	std::wstring ret(cpUCS2, cpUCS2 + bufSize - 1);

	delete[] cpUCS2;
	cpUCS2 = nullptr;

	return ret;
}

//=============================================================================
// Vector4�^��Color�^�ɕϊ�����֐�
//=============================================================================
Color Exchanger::VEC4_TO_COLOR(Vector4 _color)
{
	return Color(min(_color.x, 1.0f), min(_color.y, 1.0f), min(_color.z, 1.0f), min(_color.w, 1.0f));
}

//=============================================================================
// Color�^��Vector4�^�ɕϊ�����֐�
//=============================================================================
Vector4 Exchanger::COLOR_TO_VEC4(Color _color)
{
	return Vector4(_color.r, _color.g, _color.b, _color.a);
}