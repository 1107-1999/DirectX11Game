//=============================================================================
//
//  �L�����N�^�[�X�e�[�g�}�V�� [StateMachine_Character.h]
//  Date   : 2021/11/28
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <vector>
#include <typeinfo>
#include "State/Base/CharacterState.h"

//=============================================================================
// �N���X��`
//=============================================================================
class StateMachine_Character
{
private:

	//�I�[�i�[
	class Character* m_Owner;

	//�I�[�i�[�̌��݂̏��
	class CharacterState* m_CharacterState = nullptr;

	//�I�[�i�[�̏�Ԕz��
	std::vector<class CharacterState*> m_CharacterStates;

public:

	//�������E�X�V�E�I��
	void Init(Character* _owner);
	void Update();
	void Uninit();

	//���ړ�
	void MoveAxis(float _forward_value, float _right_value);

	//�X�v�����g
	void Sprint(bool _input);

	//�W�����v
	void Jump();

	//=============================================================================
	// ��Ԑݒ�֐�
	//=============================================================================
	template<typename T>
	inline void SetState()
	{
		//���݂̏�Ԃ����݂���ꍇ
		if (m_CharacterState != nullptr)
		{
			//�I������
			m_CharacterState->Uninit();
			m_CharacterState = nullptr;
		}

		//��Ԕz�񂩂�w��̏�Ԃ�����
		for (CharacterState* state : m_CharacterStates)
		{
			if (typeid(*state) == typeid(T))
			{
				//�w��̏�ԂɑJ��
				m_CharacterState = state;

				//�������֐�
				m_CharacterState->Init(m_Owner);
			}
		}
	}

	//��Ԏ擾
	inline CharacterState* GetCharacterState() { return m_CharacterState; }
};

