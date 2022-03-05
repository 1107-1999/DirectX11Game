//=============================================================================
//
// �e�̃e�[�u���N���X [GunTable.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GunTable.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Component/Component_OBB.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// �������֐�
//=============================================================================
void GunTable::Init()
{

	//�e�N���X������
	ActorRB::Init();

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//�ÓI���b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_StaticMesh != nullptr)
	{
		//���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Table.fbx");

		//�|�W�V�����I�t�Z�b�g
		m_Component_StaticMesh->SetPositionOffset(Vector3{ 0.0f,-0.6f,0.0f });
	
		//�X�P�[���I�t�Z�b�g����
		m_Component_StaticMesh->SetScaleRate(0.055f);

	}

	//���̃R���|�[�l���gnull�`�F�b�N
	if (m_Component_Rigidbody != nullptr)
	{
		//�ÓI�{�b�N�X���̒ǉ�(�������̓X�P�[���̃I�t�Z�b�g�l)
		m_Component_Rigidbody->AddBox(Vector3{ 0.8f,0.65f,0.5f }, m_Position, 0);
	}

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		//���W�b�h�{�f�B�Ɠ��X�P�[���ɒ���
		m_Component_OBB->SetScale(Vector3{ 1.5f,1.0f,1.0f });

		//�����}�e���A����؂ɐݒ�
		m_Component_OBB->SetPhysicsMaterial(PM_WOOD);
	}
}

