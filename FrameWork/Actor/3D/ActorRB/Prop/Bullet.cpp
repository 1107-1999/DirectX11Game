//=============================================================================
//
//  �e�N���X [Bullet.cpp]
//  Date   : 2021/1/10
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Manager/Manager_Shader.h"
#include "Bullet.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr int LIFE_TIME = 240;//��������

//=============================================================================
// �������֐�
//=============================================================================
void  Bullet::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//���W�I�t�Z�b�g����
	m_Position = Vector3{ -100.0f,-100.0f,-100.0f };

	//�X�P�[���I�t�Z�b�g����
	m_Scale = Vector3{0.25f,0.25f,0.25f};

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//�ÓI���b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_StaticMesh != nullptr)
	{
		//���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Sphere.fbx");

		//�X�P�[���I�t�Z�b�g����
		m_Component_StaticMesh->SetScaleRate(0.05f);

	}

	//�L���t���O�I�t
	m_Active = false;

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Bullet::Update()
{
	//�L���̏ꍇ
	if (m_Active)
	{
		//���W���Z
		m_Position += m_Velocity;

		//�������ԉ��Z
		m_LifeTime++;

		if (m_LifeTime >= LIFE_TIME)
		{//�������Ԃ����E���z�����ꍇ

			//�g�p�\
			m_Active = false;

		}
	}

	//�e�N���X�X�V
	Actor3D::Update();
}

//=============================================================================
//�@�e�����֐�
//=============================================================================
void Bullet::SpawnBullet(Vector3 _position, Vector3 _velocity,Vector3 _rotation)
{
	//���W�ݒ�
	m_Position = _position;

	//��]�ݒ�
	m_Rotation = _rotation;

	//���x�ݒ�
	m_Velocity = _velocity;

	//�L���t���O�I��
	m_Active = true;

	//�������ԏ�����
	m_LifeTime = 0;

}
