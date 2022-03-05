//=============================================================================
//
//  �L�����N�^�[�_������� [CharacterState_Idle.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Jump_Start.h"
#include "CharacterState_Jump_Loop.h"
#include "CharacterState_Fall.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �������֐�
//=============================================================================
void CharacterState_Idle::Init(Character* _owner)
{
	//���N���X������
	CharacterState::Init(_owner);

	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h��̃A�j����_�����A�j���ɐݒ�
		component_SkeletalMesh->SetNextAnimationName("Idle");

	}

	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//���x���~���葬�x�ɐݒ�
		m_Owner->SetPlayerVelocity(STOP_VELOCITY);

	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CharacterState_Idle::Update()
{
	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//todo���u���[�V����

		//�^���Ƀ��C���΂��Đڒn���Ă��Ȃ������ꍇ
		if (!m_Owner->GetComponentByClass<Component_OBB>()->Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true).isHIT)
		{
			//�W�����v�����ɋ󒆂ɂ��邽�ߗ�����ԂɑJ��
			m_Owner->GetStateMachine()->SetState<CharacterState_Fall>();
		}

	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CharacterState_Idle::Uninit()
{
	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h���̃A�j����_�����A�j���ɐݒ�
		component_SkeletalMesh->SetCurrentAnimationName("Idle");
	}
}

//=============================================================================
// ���ړ��֐�
//=============================================================================
void CharacterState_Idle::MoveAxis(float _forward_value, float _right_value)
{
	//�����͂�����Ă���ꍇ
	if (fabsf(_forward_value) + fabsf(_right_value) >= STOP_VELOCITY)
	{
		//������ԂɑJ��
		m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
	}
}

//=============================================================================
// �W�����v�֐�
//=============================================================================
void CharacterState_Idle::Jump()
{
	//���N���X�W�����v����
	CharacterState::Jump();

	//�W�����v�J�n��ԂɑJ��
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();

}
