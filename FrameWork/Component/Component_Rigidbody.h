//=============================================================================
//
//  ���̃R���|�[�l���g [Component_Rigidbody.h]
//  Date   : 2021/11/22
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/Component.h"
#include "../Manager/Manager_Drawer/Manager_Rigidbody.h"

//=============================================================================
// �萔��`
//=============================================================================
const float ON_GROUND_VELOCITY = 0.1f;//�ڒn����Ƃ��鑬�x

//=============================================================================
// �N���X��`
//=============================================================================
class Component_Rigidbody : public Component
{
private:

	//����
	Manager_Rigidbody::s_RigidBody* m_RigidBody;

	//�T�C�Y
	Vector3 m_Scale;

	//�W�����v�㏸����
	int m_JumpTime;

public:

	Component_Rigidbody(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//�������E�X�V�E�I��
	virtual void Init() override; 
	virtual void Update()override;
	virtual void Uninit()override {};

	//���W�擾
	Vector3 GetPosition();

	//�X�P�[���ݒ�
	void SetScale(const Vector3& _scale);

	//XZ���ړ��ݒ�
	void SetMoveXZ(const Vector3& _velocity);

	//XYZ���ړ��ݒ�
	void SetMoveXYZ(const Vector3& _velocity);

	//�d�͐ݒ�
	void SetGravity(const Vector3& _velocity);

	//���C�ݒ�
	void SetFriction(const float& _friction);

	//�W�����v
	void Jump();

	//�n�C�W�����v
	void HighJump();

	//���[�v
	void SetWarp(const Vector3& _position);

	//���x�擾
	Vector3 GetVelociy();

	//�X�t�B�A�^���̒ǉ�
	void AddSphere(const Vector3& _scale, const Vector3& _position, float _mass);

	//�{�b�N�X�^���̒ǉ�
	void AddBox(const Vector3& _scale, const Vector3& _position, float _mass);

	//�J�v�Z���^���̒ǉ�
	void AddCapsule(float radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass);

	//���ʌ^���̒ǉ�
	void AddStaticPlane(const Vector3& _up, const Vector3& _position, float _mass);

};

