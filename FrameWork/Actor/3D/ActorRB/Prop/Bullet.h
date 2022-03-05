//=============================================================================
//
//   �e�N���X [Bullet.h]
//  Date   : 2021/1/10
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../Base/Actor3D.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class Bullet : public Actor3D
{
private:

	//�ÓI���b�V���R���|�[�l���g
	class Component_StaticMesh*   m_Component_StaticMesh;

	//�������ԃJ�E���g
	int m_LifeTime = 0;

	//�L���t���O
	bool m_Active;     

	//���x
	Vector3 m_Velocity;

public:

	//�������E�X�V
	void Init()override;
	void Update()override;

	//�e����
	void SpawnBullet(Vector3 _position, Vector3 _velocity, Vector3 _rotation);

	//�g�p�\�t���O�擾
	inline bool GetActive()const { return m_Active; }

};