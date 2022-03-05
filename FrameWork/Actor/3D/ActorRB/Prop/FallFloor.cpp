//=============================================================================
//
//  �����鏰�N���X [FallFloor.cpp]
//  Date   : 2021/1/24
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "FallFloor.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Manager/Manager_Audio.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr float START_POSTION  = 285.0f;
constexpr float END_POSTION    = 87.5f;
constexpr int   PUSHER_PATTERN = 4;
constexpr int   FALL_COOLTIME  = 300;

//=============================================================================
// ���\�[�X�ǂݍ��݁E�폜�֐�
//=============================================================================
void  FallFloor::Load()
{
	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//�K���X���ǂݍ���
		manager_audio->Load_Resource("Glass_Destoroy", "ROM\\Sound\\SE\\FootStep\\Glass\\Glass_Destoroy.wav");
	}
}
void  FallFloor::Unload()
{
	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//�K���X���폜
		manager_audio->Unload_Resource("Glass_Destoroy");
	}
}

//=============================================================================
// �������֐�
//=============================================================================
void  FallFloor::Init()
{
	//�e�N���X������
	ActorRB::Init();

	//�L���[�u�R���|�[�l���g�ǉ�
	m_Component_Cube = AddComponent<Component_Cube>(0);

	//�L���[�u�R���|�[�l���gnull�`�F�b�N
	if (m_Component_Cube != nullptr)
	{

		//�e�N�X�`���ݒ�
		m_Component_Cube->SetTexture("LD");

	}

	//�ÓI�{�b�N�X���̒ǉ�
	AddBoxRB(m_Scale, m_Position, 1000000);

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//�d�͖�����
		m_Component_Rigidbody->SetGravity(Vector3_Zero);
	}

	//���̂̃X�P�[���I�t�Z�b�g�ݒ�
	SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });

	//�v���C���[���m�pOBB�ǉ�
	m_ON_Judge = AddComponent<Component_OBB>(0);

	//�v���C���[���m�pOBB�ǉ�null�`�F�b�N
	if (m_ON_Judge != nullptr)
	{
		//�X�P�[������
		m_ON_Judge->SetScale(Vector3{ 8.5f,1.0f,3.0f});

	}

	//�L���b�V���p���W������
	m_Positioncache = Vector3_Zero;
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void FallFloor::Update()
{

	//�v���C���[���m�pOBB�ǉ�null�`�F�b�N
	if (m_ON_Judge != nullptr)
	{

		//�v���C���[������Ă���ꍇ
		if (m_ON_Judge->GetOverlap())
		{

		    //���݂̍��W�ۑ�
			m_Positioncache = m_Position;

			//�����N�[���^�C������
			m_CoolTime = FALL_COOLTIME;

			if (m_Component_Rigidbody != nullptr)
			{//null�`�F�b�N

				//�����͈͂Ƀ��[�v
				m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });
			}

			//�I�[�f�B�I�}�l�[�W���[�L���b�V��
			if (Manager_Audio* manager_audio = Manager_Audio::Instance())
			{
				//�K���X���Đ�
				manager_audio->Play("Glass_Destoroy",0);
			}
		}
	}

	//�����N�[���^�C��������ꍇ
	if (m_CoolTime > 0)
	{
		//�N�[���^�C�����Z
		m_CoolTime--;

		//�N�[���^�C���I����
		if (m_CoolTime == 0)
		{
			//���̃R���|�[�l���gnull�`�F�b�N
			if (m_Component_Rigidbody != nullptr)
			{
				//����ʒu�Ƀ��[�v
				m_Component_Rigidbody->SetWarp(m_Positioncache);
			}
		}
	}

	//�e�N���X�X�V
	ActorRB::Update();
	
}

