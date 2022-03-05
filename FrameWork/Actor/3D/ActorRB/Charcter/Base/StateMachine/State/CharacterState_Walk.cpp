//=============================================================================
//
//  �L�����N�^�[������� [CharacterState_Walk.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CharacterState_Walk.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Sprint.h"
#include "CharacterState_Fall.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_OBB.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr int KEY_FRAME   = 5; //�L�[�t���[��
constexpr int KEY_FRAME2  = 15; //�L�[�t���[��2
constexpr int FRAME_RESET = 30;//�t���[�����Z�b�g����

//=============================================================================
// �������֐�
//=============================================================================
void CharacterState_Walk::Init(Character* _owner)
{

	//���N���X������
	CharacterState::Init(_owner);

	//�t���[��������
	m_Frame = 0;

	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{	
		//�u�����h��̃A�j��������A�j���ɐݒ�
		component_SkeletalMesh->SetNextAnimationName("Walk");

	}

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CharacterState_Walk::Update()
{
	if (m_Owner != nullptr)
	{
		//���x�ݒ�(��~���葬�x�ȏ�A�����ő呬�x�ȉ��ɃN�����v)
		m_Owner->SetPlayerVelocity(Math::clamp(m_Owner->GetPlayerVelocity() + ONE_FRAME_UP_VELOCITY, STOP_VELOCITY, MAX_WALK_VELOCITY));

		//�ڒn�𔻒�
		s_HIT_Result hit_result = m_Owner->GetComponentByClass<Component_OBB>()->Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true);

		//�ڒn���Ă��Ȃ��ꍇ
		if (!hit_result.isHIT)
		{
			//�W�����v�����ɋ󒆂ɂ��邽�ߗ�����ԂɑJ��
			m_Owner->GetStateMachine()->SetState<CharacterState_Fall>();

		}

		//�L�[�t���[���C�x���g�p�t���[�����Z
		m_Frame++;

		//�L�[�t���[���C�x���g
		if (m_Frame == KEY_FRAME)
		{
			//�����}�e���A���ɉ���������
			m_Owner->PlayFootStep(hit_result.physicsMaterial);
		}
		//�L�[�t���[���C�x���g2
		else if (m_Frame == KEY_FRAME2)
		{
			//���̉����Đ�
			m_Owner->PlayClothSound();

		}
		//�ő�t���[�����B��
		else if (m_Frame == FRAME_RESET)
		{
			//�A�N�Z�T�������Đ�
			m_Owner->PlayClothSoundMetal();

			//�t���[�������Z�b�g
			m_Frame = 0;
		}
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CharacterState_Walk::Uninit()
{
	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h���̃A�j��������ɐݒ�
		component_SkeletalMesh->SetCurrentAnimationName("Walk");
	}
}

//=============================================================================
// ���ړ��֐�
//=============================================================================
void CharacterState_Walk::MoveAxis(float _forward_value, float _right_value)
{
	//�����͂�����Ă��Ȃ��ꍇ
	if (fabsf(_forward_value) + fabsf(_right_value) <= STOP_VELOCITY)
	{
		//�_������ԂɑJ��
		m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
	}
	else
	{//�����͂�����Ă���ꍇ

		//���ړ�
		CharacterState::MoveAxis(_forward_value, _right_value);
	}
}

//=============================================================================
// �X�v�����g�֐�
//=============================================================================
void  CharacterState_Walk::Sprint(bool _input)
{
	//�X�v�����g���߂�����Ă���ꍇ
	if (_input)
	{
		//�����ԂɑJ��
		m_Owner->GetStateMachine()->SetState<CharacterState_Sprint>();
	}
}

//=============================================================================
// �W�����v�֐�
//=============================================================================
void CharacterState_Walk::Jump()
{
	//���N���X�W�����v����
	CharacterState::Jump();

	//�W�����v�J�n��ԂɑJ��
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();

}