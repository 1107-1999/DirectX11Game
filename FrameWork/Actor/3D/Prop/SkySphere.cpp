//=============================================================================
//
//  �X�J�C�X�t�B�A�N���X [SkySphere.cpp]
//  Date   : 2021/1/16
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "SkySphere.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"

//=============================================================================
// �������֐�
//=============================================================================
void  SkySphere::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//�ÓI���b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_StaticMesh != nullptr)
	{
		//3D���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_SkyNight.fbx", "ROM\\2D\\Sky\\T_Stars.png");
		//�X�P�[���I�t�Z�b�g����
		m_Component_StaticMesh->SetScaleRate(1000.0f);
	}

}
