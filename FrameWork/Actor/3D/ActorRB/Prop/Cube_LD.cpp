//=============================================================================
//
// ���x���f�U�C���p�L���[�u�N���X [Cube_LD.h]
//  Date   : 2021/1/19
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Cube_LD.h"
#include "../../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../../Component/Component_Cube.h"
#include "../../../../Manager/Manager_Texture.h"
#include "../../../../Manager/Manager_Shader.h"

//=============================================================================
// ���\�[�X�ǂݍ��݁E�폜�֐�
//=============================================================================
void  Cube_LD::Load()
{
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{//�e�N�X�`���[�}�l�[�W���[�L���b�V��

		//�e�N�X�`���[�ǂݍ���
		manager_Texture->LoadTexture("LD","ROM/2D/Material/T_BasicGrid_M.png");
	}

}
void  Cube_LD::Unload()
{
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{//�e�N�X�`���[�}�l�[�W���[�L���b�V��

		//�e�N�X�`���[���
		manager_Texture->UnloadTexture("LD");
	}
}

//=============================================================================
// �������֐�
//=============================================================================
void  Cube_LD::Init()
{
	//������
	ActorRB::Init();

	//�L���[�u�R���|�[�l���g�ǉ�
	m_Component_Cube = AddComponent<Component_Cube>(0);

	//�L���[�u�R���|�[�l���gnull�`�F�b�N
	if (m_Component_Cube != nullptr)
	{
		//�e�N�X�`���ݒ�
		m_Component_Cube->SetTexture("LD");
	}

	//�ÓI�{�b�N�X���W�b�h�{�f�B�ǉ�
    AddBoxRB(m_Scale, m_Position, 0);

}