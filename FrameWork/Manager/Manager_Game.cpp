//=============================================================================
//
//  �Q�[���}�l�[�W���[ [Manager_Game.cpp]
//  Date   : 2021/11/02
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <time.h>
#include "Manager_Game.h"
#include "Manager_Texture.h"
#include "Manager_Shader.h"
#include "Manager_Drawer/Manager_ImGui.h"
#include "Manager_Drawer/Manager_Font2D.h"
#include "Manager_Font.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Level/Level_Game.h"
#include "../Level/Level_Title.h"
#include "../System/Input.h"
#include "../System/Main.h"

//=============================================================================
// �������֐�
//=============================================================================
void Manager_Game::Init()
{

	//�e��Q�[���\���ɕK�v�ȃV���O���g���}�l�[�W���[������
	Manager_Texture::Instance()->Init();  //�e�N�X�`���}�l�[�W���[������
	Manager_Shader::Instance()->Init();   //�V�F�[�_�[�}�l�[�W���[������
	Renderer_Polygon::Instance()->Init(); //�|���S���`��@�\������
	Manager_Font2D::Instance()->Init();   //2D�t�H���g�}�l�[�W���[������

    //�v���C���[�R���g���[���[��null���
	m_PlayerController = nullptr;      
	 
	//���݂̃��x����null���
	m_Level = nullptr;

	//  ���̃��x����null���
	m_NextLevel = nullptr;

	//�Q�[���V�[���Z�b�g
	LoadLevelByClass<Level_Game>(30.0f);

}
//=============================================================================
// �X�V�֐�
//=============================================================================
void Manager_Game::Update()
{
	//�v���C���[�R���g���[���[null�`�F�b�N
	if (m_PlayerController != nullptr)
	{
		//�v���C���[�R���g���[���[�X�V
		m_PlayerController->Update();
	}

	//���x��null�`�F�b�N
	if (m_Level != nullptr)
	{
		//���x���X�V
		m_Level->Update();
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void Manager_Game::Uninit()
{
	//�v���C���[�R���g���[���[null�`�F�b�N
	if (m_PlayerController != nullptr)
	{
		delete m_PlayerController;   //�폜
		m_PlayerController = nullptr;//null���
	}

	//���x��null�`�F�b�N
	if (m_Level != nullptr)
	{
		m_Level->Uninit(); //�I��
		delete m_Level;    //�폜
		m_Level = nullptr; //null���
	}

	//�}�l�[�W���[�I��
	Manager_Texture::Instance()->Uninit(); //�e�N�X�`���}�l�[�W���[�I��
	Manager_Shader::Instance()->Uninit();  //�V�F�[�_�[�}�l�[�W���[�I��
	Manager_Font2D::Instance()->Uninit();  //�t�H���g������

}

//=============================================================================
// �`��֐�
//=============================================================================
void Manager_Game::Draw()
{
	//���x��null�`�F�b�N
	if (m_Level != nullptr)
	{
		//���x���`��
		m_Level->Draw();
	}
}
