//=============================================================================
//
//  ����ǃN���X [BreakWall.cpp]
//  Date   : 2021/1/24
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "BreakWall.h"
#include "../../Billboard/Explosion.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Component/Component_Billboard.h"
#include "../../../../Manager/Manager_Audio.h"
#include "../../../../Manager/Manager_Game.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Level/Base/Level.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr int   MAX_BREAK_COUNT  = 7;//�ő�ϋv�l

//=============================================================================
// �������֐�
//=============================================================================
void  BreakWall::Init()//������
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
		m_Component_Rigidbody->SetGravity(Vector3{0.0f,0.0f,0.0f});
	}

	//���̂̃X�P�[���ݒ�
	SetRigidbodyScale(Vector3{ 8.5f,0.25f,8.5f });

	//�ϋv�l������
	int m_BreakCount = 0;


}
//=============================================================================
// �ϋv�l���Z�֐�
//=============================================================================
void BreakWall::AddBreakCount()
{
	//�ϋv�l���Z
	m_BreakCount++;

	//�ϋv�l�ő�ɓ��B
	if (m_BreakCount == MAX_BREAK_COUNT)
	{
		//���̃R���|�[�l���gnull�`�F�b�N
		if (m_Component_Rigidbody != nullptr)
		{
			//�����r���{�[�h�G�t�F�N�g
			Explosion* explosion = Manager_Game::Instance()->GetLevel()->AddActor<Explosion>();

			//���W�ݒ�
			explosion->SetPosition(m_Position);

			//�X�P�[���ݒ�
			explosion->SetScale(Vector3{25.0f,25.0f,25.0f });

			//�A�j���Đ�
			explosion->Play();

			//�����͈͂Ƀ��[�v
			m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });
		}
	}
}

