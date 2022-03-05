//=============================================================================
//
//  �L�����N�^�[������ [CharacterState_Run.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CharacterState_Sprint.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Fall.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr int KEY_FRAME   =  5;//�L�[�t���[��
constexpr int FRAME_RESET = 15;//�t���[�����Z�b�g����

//=============================================================================
// �������֐�
//=============================================================================
void CharacterState_Sprint::Init(Character* _owner)
{

	//���N���X������
	CharacterState::Init(_owner);

	//�t���[��������
	m_Frame = 0;

	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h��̃A�j���𑖂�A�j���ɐݒ�
		component_SkeletalMesh->SetNextAnimationName("Run");

	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CharacterState_Sprint::Update()
{
	if (m_Owner != nullptr)
	{
		//���x�ݒ�(�����ȏ㑖�薢���ɃN�����v)
		m_Owner->SetPlayerVelocity(Math::clamp(m_Owner->GetPlayerVelocity() + ONE_FRAME_UP_VELOCITY, MAX_WALK_VELOCITY, MAX_SPRINT_VELOCITY));

		//�v���C���[�̑����Ƀ��C���΂��Đڒn�𔻒肷��
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
			//�����}�e���A���ɉ������������Đ�
			m_Owner->PlayFootStep(hit_result.physicsMaterial);

			//���̉����Đ�
			m_Owner->PlayClothSound();

		}
		//�ő�t���[�����B��
		else if (m_Frame == FRAME_RESET)
		{
			//�A�N�Z�T�������Đ�
			m_Owner->PlayClothSoundMetal();
			//�t���[��������
			m_Frame = 0;
		}

	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CharacterState_Sprint::Uninit()
{
	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())

	{	//�u�����h���̃A�j���𑖂�A�j���ɐݒ�
		component_SkeletalMesh->SetCurrentAnimationName("Run");

	}
}

//=============================================================================
// ���ړ��֐�
//=============================================================================
void CharacterState_Sprint::MoveAxis(float _forward_value, float _right_value)
{
	//�����͂�����Ă��Ȃ��ꍇ
	if (fabsf(_forward_value) + fabsf(_right_value) <= STOP_VELOCITY)
	{
		//�_������ԂɑJ��
		m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
	}
	else
	{//�����͂�����Ă���ꍇ

		//���ړ�����
		CharacterState::MoveAxis(_forward_value, _right_value);

	}
}

//=============================================================================
// �X�v�����g�֐�
//=============================================================================
void  CharacterState_Sprint::Sprint(bool _input)
{
	//�X�v�����g���߂�����Ă��Ȃ��ꍇ
	if (!_input)
	{
		//������ԂɑJ��
		m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
	}
}

//=============================================================================
// �W�����v�֐�
//=============================================================================
void CharacterState_Sprint::Jump()
{
	//���̃R���|�[�l���g��null�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//�n�C�W�����v����
		m_Component_Rigidbody->HighJump();
	}

	//�W�����v�J�n��ԂɑJ��
	m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Start>();
}