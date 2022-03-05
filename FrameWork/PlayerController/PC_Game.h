//=//=============================================================================
//
//  �Q�[���V�[���p�v���C���[�R���g���[���[ [PC_Game.h]
//  Date   : 2021/1/22
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/PlayerController.h"

//=============================================================================
// �N���X��`
//=============================================================================
class PC_Game : public PlayerController
{
private:

	//�t���O
	bool m_GunFlag;   //�e�ڐG�t���O
	bool m_ScopeFlag; //�X�R�[�v�g�p�t���O
	bool m_ShotFlag;  //�ˌ��t���O
	bool m_GoalFlag;  //�S�[���t���O

	//���`��Ԕ䗦
	float m_LerpRate;

public:

	void Init()override;
	void Update()override;

	//�e�ڐG�t���O�擾�E�ݒ�
	inline bool GetGunFlag()const  { return m_GunFlag; }
	inline void SetGunFlag(bool _flag) { m_GunFlag = _flag; }

	//�S�[���t���O�`�F�b�N
	inline bool GetGoalFlag()const { return m_GoalFlag; }
	inline void SetGoalFlag(bool _flag) { m_GoalFlag = _flag; }

	//�X�R�[�v�g�p�t���O�擾�E�ݒ�
	inline bool GetScopeFlag()const{ return m_ScopeFlag; }

};
