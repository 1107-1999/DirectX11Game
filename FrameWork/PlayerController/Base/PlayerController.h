//=============================================================================
//
//  �v���C���[�R���g���[���[(�L�[�}�b�s���O) [PlayerConroller.h]
//  Date   : 2021/10/13
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../System/Input.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr float ZOOM_SPEED = 0.25f;

//=============================================================================
// �N���X��`
//=============================================================================
class PlayerController
{
protected :

	class Input* m_Input;           //�C���v�b�g�L���b�V��
	class MainWindow* m_MainWindow; //Window�L���b�V��

	float m_Mouse_Sensi   = 0.002f;//�}�E�X���x
	float m_Gamepad_Sensi = 0.04f; //�Q�[���p�b�h���x

	//�O��ړ��L�[�}�b�s���O
	float MoveForward();

	//���E�ړ��L�[�}�b�s���O
	float MoveRight();
	
	//�J�������E�L�[�}�b�s���O
	float Turn();
	
	//�J�����㉺�L�[�}�b�s���O
	float LookUp();

	//�J�����Y�[���L�[�}�b�s���O
	float Zoom();

	//���C���A�N�V�����L�[�}�b�s���O
	bool InputAction_Main();

	//�Z�J���h�A�N�V�����L�[�}�b�s���O
	bool InputAction_Second();

	//�X�v�����g�L�[�}�b�s���O
	bool InputAction_Sprint();

	//�W�����v�L�[�}�b�s���O
	bool InputAction_Jump();

	//�|�[�Y�L�[�}�b�s���O
	bool InputAction_Pause();

	//�g�p�L�[�}�b�s���O
	bool InputAction_Use();

public:

	//������
	virtual void Init();

	//�X�V�������z�֐�
	virtual void Update() = 0;

};
