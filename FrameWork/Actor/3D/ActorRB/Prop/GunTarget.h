//=============================================================================
//
// �e�̃^�[�Q�b�g�N���X [GunTarget.h]
//  Date   : 2021/1/25
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../Base/ActorRB.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class GunTarget : public ActorRB
{
private:

	//�ÓI���b�V���R���|�[�l���g
	class Component_StaticMesh* m_Component_StaticMesh;

	//�����G�t�F�N�g�N���X
	class Explosion* m_Explosion;

	//�i�s����
	bool m_Vector;

	//���x
	float m_Velocity;


public:

	//�������E�X�V
	void Init()override;
	void Update()override;

	//���x�ݒ�
	inline void SetVelocity(float _velocity) { m_Velocity = _velocity; }

	//�i�s�����ݒ�
	inline void SetVector(bool _vector) { m_Vector = _vector; }
};