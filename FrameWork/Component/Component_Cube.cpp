//=============================================================================
//
//  �L���[�u�R���|�[�l���g [Component_Cube.cpp]
//  Author : Ryosuke Kotera
//  Date   : 2021/1/19
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <math.h>
#include "Component_Cube.h"
#include "../Level/Base/Level.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"
#include "../Manager/Manager_Game.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Actor/3D/Base/Actor3D.h"

//=============================================================================
// �������֐�
//=============================================================================
void Component_Cube::Init()
{
	//���N���X������
	Component::Init();

	//�f�t�H���g�̓A�����b�g�V�F�[�_�[
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//�e�N�X�`�����[�v�ݒ�
	m_TexLoop = true;

	//�F�𔒂ɐݒ�
	m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

	//�L���[�u�}�l�[�W���[���擾�ł����玩�g��o�^
	if (m_Manager_Cube = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Cube())
	{
		m_Manager_Cube->AddComponent(this);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void Component_Cube::Draw()
{
	//Actor3D�ɃL���X�g
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{
		//�V�F�[�_�[�ݒ�
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//�f�o�b�O�`��
		if (Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetDebugCube())
		{
			ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture("LD");
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
		}
		//�ʏ�`��
		else
		{
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
		}
		
	
		// �e�`��p�e�N�X�`��
		if (m_ShaderType == Manager_Shader::SHADER_DEPTHSHADOW)
		{
			ID3D11ShaderResourceView* ShadowTexture = Renderer_DirectX11::Instance()->GetShadowDepthTexture();
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(1, 1, &ShadowTexture);
		}

		//�|���S�������_���[����`��
		Renderer_Polygon::Instance()->DrawBox(actor3D->GetPosition(), actor3D->GetRotation(), actor3D->GetScale(), m_Color, m_TexLoop);
	}
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
//=============================================================================
void Component_Cube::SetTexture(const char* _Key)
{
	//�w��̃L�[�̃e�N�X�`���[�����邩�m�F
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(_Key))
	{
		//�e�N�X�`���ݒ�
		m_Texture = texture;
	}
}