//=============================================================================
//
//  �X�v���C�g�R���|�[�l���g [Component_Sprite.cpp]
//  Date   : 2021/11/02
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Component_Sprite.h"
#include "../Actor/2D/Base/Actor2D.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_Sprite.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Level/Base/Level.h"

//=============================================================================
//�@�������֐�
//=============================================================================
void Component_Sprite::Init()
{
	//���N���X������
	Component::Init();

	//�f�t�H���g�̓A�����b�g�V�F�[�_�[
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//���]�t���O
	m_Reverse = false;

	//�f�t�H���g�e�N�X�`���g�p�t���O
	m_isUseDefaultTexture = false;

	//�F�����l
	m_Color = { 1.0f,1.0f,1.0f,1.0f };

	//Z���W�����l
	m_PostionZ = 0.0f;

	//Actor2D�ɃL���X�g���������ꍇ
	if (Actor2D* actor2D = dynamic_cast<Actor2D*>(m_Owner))
	{
		//�I�[�i�[�̍��W�L���b�V��
		m_Position2D = actor2D->GetPosition2D();

		//�I�[�i�[�̃X�P�[���L���b�V��
		m_Scale2D = actor2D->GetScale2D();
	}

	//�X�v���C�g�}�l�[�W���[���擾�ł����ꍇ
	if (Manager_Sprite* manager_Sprite = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Sprite())
	{
		//���g���}�l�[�W���[�ɓo�^
		manager_Sprite->AddComponent(this);
	}

}

//=============================================================================
//�@�I���֐�
//=============================================================================
void Component_Sprite::Uninit()
{
	//�L���b�V�������e�N�X�`��������ꍇ
	if (m_Texture != nullptr)
	{
		//nullptr��
		m_Texture = nullptr;
	}
}

//=============================================================================
//�@�`��֐�
//=============================================================================
void Component_Sprite::Draw()
{
	//�L�����e�N�X�`����null�ł͂Ȃ��ꍇ
	if (m_Active && m_Texture != nullptr && m_Owner != nullptr)
	{
		//�V�F�[�_�[�ݒ�
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//�e�N�X�`���ݒ�
		Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		//�|���S���`��@�\�ŕ`��
		Renderer_Polygon::Instance()->Draw2D(m_Position2D, m_Scale2D, m_Color, m_Reverse, m_PostionZ);
	}
}

//=============================================================================
//�@�e�N�X�`���ݒ�֐�
//=============================================================================
void Component_Sprite::SetTexture(const char* Key)
{
	//�w��̃L�[�̃e�N�X�`�������邩�m�F
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(Key))
	{
		//�e�N�X�`���ݒ�
		m_Texture = texture;
	}
}