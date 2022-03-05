//=============================================================================
//
//  ���̃A�N�^�[���N���X [ActorRB.h]
//  Date   : 2021/11/26
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../Base/Actor3D.h"
#include "../../../../Component/Component_Rigidbody.h"
#include "../../../../Component/Component_OBB.h"

//=============================================================================
// �N���X��`
//=============================================================================
class ActorRB : public Actor3D
{
protected:

	//�R���|�[�l���g
	class Component_Rigidbody*     m_Component_Rigidbody;    //���̃R���|�[�l���g
	class Component_OBB*           m_Component_OBB;          //OBB�R���|�[�l���g(�I�[�o�[���b�v����p)

public:

	//������
	virtual void Init()override;

	//���̍��W�ݒ�
	void SetRigidbodyPosition(Vector3 _position);

	//���̃X�P�[���ݒ�
	void SetRigidbodyScale  (Vector3 _scale);  

	//�X�t�B�A�^���̒ǉ�(�����͑傫���E���W�E����)
	void AddSphereRB(const Vector3& _scale, const Vector3& _position, float _mass);

	//�{�b�N�X�^���̒ǉ�(�����͑傫���E���W�E����)
	void AddBoxRB(const Vector3& _scale, const Vector3& _position, float _mass);

	//�J�v�Z���^���̒ǉ�(�����͔��a�E�����E���W�E��]�E����)
	void AddCapsuleRB(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass);

};