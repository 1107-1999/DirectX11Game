////=============================================================================
//
//  �L�����N�^�[�X�e�[�g�}�V�� [StateMachine_Character.cpp].
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "StateMachine_Character.h"
#include "State/CharacterState_Idle.h"
#include "State/CharacterState_Jump_Start.h"
#include "State/CharacterState_Jump_Loop.h"
#include "State/CharacterState_Fall.h"
#include "State/CharacterState_Walk.h"
#include "State/CharacterState_Sprint.h"

//=============================================================================
// �������֐�
//=============================================================================
void StateMachine_Character::Init(Character* _owner)
{
	//�I�[�i�[���
	m_Owner = _owner;

	//�X�e�[�g��z��Ɋi�[
	m_CharacterStates.push_back(new CharacterState_Idle);
	m_CharacterStates.push_back(new CharacterState_Jump_Start);
	m_CharacterStates.push_back(new CharacterState_Jump_Loop);
	m_CharacterStates.push_back(new CharacterState_Fall);
	m_CharacterStates.push_back(new CharacterState_Walk);
	m_CharacterStates.push_back(new CharacterState_Sprint);

	//�����X�e�[�g�̓A�C�h��
	SetState<CharacterState_Idle>();

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void StateMachine_Character::Update()
{
	//���݂̏�Ԃ�null�`�F�b�N
	if (m_CharacterState != nullptr)
	{
		//�X�V
		m_CharacterState->Update();
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void StateMachine_Character::Uninit()
{
	//�S��Ԃ��폜
	for (CharacterState* state : m_CharacterStates)
	{
		delete state;
		state = nullptr;
	}

	//��Ԕz��̂̃N���A
	m_CharacterStates.clear();

}

//=============================================================================
//�@���ړ��֐�
//=============================================================================
void StateMachine_Character::MoveAxis(float _forward_value, float _right_value)
{
	//���݂̏�Ԃ�null�`�F�b�N
	if (m_CharacterState != nullptr)
	{
		//���ړ�
		m_CharacterState->MoveAxis(_forward_value,_right_value);
	}
}

//=============================================================================
//�@�X�v�����g�֐�
//=============================================================================
void StateMachine_Character::Sprint(bool _input)
{
	//���݂̏�Ԃ�null�`�F�b�N
	if (m_CharacterState != nullptr)
	{
		//�X�v�����g����
		m_CharacterState->Sprint(_input);
	}
}

//=============================================================================
//�@�W�����v�֐�
//=============================================================================
void StateMachine_Character::Jump()
{
	//���݂̏�Ԃ�null�`�F�b�N
	if (m_CharacterState != nullptr)
	{
		//�W�����v����
		m_CharacterState->Jump();
	}
}
