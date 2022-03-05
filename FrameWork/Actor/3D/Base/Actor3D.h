//=============================================================================
//
//  3Dアクタークラス [Actor3D.h]
//  Date   : 2021/11/5
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../Base/Actor.h"

//=============================================================================
// クラス宣言
//=============================================================================
class Actor3D : public Actor
{
protected:


	Vector3     m_Position;//3次元座標
	Vector3     m_Rotation;//3次元回転
	Vector3     m_Scale;   //3次元スケール

	D3DXMATRIX  m_Matrix;  //マトリクス

public:

	//初期化・更新
	virtual void Init()override;
	virtual void Update()override;

	//3次元座標取得・設定
	inline Vector3 GetPosition() const { return m_Position;}
	inline void    SetPosition(Vector3 _position) { m_Position = _position; }

	//3次元回転取得・設定
	inline Vector3 GetRotation() const { return m_Rotation;}
	inline void    SetRotation(Vector3 _rotation) { m_Rotation = _rotation; }

	//3次元スケール取得・設定
	inline Vector3 GetScale()    const { return m_Scale;}
	inline void    SetScale(Vector3 _scale) { m_Scale = _scale; }

	//マトリクス取得・設定
	inline D3DXMATRIX GetMatrix()   const { return m_Matrix;}
	inline void SetMatrix(D3DXMATRIX& _matrix) { m_Matrix = _matrix; } 

	//前方向ベクトル取得
	inline Vector3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		Vector3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	//横方向ベクトル取得
	inline Vector3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		Vector3 Right;
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}

	//上方向ベクトル取得
	inline Vector3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		Vector3 Up;
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}

};