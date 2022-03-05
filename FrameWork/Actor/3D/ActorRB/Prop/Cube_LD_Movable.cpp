//=============================================================================
//
// ���I���x���f�U�C���p�L���[�u�N���X [Cube_LD_Movable.cpp]
//  Date   : 2021/1/23
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Cube_LD_Movable.h"
#include "../../../../Manager/Manager_Shader.h"
#include "../../../../Component/Component_Cube.h"

//=============================================================================
// �������֐�
//=============================================================================
void  Cube_LD_Movable::Init()
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
		//���C��
		m_Component_Rigidbody->SetFriction(0.75f);
	}

	//���x������
	m_Velocity = Vector3_Zero;
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Cube_LD_Movable::Update()
{

	//�ڕWX���W��ʃ��߂��Ă����ꍇ�ɕ����]��
	if (m_Position.x >= m_Target.x && m_OldPosition.x < m_Target.x
		|| m_Position.x <= m_Target.x && m_OldPosition.x > m_Target.x)
	{
		//���݂�X���W��ړIX���W�ɂ���
		m_Position.x = m_Target.x;
		//�ړIX���W���ړ��J�n���W�ɐݒ�
		m_Target.x = m_Start.x;
		//�ړ��J�n���W�����݂̍��W�ɐݒ�
		m_Start.x = m_Position.x;
	}
	//�ڕWY���W��ʃ��߂��Ă����ꍇ�ɕ����]��
	if (m_Position.y >= m_Target.y && m_OldPosition.y < m_Target.y
		|| m_Position.y <= m_Target.y && m_OldPosition.y > m_Target.y)
	{
		//���݂�Y���W��ړIY���W�ɂ���
		m_Position.y = m_Target.y;
		//�ړIY���W���ړ��J�n���W�ɐݒ�
		m_Target.y = m_Start.y;
		//�ړ��J�n���W�����݂̍��W�ɐݒ�
		m_Start.y = m_Position.y;
	}
	//�ڕWZ���W��ʃ��߂��Ă����ꍇ�ɕ����]��
	if (m_Position.z >= m_Target.z && m_OldPosition.z < m_Target.z
		|| m_Position.z <= m_Target.z && m_OldPosition.z > m_Target.z)
	{
		//���݂�Z���W��ړIZ���W�ɂ���
		m_Position.z = m_Target.z;
		//�ړIZ���W���ړ��J�n���W�ɐݒ�
		m_Target.z = m_Start.z;
		//�ړ��J�n���W�����݂̍��W�ɐݒ�
		m_Start.z = m_Position.z;
	}

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//�ڕW���W�ɋ߂Â�
		if (m_Position.x > m_Target.x)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetRight()* m_Velocity.x);
		}
		else if (m_Position.x < m_Target.x)
		{
			m_Component_Rigidbody->SetMoveXYZ(GetRight()* m_Velocity.x);
		}
		if (m_Position.y > m_Target.y)
		{	
			m_Component_Rigidbody->SetMoveXYZ(-GetUp()* m_Velocity.y);
		}
		else if (m_Position.y < m_Target.y)
		{
		
			m_Component_Rigidbody->SetMoveXYZ(GetUp()* m_Velocity.y);
		}
		if (m_Position.z > m_Target.z)
		{
			m_Component_Rigidbody->SetMoveXYZ(-GetForward()* m_Velocity.z);
		}
		else if (m_Position.z < m_Target.z)
		{
			m_Component_Rigidbody->SetMoveXYZ(GetForward()* m_Velocity.z);
			
		}

		//1�t���[���O�̍��W�Ƃ��ĕۑ�
		m_OldPosition = m_Position;

		//�e�N���X�X�V
		ActorRB::Update();
	}
}
