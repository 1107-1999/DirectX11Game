//=============================================================================
//
//  �L�����N�^�[�W�����v����� [CharacterState_Jump_Loop.h]
//  Date   : 2021/11/28
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/CharacterState.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CharacterState_Jump_Loop : public CharacterState
{

private:

	//�W�����v���̈ړ����x��ۑ�
	float m_KeepVelocity;

	//�X�v�����g�t���O
	bool  m_Sprint;      

	//���C�̖������C���[�̃��X�g
	std::list<ACTOR_TYPE>m_IgnoreList;

public:
	
	//�������E�X�V�E�I��
	void Init(Character* _owner)override;
	void Update()override;
	void Uninit()override;

	//�X�v�����g
	void Sprint(bool _input)override;

	//�W�����v�s��
	void Jump()override {};
};