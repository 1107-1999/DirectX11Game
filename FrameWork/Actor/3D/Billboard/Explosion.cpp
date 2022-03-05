//=============================================================================
//
//  �����r���{�[�h�G�t�F�N�g�N���X [Explosion.cpp]
//  Date   : 2022/1/26
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Explosion.h"
#include "../../../Component/Component_Billboard.h"
#include "../../../Manager/Manager_Texture.h"
#include "../../../Manager/Manager_Audio.h"

//=============================================================================
// ���\�[�X�ǂݍ��݁E�폜�֐�
//=============================================================================
void  Explosion::Load()
{
	//�e�N�X�`���[�}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�e�N�X�`���ǂݍ���
		manager_Texture->LoadTexture("Explosion", "ROM\\2D\\Effect\\T_Explosion.png");
	}

	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE�ǂݍ���
		manager_audio->Load_Resource("Explosion", "ROM\\Sound\\SE\\Effect\\Explosion.wav");
	}
}
void  Explosion::Unload()
{
	//�e�N�X�`���[�}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�e�N�X�`�����
		manager_Texture->UnloadTexture("Explosion");
	}

	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE���
		manager_audio->Unload_Resource("Explosion");
	}

}

//=============================================================================
// �������֐�
//=============================================================================
void  Explosion::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//�X�P�[���ݒ�
	m_Scale = Vector3{ 2.0f,2.0f,2.0f };

	//�r���{�[�h�R���|�[�l���g�ǉ�
	m_Component_Billboard = AddComponent<Component_Billboard>(0);//�ǉ�

	//�r���{�[�h�R���|�[�l���gnull�`�F�b�N
	if (m_Component_Billboard != nullptr)
	{
		m_Component_Billboard->SetTexture("Explosion");       //�e�N�X�`���[�ݒ�
		m_Component_Billboard->CalculationOneFrameSize(5, 4); //5*4�̃A�j���[�V�����Ƃ��Đݒ�
		m_Component_Billboard->SetMaxAnimCount(3);            //6�t���[����1�x�A�j���[�V�����X�V
		m_Component_Billboard->SetLoop(false);                //���[�v�Đ��Ȃ�
		m_Component_Billboard->SetActive(false);              //�����ݒ�͔�A�N�e�B�u
	}


}

//=============================================================================
// �Đ��֐�
//=============================================================================
void Explosion::Play()
{
	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//SE�Đ�
		manager_audio->Play("Explosion", 0);
	}
	//�r���{�[�h�R���|�[�l���gnull�`�F�b�N
	if (m_Component_Billboard != nullptr)
	{
		//�A�j���Đ�
		m_Component_Billboard->Replay();
	}

}