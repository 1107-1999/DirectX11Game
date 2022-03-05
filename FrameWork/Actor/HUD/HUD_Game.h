//=============================================================================
//
//  �Q�[�����x���pHUD�N���X [HUD_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/HUD.h"

//=============================================================================
// �N���X��`
//=============================================================================
class HUD_Game : public HUD
{
private:

	//�|���S���`��@�\�N���X�L���b�V��
	class Renderer_Polygon*    m_Renderer_Polygon;

	//2D�}�l�[�W���[�t�H���g�L���b�V��
	class Manager_Font2D*      m_Manager_Font2D;

	//�v���C���[�R���g���[���[�L���b�V��
	class PC_Game*             m_PlayerConroller;

	//�X�R�[�vUI�p�X�v���C�g�R���|�[�l���g
	class Component_Sprite*    m_Component_Sprite_Scope;


public:

	//�������E�I���E�X�V
	void Init()  override;
	void Update()override;
	void Uninit()override;

	//�`��
	void Draw()override;

	//�X�R�[�v��UI��ݒ�
	void SetScopeUI(bool _flag);

};