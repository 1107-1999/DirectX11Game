//=============================================================================
//
//  ���̃A�N�^�[���N���X [ActorRB.cpp]
//  Date   : 2021/11/26
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ActorRB.h"

//=============================================================================
// �������֐�
//=============================================================================
void  ActorRB::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//���̃R���|�[�l���g�ǉ�
	m_Component_Rigidbody = AddComponent<Component_Rigidbody>(0);

	//OBB�R���|�[�l���g�ǉ�(�I�[�o�[���b�v����p)
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		//�����ݒ�
		m_Component_OBB->SetVisibility(true);
		//�X�P�[���ݒ�
		m_Component_OBB->SetScale(m_Scale);
	}

}

//=============================================================================
// ���̍��W�ݒ�֐�
//=============================================================================
void ActorRB::SetRigidbodyPosition(Vector3 _position)
{
	//��b���W�ݒ�
	m_Position = _position;

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->SetWarp(m_Position);
	}

}

//=============================================================================
// ���̃X�P�[���ݒ�֐�
//=============================================================================
void ActorRB::SetRigidbodyScale(Vector3 _scale)
{

	//��b�X�P�[����ݒ�
	m_Scale = _scale;

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->SetScale(m_Scale);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(m_Scale);
	}

}


//=============================================================================
// �X�t�B�A�^���̒ǉ��֐�(�����͑傫���E���W�E����)
//=============================================================================
void ActorRB::AddSphereRB(const Vector3& _scale, const Vector3& _position, float _mass)
{

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddSphere(HalfSize(_scale), _position, _mass);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(_scale);
	}

}

//=============================================================================
// �{�b�N�X�^���̒ǉ�(�����͑傫���E���W�E����)
//=============================================================================
void ActorRB::AddBoxRB(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddBox(HalfSize(_scale), _position, _mass);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(_scale);//�X�P�[���ݒ�
	}

}

//=============================================================================
// �J�v�Z���^���̒ǉ�(�����͔��a�E�����E���W�E��]�E����)
//=============================================================================
void ActorRB::AddCapsuleRB(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass)
{

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		m_Component_Rigidbody->AddCapsule(HalfSize(_radius), HalfSize(_height),_position,_rotation,_mass);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		m_Component_OBB->SetScale(Vector3{ _radius,_height,_radius });//�X�P�[���ݒ�
	}

}