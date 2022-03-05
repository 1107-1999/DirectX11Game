//=============================================================================
//
//  �S�[���N���X [Goal.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Goal.h"
#include "../Camera.h"
#include "../ActorRB/Prop/GunTarget.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../Component/Component_OBB.h"
#include "../../../Manager/Manager_Game.h"
#include "../../../Level/Base/Level.h"
#include "../../../PlayerController/PC_Game.h"

//=============================================================================
// �������֐�
//=============================================================================
void  Goal::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//OBB�R���|�[�l���g�ǉ�
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		//���W�b�h�{�f�B�Ɠ��X�P�[���ɒ���
		m_Component_OBB->SetScale(Vector3{ 2.0f,0.05f,2.0f });

		//���C�R���W�����𖳎�
		m_Component_OBB->SetIsReactRay(false);

		//�����}�e���A���𖳌�
		m_Component_OBB->SetPhysicsMaterial(PM_IGNORE);
	}

	//�v���C���[�R���g���[���[���擾&�L���X�g���ăL���b�V��
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Goal::Update()
{
	//�v���C���[�R���g���[���[��OBB�R���|�[�l���gnull�`�F�b�N
	if (m_PlayerConroller != nullptr && m_Component_OBB != nullptr)
	{
	    //�v���C���[�ƐڐG���Ă���ꍇ
		if (m_Component_OBB->GetOverlap())
		{
			//�v���C���[�R���g���[���[�ɃS�[���Ƃ̃I�[�o�[���b�v�����n��
			m_PlayerConroller->SetGoalFlag(true);

		}
		//�v���C���[�ƐڐG���Ă��Ȃ��ꍇ
		else
		{
			//�v���C���[�R���g���[���[�̃S�[���Ƃ̃I�[�o�[���b�v���������
			m_PlayerConroller->SetGoalFlag(false);

		}
	}
	else//null�̏ꍇ�L���b�V��
	{
		//�v���C���[�R���g���[���[���擾&�L���X�g���ăL���b�V��
		m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());
	}

	//�e�N���X�X�V
	Actor3D::Update();
}

//=============================================================================
// �I���֐�
//=============================================================================
void Goal::Uninit()
{
	//�e�N���X�X�V
	Actor3D::Uninit();
}

