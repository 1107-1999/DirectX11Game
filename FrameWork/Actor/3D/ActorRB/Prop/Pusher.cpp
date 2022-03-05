//=============================================================================
//
// �������̃N���X [Pusher.cpp]
//  Date   : 2021/1/23
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Pusher.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr float START_POSTION  = 285.0f;//�X�|�[���ʒu
constexpr float END_POSTION    = 87.5f; //�ړI�n
constexpr int   PUSHER_PATTERN = 4;     //�p�^�[����

//=============================================================================
// �������֐�
//=============================================================================
void  Pusher::Init()
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

	//�ÓI�{�b�N�X���W�b�h�{�f�B�ǉ�
	AddBoxRB(m_Scale, m_Position, 1000000);

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{

		//�d�͖�����
		m_Component_Rigidbody->SetGravity(Vector3_Zero);

		//���C��
		m_Component_Rigidbody->SetFriction(0.75f);

	}

	//���x������
	m_Velocity = {0.0f,0.0f,3000000.0f};
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Pusher::Update()
{
	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//Z���W�������z�����ꍇ
		if (m_Position.z <= END_POSTION)
		{
			//4�����烉���_���ɍ��W�ƃX�P�[����ݒ�
			int random = rand() % PUSHER_PATTERN;

			switch (random)
			{
			case 0:
				SetRigidbodyPosition(Vector3{ 0.0f,5.75f,275.0f });
				SetRigidbodyScale(Vector3{ 10.0f,1.0f,1.0f });
				break;
			case 1:
				SetRigidbodyPosition(Vector3{ -1.75f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 6.5f,4.0f,1.0f });
				break;
			case 2:
				SetRigidbodyPosition(Vector3{ 1.75f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 6.5f,4.0f,1.0f });
				break;
			case 3:
				SetRigidbodyPosition(Vector3{ 0.0f,7.25f,275.0f });
				SetRigidbodyScale(Vector3{ 7.0f,4.0f,1.0f });
				break;
			}
		}

		//�ړ�����
		m_Component_Rigidbody->SetMoveXYZ(-GetForward()* m_Velocity.z);

		//�e�N���X�X�V
		ActorRB::Update();
	}
}
