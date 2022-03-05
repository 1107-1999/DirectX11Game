//=============================================================================
//
//  �e�N�X�`���[�}�l�[�W���[ [Manage_Texturer.cpp]
//  Date   : 2021/11/2
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Manager_Texture.h"
#include "../Renderer/Renderer_DirectX11.h"

//=============================================================================
// �������֐�
//=============================================================================
void Manager_Texture::Init(void)
{
	//�G���[�p�e�N�X�`���ǂݍ���

	//���d���[�h�h�~
	if (!m_Textures["Error"])
	{
		// �e�N�X�`���ǂݍ���
		D3DX11CreateShaderResourceViewFromFile(Renderer_DirectX11::Instance()->GetDevice(),
			"ROM/2D/Error/T_Error.png",
			NULL,
			NULL,
			&m_Textures["Error"],
			NULL);

		assert(m_Textures["Error"]);
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void Manager_Texture::Uninit()
{
	//�C�e���[�^�[
	std::unordered_map<std::string, ID3D11ShaderResourceView*>::iterator itr = m_Textures.begin();

	for (itr; itr != m_Textures.end(); itr++)
	{//�S�v�f�����[�v
		if (ID3D11ShaderResourceView* texture = itr->second)
		{
			texture->Release();//�Ώۂ̗v�f���폜
		}
	}

	m_Textures.clear();
}

//=============================================================================
// ���\�[�X�ǂݍ��݊֐�
//=============================================================================
ID3D11ShaderResourceView*  Manager_Texture::LoadTexture(const char* _key, const char* _fileName)
{
	if (!m_Textures[_key])//���d���[�h�h�~
	{
		D3DX11CreateShaderResourceViewFromFile(Renderer_DirectX11::Instance()->GetDevice(),// �e�N�X�`���ǂݍ���
			_fileName,
			NULL,
			NULL,
			&m_Textures[_key],
			NULL);
	}

	return m_Textures[_key];
}

//=============================================================================
// ���\�[�X����֐�
//=============================================================================
void Manager_Texture::UnloadTexture(const char* _key)
{
	if (m_Textures[_key])//���d�A�����[�h�h�~
	{
		m_Textures[_key]->Release();//�Ώۂ̗v�f���폜
		m_Textures.erase(_key);//�L�[���폜
	}
}
