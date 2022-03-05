//=============================================================================
//
// �e�̃^�[�Q�b�g�̃��[���N���X [GunTargetRail.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GunTargetRail.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Component/Component_OBB.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// �������֐�
//=============================================================================
void GunTargetRail::Init()
{

	//�e�N���X������
	ActorRB::Init();

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//�ÓI���b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_StaticMesh != nullptr)
	{

		//���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Rail.fbx");

		//��]�I�t�Z�b�g X���@Y�� Z��
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(90.0f),DegToRad(0.0f) });

		//�X�P�[���I�t�Z�b�g����
		m_Component_StaticMesh->SetScaleRate(0.5f);

	}


	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//�ÓI�{�b�N�X���̒ǉ�(�������̓X�P�[���̃I�t�Z�b�g�l)
		m_Component_Rigidbody->AddBox(Vector3{2.5f,0.175f,0.625f}, m_Position, 0);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		//�X�P�[���I�t�Z�b�g����
		m_Component_OBB->SetScale(Vector3{ 5.0f,0.35f,1.25f });

		//�����}�e���A���������ɐݒ�
		m_Component_OBB->SetPhysicsMaterial(PM_METAL);
	}
}

