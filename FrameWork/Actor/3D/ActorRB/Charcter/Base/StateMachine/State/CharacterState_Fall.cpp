//=============================================================================
//
//  �L�����N�^�[������� [CharacterState_Fall.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CharacterState_Fall.h"
#include "CharacterState_Idle.h"
#include "CharacterState_Walk.h"
#include "CharacterState_Sprint.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �������֐�
//=============================================================================
void CharacterState_Fall::Init(Character*  _owner)
{
	//���N���X������
	CharacterState::Init(_owner);

	//�X�v�����g�t���O������
	m_Sprint = false;

	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h��̃A�j���𗎉��A�j���ɐݒ�
		component_SkeletalMesh->SetNextAnimationName("Fall");

	}

	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//���x�ݒ�
		(m_KeepVelocity < MAX_WALK_VELOCITY) ? m_KeepVelocity = MAX_WALK_VELOCITY : m_KeepVelocity = m_Owner->GetPlayerVelocity();

		//���̉����Đ�
		m_Owner->PlayClothSound();

	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CharacterState_Fall::Update()
{
	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//�v���C���[�̑����Ƀ��C���΂��Đڒn�𔻒肷��
		s_HIT_Result hit_result = m_Owner->GetComponentByClass<Component_OBB>()->
			Raycast(m_Owner->GetPosition(), m_Owner->GetPosition() - (m_Owner->GetUp() * GROUND_RAY_LENGTH), m_Owner, true,
			std::list<ACTOR_TYPE>(),//���g�𖳎�
			Color(0, 1, 1, 1));//RGBA�𐅐F�ɐݒ�

		//�ڒn���Ă���ꍇ
		if (hit_result.physicsMaterial != INVALID_ID && hit_result.physicsMaterial != PM_IGNORE)
		{
			//�����}�e���A���ɉ��������n�����Đ�
			m_Owner->PlayFootStep(hit_result.physicsMaterial);

			if (m_Sprint)
			{//�����ԂɑJ��
				m_Owner->GetStateMachine()->SetState<CharacterState_Sprint>();
			}
			else if (m_KeepVelocity >= STOP_VELOCITY)
			{//������ԂɑJ��
				m_Owner->GetStateMachine()->SetState<CharacterState_Walk>();
			}
			else
			{//�_������ԂɑJ��
				m_Owner->GetStateMachine()->SetState<CharacterState_Idle>();
			}

		}
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CharacterState_Fall::Uninit()
{
	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h���̃A�j���𗎉��A�j���ɐݒ�
		component_SkeletalMesh->SetCurrentAnimationName("Fall");
	}
}

//=============================================================================
// �X�v�����g�֐�
//=============================================================================
void CharacterState_Fall::Sprint(bool _input)
{
	//�X�v�����g�̃L�[��������Ă��邩�ǂ������m�F
	m_Sprint = _input;
}
