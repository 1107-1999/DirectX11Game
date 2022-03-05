//=============================================================================
//
//  2D�A�N�^�[�N���X [Actor2D.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../Base/Actor.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Actor2D : public Actor
{
protected:

	//2�������W
	Vector2 m_Position2D;

	//2�����X�P�[��
	Vector2 m_Scale2D;

public:

	//������
	virtual void Init()override;


	//2�������W�擾�E�ݒ�
	inline Vector2 GetPosition2D() const { return m_Position2D;}
	inline void SetPosition2D(Vector2 _position3D) { m_Position2D = _position3D; }


	//2�����X�P�[���擾�E�ݒ�
	inline Vector2 GetScale2D()    const { return m_Scale2D; }  
	inline void SetScale2D(Vector2 _scale2D) { m_Scale2D = _scale2D; }


};