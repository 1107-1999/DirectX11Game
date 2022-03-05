//=============================================================================
//
//  �L�����N�^�[�W�����v�J�n��� [CharacterState_Jump_Start.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CharacterState_Jump_Loop.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �������֐�
//=============================================================================
void CharacterState_Jump_Start::Init(Character* _owner)
{

	//���N���X������
	CharacterState::Init(_owner);

	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//�u�����h��̃A�j�����W�����v�J�n�A�j���ɐݒ�
		component_SkeletalMesh->SetNextAnimationName("Jump_Start");

		//0�t���[���ڂ���A�j�����u�����h
		component_SkeletalMesh->SetNextAnimationFrame(0);

	}

	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//���̉����Đ�
		m_Owner->PlayClothSound();

		//�A�N�Z�T���̉����Đ�
		m_Owner->PlayClothSoundMetal();

	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CharacterState_Jump_Start::Update()
{
	//�I�[�i�[��null�`�F�b�N
	if (m_Owner != nullptr)
	{
		//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
		if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
		{
			//�u�����h���[�g��0.1�ȏ�̏ꍇ
			if (component_SkeletalMesh->GetBlendLate() > 0.1f)
			{
				//�W�����v���ɑJ��
				m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Loop>();

			}
		}
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CharacterState_Jump_Start::Uninit()
{
	//�X�P���^�����b�V���R���|�[�l���g�����݂���ꍇ
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{	
		//�u�����h���̃A�j�����W�����v�J�n�A�j���ɐݒ�
		component_SkeletalMesh->SetCurrentAnimationName("Jump_Start");

	}
}