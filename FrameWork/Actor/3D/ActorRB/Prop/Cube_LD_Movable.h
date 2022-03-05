//=============================================================================
//
// ���I���x���f�U�C���p�L���[�u�N���X [Cube_LD_Movable.h]
//  Date   : 2021/1/23
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Cube_LD.h"

//=============================================================================
// �N���X
//=============================================================================
class Cube_LD_Movable : public Cube_LD
{
private:

	//1�t���[���O�̍��W
	Vector3 m_OldPosition = Vector3_Zero;

	//�J�n���W
	Vector3 m_Start    = Vector3_Zero;

	//�ڕW���W
	Vector3 m_Target   = Vector3_Zero;

	//���x
	Vector3 m_Velocity = Vector3_Zero;


public:

	//�������E�X�V
	void Init()override;
	void Update()override;

	//�ڕW�ʒu�ݒ�
	inline void SetTarget(Vector3 _target) { m_Target = _target, m_Start = m_Position;}

	//���x�ݒ�
	inline void SetVelocity(Vector3 _velocity) { m_Velocity = _velocity; }
};