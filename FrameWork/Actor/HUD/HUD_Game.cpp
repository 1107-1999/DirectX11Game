//=============================================================================
//
//  �Q�[�����x���pHUD�N���X [HUD_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "HUD_Game.h"
#include "../../Component/Component_Sprite.h"
#include "../../Manager/Manager_Drawer/Manager_Font2D.h"
#include "../../Manager/Manager_Game.h"
#include "../../Manager/Manager_Texture.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/MainWindow.h"
#include "../../PlayerController/PC_Game.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr float LERP_SPEED = 0.085f;//��ԑ��x
constexpr float LERP_START = 0.01f; //��ԊJ�n
constexpr float LERP_END   = 0.99f; //��ԏI��

//=============================================================================
// ������
//=============================================================================
void HUD_Game::Init()
{
	//�e�N�X�`���[�}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�X�R�[�v�e�N�X�`���ǂݍ���
		manager_Texture->LoadTexture("Scope", "ROM\\2D\\Gun\\T_Scope.png");
	}

	//�X�R�[�vUI�p�X�v���C�g�R���|�[�l���g�ݒ�
	m_Component_Sprite_Scope = AddComponent<Component_Sprite>(0);//�ǉ�

		//�X�R�[�vUI�p�X�v���C�g�R���|�[�l���gnull�`�F�b�N
	if (m_Component_Sprite_Scope != nullptr)
	{
		m_Component_Sprite_Scope->SetTexture("Scope");	//�e�N�X�`���[�ݒ�
		m_Component_Sprite_Scope->SetPosition2D(Vector2_Zero);//���W�I�t�Z�b�g����
		m_Component_Sprite_Scope->SetActive(false);//�����ݒ�ł͔�\��

		//window�T�C�Y�擾
		Int2 windowSize = MainWindow::Instance()->GetWindowSize();
		//�X�P�[����window�T�C�Y�ɐݒ�
		m_Component_Sprite_Scope->SetScale2D(Vector2{ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
	}

	
	//�v���C���[�R���g���[���[���擾&�L���X�g���ăL���b�V��
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());


	//2D�t�H���g�}�l�[�W���[�L���b�V���L���b�V��
	if (m_Manager_Font2D = Manager_Font2D::Instance())
	{
		//���S���낦
		m_Manager_Font2D->SetAilgningMode(Manager_Font::e_Aligning::center);

		//�t�H���g�ݒ�
		m_Manager_Font2D->SetFont(L"02UtsukushiMincho", L"02������������");

		//�����̊Ԋu
		m_Manager_Font2D->SetCharLength(1.0f);

		//�t�H���g�T�C�Y�ݒ�
		m_Manager_Font2D->SetFontSize(64);

		//�C�^���b�N�̎g�p���Ȃ�
		m_Manager_Font2D->SetIsUseItalic(false);

		//�����̑���
		m_Manager_Font2D->SetFontWeight(FW_DONTCARE);

		//���F
		m_Manager_Font2D->SetFontColor(Color(1, 1, 1, 1));
	}

	//�|���S���`��@�\�N���X�L���b�V��
	m_Renderer_Polygon = Renderer_Polygon::Instance();

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void HUD_Game::Update()
{
	//�e�N���X�X�V
	HUD::Update();
}

//=============================================================================
// �I���֐�
//=============================================================================	
void HUD_Game::Uninit()
{

	//�e�N�X�`���[�}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�X�R�[�v�e�N�X�`���폜
		manager_Texture->UnloadTexture("Scope");
	}

	//�e�N���X�I��
	HUD::Uninit();
}
//=============================================================================
// �`��֐�
//=============================================================================
void HUD_Game::Draw()
{
	//2D�t�H���g�}�l�[�W���[�ƃ|���S���`��@�\�N���Xnull�`�F�b�N
	if (m_Manager_Font2D != nullptr && m_Renderer_Polygon != nullptr)
	{
		//�e�Փ˃t���O�������Ă���ꍇ
		if (m_PlayerConroller->GetGunFlag() && !m_PlayerConroller->GetScopeFlag())
		{
			//UI�`��(�����͍��W�E�X�P�[���E�F)
			m_Renderer_Polygon->DrawBox2D(Vector2{ 400.0f, -256.0f }, Vector2{ 400.0f,200.0f }, Color{0.0f,0.0f,0.0f,0.75f});

			//�e�L�X�g�`��(�����͍��W)
			m_Manager_Font2D->Printf2D({ 200.0f, -290.0f }, "�E�N���b�N:ADS");

		}
		//�S�[���t���O�������Ă���ꍇ
		if (m_PlayerConroller->GetGoalFlag())
		{
			//UI�`��(�����͍��W�E�X�P�[���E�F)
			m_Renderer_Polygon->DrawBox2D(Vector2{ 400.0f, -256.0f }, Vector2{ 600.0f,200.0f }, Color{ 0.0f,0.0f,0.0f,0.75f });

			//�e�L�X�g�`��(�����͍��W)
			m_Manager_Font2D->Printf2D({ 200.0f, -290.0f }, "���N���b�N:�X�^�[�g�ɖ߂�");
		}
	}
}

//=============================================================================
// �X�R�[�vUI�ݒ�֐�
//=============================================================================
void HUD_Game::SetScopeUI(bool _flag)
{
	//�X�R�[�vUI�p�X�v���C�g�R���|�[�l���g
	if (m_Component_Sprite_Scope != nullptr)
	{
		//�`��t���O�ݒ�
		m_Component_Sprite_Scope->SetActive(_flag);
	}
}
