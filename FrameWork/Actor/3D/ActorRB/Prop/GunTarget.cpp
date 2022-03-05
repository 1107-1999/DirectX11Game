//=============================================================================
//
// �e�̃^�[�Q�b�g�N���X [GunTarget.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GunTarget.h"
#include "../../Billboard/Explosion.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Manager/Manager_Game.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Level/Base/Level.h"
#include "../../../../Actor/3D/ActorRB/Prop/BreakWall.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr float TARGET_LIMIT = 2.75f;//�^�[�Q�b�g�̌��E���W

//=============================================================================
// �������֐�
//=============================================================================
void  GunTarget::Init()
{
	//������
	ActorRB::Init();

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	if (m_Component_StaticMesh != nullptr)
	{//null�`�F�b�N

		//���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Target.fbx");

		//��]�I�t�Z�b�g X���@Y�� Z��
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(-90.0f),DegToRad(0.0f) });

		//�X�P�[���I�t�Z�b�g
		m_Component_StaticMesh->SetScaleRate(0.5f);

	}

	//�ÓI�{�b�N�X���̒ǉ�
	AddBoxRB(m_Scale, m_Position, 1000000);

	//���W�b�h�{�f�B�R���|�[�l���g�����݂���ꍇ
	if (m_Component_Rigidbody != nullptr)
	{

		//�d�͖�����
		m_Component_Rigidbody->SetGravity(Vector3{0.0f,0.0f,0.0f});
		//�X�P�[���I�t�Z�b�g����
		m_Component_Rigidbody->SetScale(Vector3{ 0.5f,0.125f,0.75f });

	}

	//OBB�R���|�[�l���g�����݂���ꍇ
	if (m_Component_OBB != nullptr)
	{
		//���W�b�h�{�f�B�Ɠ��X�P�[���ɒ���
		m_Component_OBB->SetScale(Vector3{ 0.5f,0.63f,0.1f });
		m_Component_OBB->SetPositionOffset(Vector3{ 0.0f,0.925f,0.0f });
	}

	//�������x
	m_Velocity = 2000000.0f;

	//�i�s����
	m_Vector = true;

	//�����G�t�F�N�g�L���b�V��
	m_Explosion = Manager_Game::Instance()->GetLevel()->AddActor<Explosion>();

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void GunTarget::Update()
{
	if (m_Component_OBB->GetOverlap())
	{//�e�ƂԂ������ꍇ

		if (m_Explosion != nullptr)
		{//�����G�t�F�N�g�ݒ�

		    //�����A�j���Đ�
			m_Explosion->Play();

			//���W�ݒ�
			m_Explosion->SetPosition(m_Position + HalfSize(GetUp()));
		}

		//�����͈͂Ƀ��[�v
		m_Component_Rigidbody->SetWarp(Vector3{ 0.0f,-1000.0f,0.0f });

		if (BreakWall* wall = Manager_Game::Instance()->GetLevel()->GetActor<BreakWall>())
		{//�擾&�L���b�V��
			wall->AddBreakCount();
		}

	}

	//�ڕW���W��ʃ��߂��Ă����ꍇ�ɕ����]��
	if (m_Position.x >= TARGET_LIMIT && !m_Vector)
	{
		m_Position.x = TARGET_LIMIT;
		m_Vector = true;
	}
	else if (m_Position.x <= -TARGET_LIMIT && m_Vector)
	{
		m_Position.x = -TARGET_LIMIT;
		m_Vector = false;
	}

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		if (m_Vector)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetRight()* m_Velocity);
		}
		else 
		{
			m_Component_Rigidbody->SetMoveXYZ(GetRight()* m_Velocity);
		}
	
		//�e�N���X�X�V
		ActorRB::Update();
	}
}
