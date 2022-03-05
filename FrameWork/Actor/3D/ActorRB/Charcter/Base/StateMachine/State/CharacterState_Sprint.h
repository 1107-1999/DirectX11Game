//=============================================================================
//
//  �L�����N�^�[������ [CharacterState_Sprint.h]
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
class CharacterState_Sprint : public CharacterState
{
private:

	//�L�[�t���[���C�x���g�p�̃t���[��
	int m_Frame;

public:

	//�������E�X�V�E�I��
	void Init(Character* _owner)override;
	void Update()override;
	void Uninit()override;

	//���ړ�
	void MoveAxis(float _forward_value, float _right_value)override;

	//�W�����v
	void Jump()override;

	//�X�v�����g
	void Sprint(bool _input)override;

};